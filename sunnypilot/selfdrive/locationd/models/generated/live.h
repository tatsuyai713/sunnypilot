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
void live_H(double *in_vec, double *out_394001088320882255);
void live_err_fun(double *nom_x, double *delta_x, double *out_8256788261500104656);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_4894298477896884618);
void live_H_mod_fun(double *state, double *out_6041622406962490376);
void live_f_fun(double *state, double dt, double *out_3111445859680897380);
void live_F_fun(double *state, double dt, double *out_6402686530602650807);
void live_h_4(double *state, double *unused, double *out_3359507408849440277);
void live_H_4(double *state, double *unused, double *out_4678583156868782662);
void live_h_9(double *state, double *unused, double *out_5773706798608287354);
void live_H_9(double *state, double *unused, double *out_4437393510239192017);
void live_h_10(double *state, double *unused, double *out_5073176063187299258);
void live_H_10(double *state, double *unused, double *out_2607083428249116619);
void live_h_12(double *state, double *unused, double *out_3994365302805524332);
void live_H_12(double *state, double *unused, double *out_4057484131821188995);
void live_h_35(double *state, double *unused, double *out_7524966619659876061);
void live_H_35(double *state, double *unused, double *out_1311921099496175286);
void live_h_32(double *state, double *unused, double *out_2144116385554268400);
void live_H_32(double *state, double *unused, double *out_8517766353557099132);
void live_h_13(double *state, double *unused, double *out_8991776402620587462);
void live_H_13(double *state, double *unused, double *out_6565621764661758674);
void live_h_14(double *state, double *unused, double *out_5773706798608287354);
void live_H_14(double *state, double *unused, double *out_4437393510239192017);
void live_h_33(double *state, double *unused, double *out_7543367792528458580);
void live_H_33(double *state, double *unused, double *out_1838635905142682318);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}