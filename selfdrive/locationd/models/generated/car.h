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
void car_err_fun(double *nom_x, double *delta_x, double *out_5891821101885730116);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6203099983276503616);
void car_H_mod_fun(double *state, double *out_1158501590184924800);
void car_f_fun(double *state, double dt, double *out_2960540939665683529);
void car_F_fun(double *state, double dt, double *out_3433503983489643706);
void car_h_25(double *state, double *unused, double *out_5763669702333400970);
void car_H_25(double *state, double *unused, double *out_3745190234999740040);
void car_h_24(double *state, double *unused, double *out_27122391976433345);
void car_H_24(double *state, double *unused, double *out_1123624630027966812);
void car_h_30(double *state, double *unused, double *out_5606483033982271825);
void car_H_30(double *state, double *unused, double *out_782506095127868158);
void car_h_26(double *state, double *unused, double *out_6549992886883934260);
void car_H_26(double *state, double *unused, double *out_3686916125683816);
void car_h_27(double *state, double *unused, double *out_2726883650889068285);
void car_H_27(double *state, double *unused, double *out_2957269406928293069);
void car_h_29(double *state, double *unused, double *out_3002077713173574174);
void car_H_29(double *state, double *unused, double *out_272274750813475974);
void car_h_28(double *state, double *unused, double *out_3031101263104669671);
void car_H_28(double *state, double *unused, double *out_1691355520751850277);
void car_h_31(double *state, double *unused, double *out_5222515607127262321);
void car_H_31(double *state, double *unused, double *out_622521186107667660);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}