#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_1368921087911862561);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5068271539113922038);
void car_H_mod_fun(double *state, double *out_6583180257677944448);
void car_f_fun(double *state, double dt, double *out_4660837736289282129);
void car_F_fun(double *state, double dt, double *out_6235844391847691033);
void car_h_25(double *state, double *unused, double *out_2251326960498493501);
void car_H_25(double *state, double *unused, double *out_7458489002016947428);
void car_h_24(double *state, double *unused, double *out_6394965051889365613);
void car_H_24(double *state, double *unused, double *out_7430329472890281052);
void car_h_30(double *state, double *unused, double *out_6388550516220048383);
void car_H_30(double *state, double *unused, double *out_8469922113185355561);
void car_h_26(double *state, double *unused, double *out_2331220623150867177);
void car_H_26(double *state, double *unused, double *out_7683729101931803587);
void car_h_27(double *state, double *unused, double *out_7894056831579450336);
void car_H_27(double *state, double *unused, double *out_7802058648723771144);
void car_h_29(double *state, double *unused, double *out_1243660453104400846);
void car_H_29(double *state, double *unused, double *out_7959690768870963377);
void car_h_28(double *state, double *unused, double *out_3836726938510269130);
void car_H_28(double *state, double *unused, double *out_5404654287769057665);
void car_h_31(double *state, double *unused, double *out_1976132898213987612);
void car_H_31(double *state, double *unused, double *out_8309937204165155063);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}