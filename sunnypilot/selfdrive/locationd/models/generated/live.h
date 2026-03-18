#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_3099509702336473725);
void live_err_fun(double *nom_x, double *delta_x, double *out_8097947864915477351);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_6659728705815909442);
void live_H_mod_fun(double *state, double *out_7683720194163876812);
void live_f_fun(double *state, double dt, double *out_4276576548120489665);
void live_F_fun(double *state, double dt, double *out_9042179027035700236);
void live_h_4(double *state, double *unused, double *out_8699187418404914402);
void live_H_4(double *state, double *unused, double *out_2103185673164991017);
void live_h_9(double *state, double *unused, double *out_2682481178180639851);
void live_H_9(double *state, double *unused, double *out_2344375319794581662);
void live_h_10(double *state, double *unused, double *out_4595898332515769219);
void live_H_10(double *state, double *unused, double *out_8448509587531445202);
void live_h_12(double *state, double *unused, double *out_2977365880817805739);
void live_H_12(double *state, double *unused, double *out_7122642081196952812);
void live_h_35(double *state, double *unused, double *out_8539469877558759811);
void live_H_35(double *state, double *unused, double *out_8578538960187585095);
void live_h_32(double *state, double *unused, double *out_7268329618323729799);
void live_H_32(double *state, double *unused, double *out_2953340609827850165);
void live_h_13(double *state, double *unused, double *out_7236993971345680375);
void live_H_13(double *state, double *unused, double *out_6074626252534009767);
void live_h_14(double *state, double *unused, double *out_2682481178180639851);
void live_H_14(double *state, double *unused, double *out_2344375319794581662);
void live_h_33(double *state, double *unused, double *out_9132950199813792637);
void live_H_33(double *state, double *unused, double *out_5427981955548727491);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}