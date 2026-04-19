# Lateral Path Post-Processing (Algorithm D) — 使い方ガイド

## 概要

この機能は、openpilot のニューラルネットモデルが出力する横方向経路データを後処理し、
ステアリング制御の安定性と応答性を向上させます。

### Algorithm D (B + C ハイブリッド) とは

モデルは毎フレーム (20Hz) 前方の走行経路を予測しますが、フレーム間で経路が微妙に振動し、
ステアリングのジッター（小刻みなブレ）が発生することがあります。

Algorithm D は **2つのアプローチのいいとこ取り** をしたハイブリッド方式です:

| ブランチ | 名前 | 特長 |
|---------|------|------|
| **B** | Stable Preview | 単一フレームのプレビュー曲率整形。アクチュエータ遅延を補償する先読み処理。**応答性が高い** |
| **C** | Motion-Aligned Fusion | 過去のフレームの経路をデッドレコニングで現在座標に変換し時空間融合。**安定性が高い** |
| **D** | B + C Hybrid | BとCを融合支持度・信頼度・経路一致度で加重ブレンド |

```
modelV2.position (x, y, yStd)  ← モデルの経路予測
        │
        ▼
  ┌─────────────────────────────┐
  │   lateral_postprocessd      │
  │                             │
  │  B: プレビュー曲率整形      │──┐
  │  C: 時空間融合             │──┤
  │  D: ハイブリッドブレンド    │◄─┘
  │                             │
  │  → 曲率スカラーを抽出       │
  └─────────┬───────────────────┘
            │
            ▼
  lateralManeuverPlan.desiredCurvature (20Hz)
            │
            ▼
  controlsd.py (clip_curvature → actuators)
```

---

## インストール方法

### 方法 1: comma 3X の標準インストール画面から（推奨）

1. このブランチを自分の GitHub フォークにプッシュ:
   ```bash
   git push <あなたのリモート名> feature/lateral-postprocess-d
   ```

2. comma 3X で **設定 → ソフトウェア → Uninstall** を実行（既にインストール済みの場合）

3. 初期セットアップ画面で **Custom Software** を選択

4. 以下の形式で URL を入力:
   ```
   https://installer.comma.ai/<GitHubユーザー名>/sunnypilot/feature--lateral-postprocess-d
   ```
   > **注意**: ブランチ名の `/` は `--` に置き換えてください

5. インストール完了後、自動的に再起動されます

### 方法 2: SSH 経由（開発者向け）

```bash
ssh comma@<デバイスIP>
cd /data/openpilot
git remote add myrepo https://github.com/<GitHubユーザー名>/sunnypilot.git
git fetch myrepo feature/lateral-postprocess-d
git checkout feature/lateral-postprocess-d
sudo reboot
```

---

## 有効化 / 無効化

### GUI から（推奨）

1. comma 3X の画面で **設定** を開く
2. **sunnypilot** タブ → **Steering** パネルを選択
3. 一番下にある **「Lateral Path Post-Processing」** トグルを ON/OFF

> ⚠️ **トグルはオフロード（停車中）時のみ切り替え可能です**

### SSH から（開発者向け）

```bash
# 有効化
python3 -c "from openpilot.common.params import Params; Params().put_bool('LateralPostProcessEnabled', True)"

# 無効化
python3 -c "from openpilot.common.params import Params; Params().put_bool('LateralPostProcessEnabled', False)"

# 現在の状態を確認
python3 -c "from openpilot.common.params import Params; print(Params().get_bool('LateralPostProcessEnabled'))"
```

変更後は再起動してください:
```bash
sudo reboot
```

---

## 動作確認

### プロセスが起動しているか確認

```bash
ssh comma@<デバイスIP>
tmux a
# lateral_postprocessd のウィンドウがあるか確認
```

または:
```bash
ps aux | grep lateral_postprocessd
```

### ログで確認

起動時に以下のログが出力されます:
```
lateral_postprocessd: waiting for CarParams
lateral_postprocessd: got CarParams, fingerprint=TOYOTA_COROLLA_TSS2
```

---

## 変更ファイル一覧

| ファイル | 内容 |
|---------|------|
| `sunnypilot/selfdrive/controls/lateral_postprocessd.py` | Algorithm D のリアルタイムデーモン（新規） |
| `common/params_keys.h` | `LateralPostProcessEnabled` パラメータ登録 |
| `openpilot/common/params_keys.h` | 同上（ミラーファイル） |
| `system/manager/process_config.py` | プロセス登録 + 起動条件 |
| `selfdrive/ui/sunnypilot/layouts/settings/steering.py` | GUI トグル追加 |

---

## 注意事項

- **`LateralManeuverMode`（テスト用ツール）と同時に有効にしないでください。**
  両方とも `lateralManeuverPlan` メッセージを publish するため競合します。

- この機能は `modelV2.position` (x, y 座標) から独自に曲率を計算し、
  モデル標準の `modelV2.action.desiredCurvature`（ヨー角ベース）を置き換えます。

- トグルを OFF にすると、プロセスは自動停止し、
  `controlsd` は通常通り `modelV2.action.desiredCurvature` にフォールバックします。

- 設定は `PERSISTENT | BACKUP` フラグ付きのため、再起動やソフトウェアアップデート後も保持されます。

---

## アルゴリズムの主要パラメータ

現在のパラメータはコード内で固定されています（`lateral_postprocessd.py` 冒頭の定数）:

| パラメータ | 値 | 説明 |
|-----------|-----|------|
| `DEFAULT_PREVIEW_RESPONSE_DELAY_S` | 0.18 s | プレビュー先読みの応答遅延（liveDelay 優先） |
| `DEFAULT_FUSION_HISTORY_SECONDS` | 1.2 s | 時空間融合の履歴ウィンドウ |
| `PREVIEW_LOOKAHEAD_SCALE` | 1.0 | プレビュー先読み倍率 |
| `HYBRID_BASE_C_WEIGHT` | 0.10 | Cブランチの基本重み |
| `HYBRID_MAX_C_WEIGHT` | 0.85 | Cブランチの最大重み |
| `CONTROL_HORIZON_BASE_M` | 10.0 m | 信頼ホライズン基底距離 |
| `CONTROL_HORIZON_SPEED_GAIN` | 1.15 | 速度に応じたホライズン拡大ゲイン |

---

## トラブルシューティング

| 症状 | 対処 |
|------|------|
| トグルが見つからない | Settings → sunnypilot → Steering の一番下を確認 |
| トグルがグレーアウト | 停車してオフロードにしてから操作 |
| プロセスが起動しない | `LateralPostProcessEnabled` が True か確認。`tmux` でエラーログを確認 |
| ステアリング挙動が変わらない | `controlsd` が `lateralManeuverPlan` を受信しているか確認。`selfdriveState.enabled` が True であること |
| `lateralManeuversd` との競合 | `LateralManeuverMode` を OFF にしてください |
