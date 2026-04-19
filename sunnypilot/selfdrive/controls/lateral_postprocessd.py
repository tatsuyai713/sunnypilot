#!/usr/bin/env python3
"""
Lateral Post-Processor Daemon — Algorithm D (B + C Hybrid)

Ported from rlog_viewer/plugin_bev_fusion.py for real-time use in sunnypilot.

Subscribes to modelV2, carState, livePose, liveDelay and publishes
lateralManeuverPlan with a processed desired curvature that blends:
  B) Single-frame preview curvature shaping (reactive)
  C) Temporal BEV path fusion (stable)
  D) Weighted hybrid of B and C

The processed curvature replaces modelV2.action.desiredCurvature via the
lateralManeuverPlan priority mechanism already wired in controlsd.py.
"""

from __future__ import annotations

import math
from collections import deque
from typing import Deque, Optional, Tuple

import numpy as np

import cereal.messaging as messaging
from cereal import car
from openpilot.common.params import Params
from openpilot.common.realtime import DT_MDL, Ratekeeper
from openpilot.common.swaglog import cloudlog
from openpilot.selfdrive.controls.lib.drive_helpers import clip_curvature

# ══════════════════════════════════════════════════════════════════
# Algorithm constants (matching rlog_viewer/plugin_bev_fusion.py)
# ══════════════════════════════════════════════════════════════════

GRID_STEP_M = 0.5
MIN_PROCESSING_HORIZON_M = 55.0
PREVIEW_LOOKAHEAD_TIMES: Tuple[float, ...] = (0.10, 0.25, 0.45, 0.70, 1.00)
PREVIEW_LOOKAHEAD_WEIGHTS_RAW = np.array([0.15, 0.20, 0.25, 0.22, 0.18], dtype=np.float64)
DEFAULT_PREVIEW_RESPONSE_DELAY_S = 0.18
PREVIEW_END_FADE_M = 10.0
PATH_STD_CONF_DECAY_M = 1.5
PATH_CONFIDENCE_FLOOR = 0.05
REFERENCE_SMOOTH_WINDOW = 5
CURVATURE_SMOOTH_WINDOW = 7
CONTROL_HORIZON_BASE_M = 10.0
CONTROL_HORIZON_SPEED_GAIN = 1.15
CONTROL_MIN_TRUST_HORIZON_M = 20.0
CONTROL_MAX_TRUST_HORIZON_M = 45.0
CONTROL_BLEND_FULL_M = 15.0
CONTROL_DELTA_CLAMP_BASE_M = 0.35
CONTROL_DELTA_CLAMP_GAIN = 0.03
TAIL_REFERENCE_BLEND_MARGIN_M = 8.0
FUSION_MIN_WEIGHT_SUM = 0.03
KAPPA_CLAMP_BLEND_M = 5.0
PROC_SCALAR_FIT_WINDOW_M = 6.0
PROC_SCALAR_MIN_POINTS = 5
PROC_SCALAR_WINDOW_M = 2.0

# Proc scalar reference
PROC_REF_MIN_DIST_M = 3.0
PROC_REF_PREVIEW_TIME_S = 0.15

# Temporal fusion
DEFAULT_FUSION_HISTORY_SECONDS = 1.2
FUSION_TIME_DECAY_TAU = 0.50
FUSION_DISTANCE_DECAY_TAU = 16.0
FUSION_ROBUST_GATE_BASE = 0.18
FUSION_ROBUST_GATE_GAIN = 0.012
FUSION_SMOOTH_WINDOW = 9

# C scalar stabilization
C_SCALAR_MEDIAN_WINDOW = 5
C_SCALAR_ALPHA_BASE = 0.08
C_SCALAR_ALPHA_SUPPORT_GAIN = 0.22
C_SCALAR_FULL_SUPPORT_CONTRIBUTORS = 6.0

# D hybrid blending
HYBRID_BASE_C_WEIGHT = 0.10
HYBRID_SUPPORT_GAIN = 0.65
HYBRID_MIN_C_WEIGHT = 0.05
HYBRID_MAX_C_WEIGHT = 0.85
HYBRID_PATH_AGREEMENT_DECAY_M = 0.60

# Lane-change handling
LANE_CHANGE_FUSION_HISTORY_S = 0.1
LANE_CHANGE_SCALAR_ALPHA = 0.6

# openpilot limits (for matching viewer replay)
OPENPILOT_MIN_SPEED_MPS = 1.0

# Preview lookahead scale
PREVIEW_LOOKAHEAD_SCALE = 1.0

# Dead reckoning
WHEELBASE_M = 2.70


# ══════════════════════════════════════════════════════════════════
# Utility functions (ported from plugin_bev_fusion.py)
# ══════════════════════════════════════════════════════════════════

def max_finite_x(path_x: np.ndarray) -> float:
  arr = np.asarray(path_x, dtype=np.float64)
  if arr.size == 0:
    return 0.0
  finite = arr[np.isfinite(arr)]
  return float(np.max(finite)) if finite.size > 0 else 0.0


def build_processing_grid(max_x: float) -> np.ndarray:
  if max_x > 0.0:
    max_x = math.ceil(max_x / GRID_STEP_M) * GRID_STEP_M
  horizon = max(MIN_PROCESSING_HORIZON_M, max_x)
  return np.arange(0.0, horizon + GRID_STEP_M, GRID_STEP_M, dtype=np.float64)


def resample_to_grid(path_x: np.ndarray, path_y: np.ndarray,
                     x_grid: np.ndarray) -> np.ndarray:
  order = np.argsort(path_x)
  xs, ys = path_x[order], path_y[order]
  keep = np.ones_like(xs, dtype=bool)
  keep[1:] = np.diff(xs) > 1e-6
  xs, ys = xs[keep], ys[keep]
  if len(xs) < 2:
    return np.zeros_like(x_grid)
  return np.interp(x_grid, xs, ys, left=ys[0], right=ys[-1])


def resample_to_grid_masked(path_x: np.ndarray, path_y: np.ndarray,
                             x_grid: np.ndarray):
  order = np.argsort(path_x)
  xs, ys = path_x[order], path_y[order]
  keep = np.ones_like(xs, dtype=bool)
  keep[1:] = np.diff(xs) > 1e-6
  xs, ys = xs[keep], ys[keep]
  if len(xs) < 2:
    return np.zeros_like(x_grid), np.zeros(len(x_grid), dtype=bool)
  y_out = np.interp(x_grid, xs, ys, left=ys[0], right=ys[-1])
  valid = (x_grid >= xs[0]) & (x_grid <= xs[-1])
  return y_out, valid


def smooth_signal(values: np.ndarray, window: int) -> np.ndarray:
  arr = np.asarray(values, dtype=np.float64)
  if arr.size == 0 or window < 3:
    return arr.copy()
  if window % 2 == 0:
    window += 1
  pad = window // 2
  kernel = np.ones(window, dtype=np.float64) / float(window)
  padded = np.pad(arr, (pad, pad), mode="edge")
  return np.convolve(padded, kernel, mode="valid")


def curvature_from_local_path(x: np.ndarray, y: np.ndarray) -> np.ndarray:
  dx = np.gradient(x)
  dy = np.gradient(y)
  ddx = np.gradient(dx)
  ddy = np.gradient(dy)
  denom = np.maximum((dx * dx + dy * dy) ** 1.5, 1e-9)
  return (dx * ddy - dy * ddx) / denom


def clamp_kappa_beyond_horizon(kappa: np.ndarray, x_grid: np.ndarray,
                               max_x: float) -> np.ndarray:
  kappa = np.array(kappa, dtype=np.float64)
  if max_x >= float(x_grid[-1]):
    return kappa
  blend_start = max_x - KAPPA_CLAMP_BLEND_M
  anchor_idx = max(0, int(np.searchsorted(x_grid, blend_start)))
  anchor_val = kappa[min(anchor_idx, len(kappa) - 1)]
  blend_mask = (x_grid >= blend_start) & (x_grid <= max_x)
  if np.any(blend_mask):
    t = np.clip((x_grid[blend_mask] - blend_start) / max(KAPPA_CLAMP_BLEND_M, 1e-6), 0.0, 1.0)
    t_smooth = t * t * (3.0 - 2.0 * t)
    kappa[blend_mask] = (1.0 - t_smooth) * kappa[blend_mask] + t_smooth * anchor_val
  kappa[x_grid > max_x] = anchor_val
  return kappa


def confidence_from_path_std(path_y_std: np.ndarray, expected_len: int) -> np.ndarray:
  if expected_len <= 0:
    return np.zeros(0, dtype=np.float64)
  arr = np.asarray(path_y_std, dtype=np.float64)
  if arr.size != expected_len:
    return np.ones(expected_len, dtype=np.float64)
  finite = np.isfinite(arr)
  if not np.any(finite):
    return np.ones(expected_len, dtype=np.float64)
  filled = arr.copy()
  filled[~finite] = float(np.nanmedian(filled[finite]))
  filled = np.maximum(filled, 0.0)
  conf = np.exp(-filled / PATH_STD_CONF_DECAY_M)
  return np.clip(conf, PATH_CONFIDENCE_FLOOR, 1.0)


def control_trust_horizon(v: float, max_x: float) -> float:
  if max_x <= 0.0:
    return 0.0
  target = CONTROL_HORIZON_BASE_M + CONTROL_HORIZON_SPEED_GAIN * max(v, 0.0)
  trusted = min(max_x, min(CONTROL_MAX_TRUST_HORIZON_M, max(CONTROL_MIN_TRUST_HORIZON_M, target)))
  return float(max(0.0, trusted))


def _smoothstep(x: np.ndarray, edge0: float, edge1: float) -> np.ndarray:
  if edge1 <= edge0:
    return (x >= edge1).astype(np.float64)
  t = np.clip((x - edge0) / (edge1 - edge0), 0.0, 1.0)
  return t * t * (3.0 - 2.0 * t)


def preview_weights() -> np.ndarray:
  return PREVIEW_LOOKAHEAD_WEIGHTS_RAW / PREVIEW_LOOKAHEAD_WEIGHTS_RAW.sum()


def preview_shape_curvature(
    kappa: np.ndarray,
    v: float,
    x_grid: np.ndarray,
    *,
    response_delay_s: float = DEFAULT_PREVIEW_RESPONSE_DELAY_S,
    support_horizon_m: Optional[float] = None,
    confidence: Optional[np.ndarray] = None,
    lookahead_scale: float = 1.0,
) -> np.ndarray:
  kappa_arr = np.asarray(kappa, dtype=np.float64)
  x_arr = np.asarray(x_grid, dtype=np.float64)
  shaped = np.empty_like(kappa_arr)
  weights = preview_weights()
  support_horizon = float(x_arr[-1]) if support_horizon_m is None else min(float(support_horizon_m), float(x_arr[-1]))
  conf_arr = None
  if confidence is not None and len(confidence) == len(x_arr):
    conf_arr = np.clip(np.asarray(confidence, dtype=np.float64), PATH_CONFIDENCE_FLOOR, 1.0)
  scale = max(float(lookahead_scale), 0.0)

  accum = np.zeros_like(kappa_arr)
  weight_sum = np.zeros_like(kappa_arr)
  for tau, base_weight in zip(PREVIEW_LOOKAHEAD_TIMES, weights):
    lookahead_offset = max(v * (tau + response_delay_s) * scale, 0.0)
    x_look = x_arr + lookahead_offset
    sample_x = np.minimum(x_look, support_horizon)
    fade = np.ones_like(x_arr)
    over_mask = x_look > support_horizon
    if np.any(over_mask):
      fade[over_mask] = np.maximum(0.0, 1.0 - (x_look[over_mask] - support_horizon) / PREVIEW_END_FADE_M)
    if conf_arr is not None:
      fade *= np.interp(sample_x, x_arr, conf_arr)
    effective_weight = base_weight * fade
    valid = effective_weight > 1e-9
    if not np.any(valid):
      continue
    sample = np.interp(sample_x, x_arr, kappa_arr)
    accum[valid] += effective_weight[valid] * sample[valid]
    weight_sum[valid] += effective_weight[valid]

  np.copyto(shaped, kappa_arr)
  valid = weight_sum > 1e-9
  shaped[valid] = accum[valid] / weight_sum[valid]
  return shaped


def reconstruct_path_from_curvature_delta(
    kappa_target: np.ndarray,
    kappa_ref: np.ndarray,
    y_ref: np.ndarray,
    x_grid: np.ndarray,
) -> np.ndarray:
  ds = float(x_grid[1] - x_grid[0])
  n = len(x_grid)
  delta_kappa = np.asarray(kappa_target, dtype=np.float64) - np.asarray(kappa_ref, dtype=np.float64)
  delta_slope = np.zeros(n, dtype=np.float64)
  for i in range(1, n):
    delta_slope[i] = delta_slope[i - 1] + 0.5 * (delta_kappa[i - 1] + delta_kappa[i]) * ds
  delta_y = np.zeros(n, dtype=np.float64)
  for i in range(1, n):
    delta_y[i] = delta_y[i - 1] + 0.5 * (delta_slope[i - 1] + delta_slope[i]) * ds
  return np.asarray(y_ref, dtype=np.float64) + delta_y


def clamp_path_delta(y_candidate: np.ndarray, y_ref: np.ndarray,
                     x_grid: np.ndarray) -> np.ndarray:
  max_delta = CONTROL_DELTA_CLAMP_BASE_M + CONTROL_DELTA_CLAMP_GAIN * np.asarray(x_grid, dtype=np.float64)
  delta = np.asarray(y_candidate, dtype=np.float64) - np.asarray(y_ref, dtype=np.float64)
  return np.asarray(y_ref, dtype=np.float64) + np.clip(delta, -max_delta, max_delta)


def blend_to_reference(
    y_candidate: np.ndarray,
    y_ref: np.ndarray,
    x_grid: np.ndarray,
    *,
    full_effect_m: float,
    zero_effect_m: float,
    confidence: Optional[np.ndarray] = None,
) -> np.ndarray:
  alpha = 1.0 - _smoothstep(np.asarray(x_grid, dtype=np.float64), full_effect_m, zero_effect_m)
  if confidence is not None and len(confidence) == len(x_grid):
    alpha *= np.sqrt(np.clip(np.asarray(confidence, dtype=np.float64), PATH_CONFIDENCE_FLOOR, 1.0))
  return np.asarray(y_ref, dtype=np.float64) + alpha * (np.asarray(y_candidate, dtype=np.float64) - np.asarray(y_ref, dtype=np.float64))


def build_control_stable_path(
    y_ref: np.ndarray,
    x_grid: np.ndarray,
    v: float,
    *,
    response_delay_s: float = DEFAULT_PREVIEW_RESPONSE_DELAY_S,
    confidence: Optional[np.ndarray] = None,
    tail_reference: Optional[np.ndarray] = None,
) -> Tuple[np.ndarray, np.ndarray, np.ndarray, float]:
  y_base = smooth_signal(y_ref, REFERENCE_SMOOTH_WINDOW)
  kappa_ref = smooth_signal(
    curvature_from_local_path(x_grid, y_base),
    CURVATURE_SMOOTH_WINDOW,
  )
  trust_horizon = control_trust_horizon(v, float(x_grid[-1]) if len(x_grid) else 0.0)
  if trust_horizon <= 0.0:
    return y_base, kappa_ref, kappa_ref, 0.0

  kappa_target = preview_shape_curvature(
    kappa_ref, v, x_grid,
    response_delay_s=response_delay_s,
    support_horizon_m=trust_horizon,
    confidence=confidence,
  )
  y_candidate = reconstruct_path_from_curvature_delta(kappa_target, kappa_ref, y_base, x_grid)
  y_candidate = clamp_path_delta(y_candidate, y_base, x_grid)
  full_effect = min(CONTROL_BLEND_FULL_M, max(8.0, 0.55 * trust_horizon))
  y_out = blend_to_reference(
    y_candidate, y_base, x_grid,
    full_effect_m=full_effect,
    zero_effect_m=trust_horizon,
    confidence=confidence,
  )
  y_out = smooth_signal(y_out, REFERENCE_SMOOTH_WINDOW)
  tail_ref = np.asarray(y_ref if tail_reference is None else tail_reference, dtype=np.float64)
  restore_start = max(8.0, trust_horizon - TAIL_REFERENCE_BLEND_MARGIN_M)
  restore_end = min(float(x_grid[-1]), trust_horizon + TAIL_REFERENCE_BLEND_MARGIN_M)
  y_out = blend_to_reference(
    y_out, tail_ref, x_grid,
    full_effect_m=restore_start,
    zero_effect_m=restore_end,
  )
  kappa_out = smooth_signal(
    curvature_from_local_path(x_grid, y_out),
    CURVATURE_SMOOTH_WINDOW,
  )
  return y_out, kappa_ref, kappa_out, trust_horizon


def proc_scalar_reference_distance(v: float, max_x: float) -> float:
  if max_x <= 0.0:
    return float(PROC_REF_MIN_DIST_M)
  target = max(PROC_REF_MIN_DIST_M, max(float(v), 0.0) * PROC_REF_PREVIEW_TIME_S)
  return float(min(max_x, target))


def scalar_reference_curvature(
    kappa: np.ndarray, x: np.ndarray, *, center_m: float,
    window_m: float = PROC_SCALAR_WINDOW_M,
) -> float:
  kappa_arr = np.asarray(kappa, dtype=np.float64)
  x_arr = np.asarray(x, dtype=np.float64)
  if kappa_arr.size == 0:
    return 0.0
  center = float(np.clip(center_m, float(x_arr[0]), float(x_arr[-1])))
  half = max(float(window_m) * 0.5, 0.25)
  mask = (x_arr >= center - half) & (x_arr <= center + half)
  if np.count_nonzero(mask) >= 2:
    distances = np.abs(x_arr[mask] - center)
    weights = np.maximum(1e-3, 1.0 - distances / half)
    return float(np.average(kappa_arr[mask], weights=weights))
  return float(np.interp(center, x_arr, kappa_arr))


def local_path_fit_curvature(
    x: np.ndarray, y: np.ndarray, *, center_m: float,
    window_m: float = PROC_SCALAR_FIT_WINDOW_M,
) -> float:
  x_arr = np.asarray(x, dtype=np.float64)
  y_arr = np.asarray(y, dtype=np.float64)
  if x_arr.size < PROC_SCALAR_MIN_POINTS:
    return 0.0
  center = float(np.clip(center_m, float(x_arr[0]), float(x_arr[-1])))
  half = max(float(window_m) * 0.5, 0.5)
  mask = (x_arr >= center - half) & (x_arr <= center + half)
  if np.count_nonzero(mask) < PROC_SCALAR_MIN_POINTS:
    nearest = np.argsort(np.abs(x_arr - center))[:PROC_SCALAR_MIN_POINTS]
    mask = np.zeros_like(x_arr, dtype=bool)
    mask[nearest] = True
  x_local = x_arr[mask] - center
  y_local = y_arr[mask]
  try:
    coeffs = np.polyfit(x_local, y_local, 2)
  except np.linalg.LinAlgError:
    return 0.0
  a, b, _ = coeffs
  denom = max((1.0 + float(b) ** 2) ** 1.5, 1e-9)
  return float(2.0 * a) / denom


def local_window_confidence(
    confidence: np.ndarray, x: np.ndarray, *, center_m: float,
    window_m: float = PROC_SCALAR_FIT_WINDOW_M,
) -> float:
  conf_arr = np.asarray(confidence, dtype=np.float64)
  x_arr = np.asarray(x, dtype=np.float64)
  if conf_arr.size == 0 or conf_arr.size != x_arr.size:
    return 1.0
  center = float(np.clip(center_m, float(x_arr[0]), float(x_arr[-1])))
  half = max(float(window_m) * 0.5, 0.5)
  mask = (x_arr >= center - half) & (x_arr <= center + half)
  if np.count_nonzero(mask) < 2:
    return float(np.clip(np.interp(center, x_arr, conf_arr), PATH_CONFIDENCE_FLOOR, 1.0))
  distances = np.abs(x_arr[mask] - center)
  weights = np.maximum(1e-3, 1.0 - distances / half)
  return float(np.clip(np.average(conf_arr[mask], weights=weights), PATH_CONFIDENCE_FLOOR, 1.0))


def hybrid_c_weight(
    x_grid: np.ndarray, y_preview: np.ndarray, y_fused: np.ndarray,
    *, contributors: int, local_confidence: float, center_m: float,
) -> float:
  support = np.clip((float(contributors) - 1.0) / C_SCALAR_FULL_SUPPORT_CONTRIBUTORS, 0.0, 1.0)
  near_limit = min(float(x_grid[-1]), max(12.0, float(center_m) + 4.0))
  mask = np.asarray(x_grid, dtype=np.float64) <= near_limit
  if np.count_nonzero(mask) < 3:
    agreement = 1.0
  else:
    mean_abs_delta = float(np.mean(np.abs(np.asarray(y_preview)[mask] - np.asarray(y_fused)[mask])))
    agreement = math.exp(-mean_abs_delta / HYBRID_PATH_AGREEMENT_DECAY_M)
  confidence = float(np.clip(local_confidence, PATH_CONFIDENCE_FLOOR, 1.0))
  weight_c = HYBRID_BASE_C_WEIGHT + HYBRID_SUPPORT_GAIN * support * confidence * agreement
  return float(np.clip(weight_c, HYBRID_MIN_C_WEIGHT, HYBRID_MAX_C_WEIGHT))


def stabilize_c_scalar_candidate(
    observed: float,
    prev_filtered: Optional[float],
    median_history: Deque[float],
    *, contributors: int, local_confidence: float,
    lane_change_active: bool = False,
) -> float:
  if lane_change_active:
    if prev_filtered is None or not math.isfinite(prev_filtered):
      return float(observed)
    alpha = LANE_CHANGE_SCALAR_ALPHA
    return float(prev_filtered + alpha * (float(observed) - prev_filtered))
  median_history.append(float(observed))
  median_observed = float(np.median(np.asarray(median_history, dtype=np.float64)))
  if prev_filtered is None or not math.isfinite(prev_filtered):
    return median_observed
  support = np.clip((float(contributors) - 1.0) / C_SCALAR_FULL_SUPPORT_CONTRIBUTORS, 0.0, 1.0)
  support *= float(np.clip(local_confidence, PATH_CONFIDENCE_FLOOR, 1.0))
  alpha = C_SCALAR_ALPHA_BASE + C_SCALAR_ALPHA_SUPPORT_GAIN * support
  return float(prev_filtered + alpha * (median_observed - prev_filtered))


def wrap_to_pi(angle: float) -> float:
  return math.atan2(math.sin(angle), math.cos(angle))


# ══════════════════════════════════════════════════════════════════
# Temporal BEV Path Fuser
# ══════════════════════════════════════════════════════════════════

class _PathRecord:
  __slots__ = ('t', 'x_local', 'y_local', 'confidence', 'global_x', 'global_y', 'global_psi')

  def __init__(self, t: float, x_local: np.ndarray, y_local: np.ndarray,
               confidence: np.ndarray, global_x: float, global_y: float,
               global_psi: float):
    self.t = t
    self.x_local = x_local
    self.y_local = y_local
    self.confidence = confidence
    self.global_x = global_x
    self.global_y = global_y
    self.global_psi = global_psi


class TemporalBEVPathFuser:
  def __init__(self, history_seconds: float = DEFAULT_FUSION_HISTORY_SECONDS):
    self.history_seconds = history_seconds
    self.history: Deque[_PathRecord] = deque()

  def clear(self) -> None:
    self.history.clear()

  def prune_to_seconds(self, current_t: float, max_age_s: float) -> None:
    cutoff = current_t - max_age_s
    while self.history and self.history[0].t < cutoff:
      self.history.popleft()

  def push(self, record: _PathRecord) -> None:
    self.history.append(record)
    while self.history and (record.t - self.history[0].t) > self.history_seconds:
      self.history.popleft()

  def fuse(self, record: _PathRecord, x_grid: np.ndarray) -> Tuple[np.ndarray, np.ndarray]:
    x_grid = np.asarray(x_grid, dtype=np.float64)
    candidates: list = []
    weights_list: list = []

    for h in self.history:
      xw, yw = self._warp(h, record)
      valid = xw > -2.0
      if np.count_nonzero(valid) < 4:
        continue
      yr, yr_valid = resample_to_grid_masked(xw[valid], yw[valid], x_grid)
      cr, _ = resample_to_grid_masked(xw[valid], h.confidence[valid], x_grid)
      age = record.t - h.t
      w_time = math.exp(-age / max(FUSION_TIME_DECAY_TAU, 1e-6))
      w_dist = np.exp(-np.maximum(x_grid, 0.0) / max(FUSION_DISTANCE_DECAY_TAU, 1e-6))
      w = w_time * w_dist * np.clip(cr, 0.0, 1.0) * yr_valid.astype(np.float64)
      candidates.append(yr)
      weights_list.append(w)

    if not candidates:
      return resample_to_grid(record.x_local, record.y_local, x_grid), np.ones(len(x_grid), dtype=bool)

    Y = np.stack(candidates, axis=0)
    W = np.stack(weights_list, axis=0)
    w_sum = np.sum(W, axis=0)

    y_raw_fallback = resample_to_grid(record.x_local, record.y_local, x_grid)
    no_coverage = w_sum < FUSION_MIN_WEIGHT_SUM

    y_est = np.sum(Y * W, axis=0) / np.maximum(w_sum, 1e-9)
    y_est[no_coverage] = y_raw_fallback[no_coverage]

    # Robust IRLS-style refinement
    gate = FUSION_ROBUST_GATE_BASE + FUSION_ROBUST_GATE_GAIN * np.maximum(x_grid, 0.0)
    for _ in range(3):
      resid = Y - y_est[None, :]
      gate_mask = (np.abs(resid) <= gate[None, :]).astype(np.float64)
      W2 = W * gate_mask
      denom = np.sum(W2, axis=0)
      covered = denom >= FUSION_MIN_WEIGHT_SUM
      y_est[covered] = np.sum(Y * W2, axis=0)[covered] / denom[covered]

    valid_out = ~no_coverage
    return self._smooth(y_est, coverage_mask=valid_out), valid_out

  @staticmethod
  def _warp(old: _PathRecord, cur: _PathRecord) -> Tuple[np.ndarray, np.ndarray]:
    co, so = math.cos(old.global_psi), math.sin(old.global_psi)
    xg = old.global_x + co * old.x_local - so * old.y_local
    yg = old.global_y + so * old.x_local + co * old.y_local
    cc, sc = math.cos(cur.global_psi), math.sin(cur.global_psi)
    dx = xg - cur.global_x
    dy = yg - cur.global_y
    x_cur = cc * dx + sc * dy
    y_cur = -sc * dx + cc * dy
    return x_cur, y_cur

  def _smooth(self, y: np.ndarray, *, coverage_mask: Optional[np.ndarray] = None) -> np.ndarray:
    window = FUSION_SMOOTH_WINDOW
    if window < 3:
      return y.copy()
    if window % 2 == 0:
      window += 1
    kernel = np.ones(window, dtype=np.float64)
    y_arr = np.asarray(y, dtype=np.float64)
    if coverage_mask is not None:
      w = np.asarray(coverage_mask, dtype=np.float64)
      numer = np.convolve(y_arr * w, kernel, mode="same")
      denom = np.convolve(w, kernel, mode="same")
      return np.where(denom > 0.5, numer / np.maximum(denom, 1e-9), y_arr)
    numer = np.convolve(y_arr, kernel, mode="same")
    denom = np.convolve(np.ones(len(y_arr), dtype=np.float64), kernel, mode="same")
    return numer / np.maximum(denom, 1e-9)


# ══════════════════════════════════════════════════════════════════
# Real-time Algorithm D Processor
# ══════════════════════════════════════════════════════════════════

class LateralPostProcessor:
  """Real-time Algorithm D (B + C Hybrid) lateral post-processor.

  Maintains state across frames for temporal fusion and dead reckoning.
  Call process() once per modelV2 frame.
  """

  def __init__(self):
    self.fuser = TemporalBEVPathFuser(DEFAULT_FUSION_HISTORY_SECONDS)

    # Dead-reckoning pose
    self.global_x: float = 0.0
    self.global_y: float = 0.0
    self.global_psi: float = 0.0
    self.prev_t: Optional[float] = None
    self.prev_pose_yaw: Optional[float] = None

    # Scalar stabilization state
    self.prev_proc_scalar_filtered: Optional[float] = None
    self.proc_scalar_history: Deque[float] = deque(maxlen=C_SCALAR_MEDIAN_WINDOW)

    # Lane-change state
    self.prev_blinker: bool = False

    # Cached grid
    self._x_grid: Optional[np.ndarray] = None
    self._grid_max_x: float = 0.0

  def _ensure_grid(self, max_x: float) -> np.ndarray:
    needed = max(MIN_PROCESSING_HORIZON_M, max_x)
    if self._x_grid is None or needed > self._grid_max_x + 1.0:
      self._x_grid = build_processing_grid(max_x)
      self._grid_max_x = needed
    return self._x_grid

  def _update_pose(self, t: float, v_ego: float,
                   pose_yaw: float, yaw_rate: float,
                   steering_angle_deg: float) -> Tuple[float, float, float]:
    """Dead-reckon global pose from ego motion."""
    if self.prev_t is not None:
      dt = t - self.prev_t
      if 0.0 < dt < 1.0:
        # Resolve yaw rate: livePose.yaw diff > yaw_rate > steering kinematic
        if math.isfinite(pose_yaw) and self.prev_pose_yaw is not None:
          new_psi = self.global_psi + wrap_to_pi(pose_yaw - self.prev_pose_yaw)
        elif math.isfinite(yaw_rate):
          new_psi = self.global_psi + yaw_rate * dt
        else:
          steer_rad = math.radians(steering_angle_deg / 15.0)
          yr = v_ego * math.tan(steer_rad) / WHEELBASE_M
          new_psi = self.global_psi + yr * dt

        psi_mid = 0.5 * (self.global_psi + new_psi)
        self.global_x += v_ego * math.cos(psi_mid) * dt
        self.global_y += v_ego * math.sin(psi_mid) * dt
        self.global_psi = new_psi

    if math.isfinite(pose_yaw):
      self.prev_pose_yaw = pose_yaw
    self.prev_t = t

    return self.global_x, self.global_y, self.global_psi

  def process(
      self,
      path_x: np.ndarray,
      path_y: np.ndarray,
      path_y_std: np.ndarray,
      v_ego: float,
      timestamp: float,
      pose_yaw: float,
      yaw_rate: float,
      steering_angle_deg: float,
      left_blinker: bool,
      right_blinker: bool,
      response_delay_s: float,
      roll: float,
  ) -> Optional[float]:
    """Process one frame and return the processed desired curvature, or None."""
    if len(path_x) < 5:
      return None

    # Lane-change detection
    blinker = left_blinker or right_blinker
    blinker_edge = blinker != self.prev_blinker
    if blinker_edge:
      self.fuser.clear()
      self.prev_proc_scalar_filtered = None
      self.proc_scalar_history.clear()
    self.prev_blinker = blinker

    max_x = max_finite_x(path_x)
    if max_x <= 0.0:
      return None

    x_grid = self._ensure_grid(max_x)
    v = max(v_ego, OPENPILOT_MIN_SPEED_MPS)
    scalar_ref_distance = proc_scalar_reference_distance(v, max_x)
    trust_horizon = control_trust_horizon(v, float(x_grid[-1]) if len(x_grid) else 0.0)

    # Confidence from path std
    path_conf = confidence_from_path_std(path_y_std, len(path_x))
    path_conf_grid = resample_to_grid(path_x, path_conf, x_grid)

    # ── B branch: single-frame preview shaping ──
    y_raw_grid = resample_to_grid(path_x, path_y, x_grid)
    y_preview = smooth_signal(y_raw_grid, REFERENCE_SMOOTH_WINDOW)

    # ── Dead-reckon pose and push to fusion ──
    gx, gy, gpsi = self._update_pose(timestamp, v_ego, pose_yaw, yaw_rate, steering_angle_deg)
    record = _PathRecord(
      t=timestamp,
      x_local=path_x.copy(),
      y_local=path_y.copy(),
      confidence=path_conf,
      global_x=gx, global_y=gy, global_psi=gpsi,
    )
    self.fuser.push(record)
    if blinker:
      self.fuser.prune_to_seconds(timestamp, LANE_CHANGE_FUSION_HISTORY_S)

    # ── C branch: temporal fusion ──
    y_fused, _ = self.fuser.fuse(record, x_grid)

    # ── D: hybrid blend ──
    local_conf = local_window_confidence(path_conf_grid, x_grid, center_m=scalar_ref_distance)
    num_contrib = len(self.fuser.history)
    weight_c = hybrid_c_weight(
      x_grid, y_preview, y_fused,
      contributors=num_contrib,
      local_confidence=local_conf,
      center_m=scalar_ref_distance,
    )
    y_hybrid = (1.0 - weight_c) * y_preview + weight_c * y_fused
    y_hybrid = smooth_signal(y_hybrid, REFERENCE_SMOOTH_WINDOW)

    # ── Curvature from hybrid path ──
    kappa_hybrid_base = clamp_kappa_beyond_horizon(
      smooth_signal(
        curvature_from_local_path(x_grid, y_hybrid),
        CURVATURE_SMOOTH_WINDOW,
      ),
      x_grid, max_x,
    )

    # ── Preview shaping on curvature ──
    if trust_horizon > 0.0:
      kappa_hybrid = clamp_kappa_beyond_horizon(
        preview_shape_curvature(
          kappa_hybrid_base, v, x_grid,
          response_delay_s=response_delay_s,
          support_horizon_m=trust_horizon,
          confidence=path_conf_grid,
          lookahead_scale=PREVIEW_LOOKAHEAD_SCALE,
        ),
        x_grid, max_x,
      )
    else:
      kappa_hybrid = kappa_hybrid_base

    # ── Extract scalar curvature ──
    proc_observed = scalar_reference_curvature(kappa_hybrid, x_grid, center_m=scalar_ref_distance)

    # ── Stabilize scalar (temporal median + EMA) ──
    proc_raw = stabilize_c_scalar_candidate(
      proc_observed,
      self.prev_proc_scalar_filtered,
      self.proc_scalar_history,
      contributors=num_contrib,
      local_confidence=local_conf,
      lane_change_active=blinker,
    )
    self.prev_proc_scalar_filtered = proc_raw

    return proc_raw


# ══════════════════════════════════════════════════════════════════
# Daemon entry point
# ══════════════════════════════════════════════════════════════════

def main():
  params = Params()
  cloudlog.info("lateral_postprocessd: waiting for CarParams")
  CP = messaging.log_from_bytes(params.get("CarParams", block=True), car.CarParams)
  cloudlog.info(f"lateral_postprocessd: got CarParams, fingerprint={CP.carFingerprint}")

  sm = messaging.SubMaster(
    ['modelV2', 'carState', 'livePose', 'liveDelay', 'selfdriveState'],
    poll='modelV2',
  )
  pm = messaging.PubMaster(['lateralManeuverPlan'])

  processor = LateralPostProcessor()

  rk = Ratekeeper(1.0 / DT_MDL, print_delay_threshold=None)  # 20 Hz

  while True:
    sm.update()

    if not sm.updated['modelV2']:
      rk.keep_time()
      continue

    model = sm['modelV2']
    cs = sm['carState']
    live_pose = sm['livePose']
    live_delay = sm['liveDelay']
    ss = sm['selfdriveState']

    # Extract path geometry from model
    pos = model.position
    path_x = np.array(pos.x, dtype=np.float64)
    path_y = np.array(pos.y, dtype=np.float64)
    path_y_std = np.array(pos.yStd, dtype=np.float64) if len(pos.yStd) > 0 else np.ones_like(path_y)

    v_ego = max(float(cs.vEgo), 0.0)
    timestamp = float(model.timestamp) * 1e-9 if model.timestamp > 0 else float(sm.logMonoTime['modelV2']) * 1e-9

    # livePose yaw and yaw rate
    pose_yaw = float(live_pose.orientationNED.z) if live_pose.orientationNED.valid else float('nan')
    yaw_rate = float(live_pose.angularVelocityDevice.z) if live_pose.angularVelocityDevice.valid else float('nan')
    steering_angle_deg = float(cs.steeringAngleDeg)

    # Blinkers
    left_blinker = bool(cs.leftBlinker)
    right_blinker = bool(cs.rightBlinker)

    # Response delay
    response_delay_s = DEFAULT_PREVIEW_RESPONSE_DELAY_S
    if sm.valid['liveDelay']:
      delay_val = float(live_delay.lateralDelay)
      if math.isfinite(delay_val) and delay_val >= 0.0:
        response_delay_s = float(np.clip(delay_val, 0.0, 0.60))

    # Roll from livePose
    roll = float(live_pose.orientationNED.x) if live_pose.orientationNED.valid else 0.0

    # Don't publish if not engaged
    enabled = bool(ss.enabled)

    proc_curvature = processor.process(
      path_x=path_x,
      path_y=path_y,
      path_y_std=path_y_std,
      v_ego=v_ego,
      timestamp=timestamp,
      pose_yaw=pose_yaw,
      yaw_rate=yaw_rate,
      steering_angle_deg=steering_angle_deg,
      left_blinker=left_blinker,
      right_blinker=right_blinker,
      response_delay_s=response_delay_s,
      roll=roll,
    )

    plan_msg = messaging.new_message('lateralManeuverPlan')

    if proc_curvature is not None and enabled and math.isfinite(proc_curvature):
      plan_msg.valid = True
      plan_msg.lateralManeuverPlan.desiredCurvature = float(proc_curvature)
    else:
      plan_msg.valid = False

    pm.send('lateralManeuverPlan', plan_msg)

    rk.keep_time()


if __name__ == "__main__":
  main()
