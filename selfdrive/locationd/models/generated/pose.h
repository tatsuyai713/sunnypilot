#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3763521124081322775);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_177812529109460282);
void pose_H_mod_fun(double *state, double *out_6160206684466877958);
void pose_f_fun(double *state, double dt, double *out_4800341315034629509);
void pose_F_fun(double *state, double dt, double *out_2115414934888159835);
void pose_h_4(double *state, double *unused, double *out_2892054295359636963);
void pose_H_4(double *state, double *unused, double *out_4086232505269448891);
void pose_h_10(double *state, double *unused, double *out_1520403981462315862);
void pose_H_10(double *state, double *unused, double *out_944059824953988773);
void pose_h_13(double *state, double *unused, double *out_7929828547441307226);
void pose_H_13(double *state, double *unused, double *out_3524398703047252038);
void pose_h_14(double *state, double *unused, double *out_4827639347712724102);
void pose_H_14(double *state, double *unused, double *out_122991648929964362);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}