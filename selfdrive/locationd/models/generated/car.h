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
void car_err_fun(double *nom_x, double *delta_x, double *out_2642664406632120816);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8668876234455005345);
void car_H_mod_fun(double *state, double *out_5722998466790378124);
void car_f_fun(double *state, double dt, double *out_6187952112751757232);
void car_F_fun(double *state, double dt, double *out_3020272003759919908);
void car_h_25(double *state, double *unused, double *out_7087525484569157169);
void car_H_25(double *state, double *unused, double *out_928167623862509015);
void car_h_24(double *state, double *unused, double *out_4610318856001482860);
void car_H_24(double *state, double *unused, double *out_1244481975142990551);
void car_h_30(double *state, double *unused, double *out_3866898611560766707);
void car_H_30(double *state, double *unused, double *out_3446500582369757642);
void car_h_26(double *state, double *unused, double *out_871247437946047223);
void car_H_26(double *state, double *unused, double *out_2813335695011547209);
void car_h_27(double *state, double *unused, double *out_989254831879423967);
void car_H_27(double *state, double *unused, double *out_1271737270569332731);
void car_h_29(double *state, double *unused, double *out_1775831259520190128);
void car_H_29(double *state, double *unused, double *out_3956731926684149826);
void car_h_28(double *state, double *unused, double *out_6631984702960380802);
void car_H_28(double *state, double *unused, double *out_1125667090385380748);
void car_h_31(double *state, double *unused, double *out_3750846821039250763);
void car_H_31(double *state, double *unused, double *out_3439543797244898685);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}