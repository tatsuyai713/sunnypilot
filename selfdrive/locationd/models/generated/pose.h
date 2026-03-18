#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7475867757860580655);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6907412215356863750);
void pose_H_mod_fun(double *state, double *out_3605623673578465873);
void pose_f_fun(double *state, double dt, double *out_8195462837691250934);
void pose_F_fun(double *state, double dt, double *out_613318021964956292);
void pose_h_4(double *state, double *unused, double *out_7408733835662868600);
void pose_H_4(double *state, double *unused, double *out_166183536265441699);
void pose_h_10(double *state, double *unused, double *out_5309858706066724578);
void pose_H_10(double *state, double *unused, double *out_4037125241597057406);
void pose_h_13(double *state, double *unused, double *out_7326591431181517962);
void pose_H_13(double *state, double *unused, double *out_3378457361597774500);
void pose_h_14(double *state, double *unused, double *out_153623312624921138);
void pose_H_14(double *state, double *unused, double *out_4129424392604926228);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}