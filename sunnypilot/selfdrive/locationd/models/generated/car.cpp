#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3757951423899805493) {
   out_3757951423899805493[0] = delta_x[0] + nom_x[0];
   out_3757951423899805493[1] = delta_x[1] + nom_x[1];
   out_3757951423899805493[2] = delta_x[2] + nom_x[2];
   out_3757951423899805493[3] = delta_x[3] + nom_x[3];
   out_3757951423899805493[4] = delta_x[4] + nom_x[4];
   out_3757951423899805493[5] = delta_x[5] + nom_x[5];
   out_3757951423899805493[6] = delta_x[6] + nom_x[6];
   out_3757951423899805493[7] = delta_x[7] + nom_x[7];
   out_3757951423899805493[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1185494606804549419) {
   out_1185494606804549419[0] = -nom_x[0] + true_x[0];
   out_1185494606804549419[1] = -nom_x[1] + true_x[1];
   out_1185494606804549419[2] = -nom_x[2] + true_x[2];
   out_1185494606804549419[3] = -nom_x[3] + true_x[3];
   out_1185494606804549419[4] = -nom_x[4] + true_x[4];
   out_1185494606804549419[5] = -nom_x[5] + true_x[5];
   out_1185494606804549419[6] = -nom_x[6] + true_x[6];
   out_1185494606804549419[7] = -nom_x[7] + true_x[7];
   out_1185494606804549419[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1466697554802129451) {
   out_1466697554802129451[0] = 1.0;
   out_1466697554802129451[1] = 0.0;
   out_1466697554802129451[2] = 0.0;
   out_1466697554802129451[3] = 0.0;
   out_1466697554802129451[4] = 0.0;
   out_1466697554802129451[5] = 0.0;
   out_1466697554802129451[6] = 0.0;
   out_1466697554802129451[7] = 0.0;
   out_1466697554802129451[8] = 0.0;
   out_1466697554802129451[9] = 0.0;
   out_1466697554802129451[10] = 1.0;
   out_1466697554802129451[11] = 0.0;
   out_1466697554802129451[12] = 0.0;
   out_1466697554802129451[13] = 0.0;
   out_1466697554802129451[14] = 0.0;
   out_1466697554802129451[15] = 0.0;
   out_1466697554802129451[16] = 0.0;
   out_1466697554802129451[17] = 0.0;
   out_1466697554802129451[18] = 0.0;
   out_1466697554802129451[19] = 0.0;
   out_1466697554802129451[20] = 1.0;
   out_1466697554802129451[21] = 0.0;
   out_1466697554802129451[22] = 0.0;
   out_1466697554802129451[23] = 0.0;
   out_1466697554802129451[24] = 0.0;
   out_1466697554802129451[25] = 0.0;
   out_1466697554802129451[26] = 0.0;
   out_1466697554802129451[27] = 0.0;
   out_1466697554802129451[28] = 0.0;
   out_1466697554802129451[29] = 0.0;
   out_1466697554802129451[30] = 1.0;
   out_1466697554802129451[31] = 0.0;
   out_1466697554802129451[32] = 0.0;
   out_1466697554802129451[33] = 0.0;
   out_1466697554802129451[34] = 0.0;
   out_1466697554802129451[35] = 0.0;
   out_1466697554802129451[36] = 0.0;
   out_1466697554802129451[37] = 0.0;
   out_1466697554802129451[38] = 0.0;
   out_1466697554802129451[39] = 0.0;
   out_1466697554802129451[40] = 1.0;
   out_1466697554802129451[41] = 0.0;
   out_1466697554802129451[42] = 0.0;
   out_1466697554802129451[43] = 0.0;
   out_1466697554802129451[44] = 0.0;
   out_1466697554802129451[45] = 0.0;
   out_1466697554802129451[46] = 0.0;
   out_1466697554802129451[47] = 0.0;
   out_1466697554802129451[48] = 0.0;
   out_1466697554802129451[49] = 0.0;
   out_1466697554802129451[50] = 1.0;
   out_1466697554802129451[51] = 0.0;
   out_1466697554802129451[52] = 0.0;
   out_1466697554802129451[53] = 0.0;
   out_1466697554802129451[54] = 0.0;
   out_1466697554802129451[55] = 0.0;
   out_1466697554802129451[56] = 0.0;
   out_1466697554802129451[57] = 0.0;
   out_1466697554802129451[58] = 0.0;
   out_1466697554802129451[59] = 0.0;
   out_1466697554802129451[60] = 1.0;
   out_1466697554802129451[61] = 0.0;
   out_1466697554802129451[62] = 0.0;
   out_1466697554802129451[63] = 0.0;
   out_1466697554802129451[64] = 0.0;
   out_1466697554802129451[65] = 0.0;
   out_1466697554802129451[66] = 0.0;
   out_1466697554802129451[67] = 0.0;
   out_1466697554802129451[68] = 0.0;
   out_1466697554802129451[69] = 0.0;
   out_1466697554802129451[70] = 1.0;
   out_1466697554802129451[71] = 0.0;
   out_1466697554802129451[72] = 0.0;
   out_1466697554802129451[73] = 0.0;
   out_1466697554802129451[74] = 0.0;
   out_1466697554802129451[75] = 0.0;
   out_1466697554802129451[76] = 0.0;
   out_1466697554802129451[77] = 0.0;
   out_1466697554802129451[78] = 0.0;
   out_1466697554802129451[79] = 0.0;
   out_1466697554802129451[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4486103183427186323) {
   out_4486103183427186323[0] = state[0];
   out_4486103183427186323[1] = state[1];
   out_4486103183427186323[2] = state[2];
   out_4486103183427186323[3] = state[3];
   out_4486103183427186323[4] = state[4];
   out_4486103183427186323[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4486103183427186323[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4486103183427186323[7] = state[7];
   out_4486103183427186323[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1014623250982861925) {
   out_1014623250982861925[0] = 1;
   out_1014623250982861925[1] = 0;
   out_1014623250982861925[2] = 0;
   out_1014623250982861925[3] = 0;
   out_1014623250982861925[4] = 0;
   out_1014623250982861925[5] = 0;
   out_1014623250982861925[6] = 0;
   out_1014623250982861925[7] = 0;
   out_1014623250982861925[8] = 0;
   out_1014623250982861925[9] = 0;
   out_1014623250982861925[10] = 1;
   out_1014623250982861925[11] = 0;
   out_1014623250982861925[12] = 0;
   out_1014623250982861925[13] = 0;
   out_1014623250982861925[14] = 0;
   out_1014623250982861925[15] = 0;
   out_1014623250982861925[16] = 0;
   out_1014623250982861925[17] = 0;
   out_1014623250982861925[18] = 0;
   out_1014623250982861925[19] = 0;
   out_1014623250982861925[20] = 1;
   out_1014623250982861925[21] = 0;
   out_1014623250982861925[22] = 0;
   out_1014623250982861925[23] = 0;
   out_1014623250982861925[24] = 0;
   out_1014623250982861925[25] = 0;
   out_1014623250982861925[26] = 0;
   out_1014623250982861925[27] = 0;
   out_1014623250982861925[28] = 0;
   out_1014623250982861925[29] = 0;
   out_1014623250982861925[30] = 1;
   out_1014623250982861925[31] = 0;
   out_1014623250982861925[32] = 0;
   out_1014623250982861925[33] = 0;
   out_1014623250982861925[34] = 0;
   out_1014623250982861925[35] = 0;
   out_1014623250982861925[36] = 0;
   out_1014623250982861925[37] = 0;
   out_1014623250982861925[38] = 0;
   out_1014623250982861925[39] = 0;
   out_1014623250982861925[40] = 1;
   out_1014623250982861925[41] = 0;
   out_1014623250982861925[42] = 0;
   out_1014623250982861925[43] = 0;
   out_1014623250982861925[44] = 0;
   out_1014623250982861925[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1014623250982861925[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1014623250982861925[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1014623250982861925[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1014623250982861925[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1014623250982861925[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1014623250982861925[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1014623250982861925[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1014623250982861925[53] = -9.8100000000000005*dt;
   out_1014623250982861925[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1014623250982861925[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1014623250982861925[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1014623250982861925[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1014623250982861925[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1014623250982861925[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1014623250982861925[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1014623250982861925[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1014623250982861925[62] = 0;
   out_1014623250982861925[63] = 0;
   out_1014623250982861925[64] = 0;
   out_1014623250982861925[65] = 0;
   out_1014623250982861925[66] = 0;
   out_1014623250982861925[67] = 0;
   out_1014623250982861925[68] = 0;
   out_1014623250982861925[69] = 0;
   out_1014623250982861925[70] = 1;
   out_1014623250982861925[71] = 0;
   out_1014623250982861925[72] = 0;
   out_1014623250982861925[73] = 0;
   out_1014623250982861925[74] = 0;
   out_1014623250982861925[75] = 0;
   out_1014623250982861925[76] = 0;
   out_1014623250982861925[77] = 0;
   out_1014623250982861925[78] = 0;
   out_1014623250982861925[79] = 0;
   out_1014623250982861925[80] = 1;
}
void h_25(double *state, double *unused, double *out_2787905945015027630) {
   out_2787905945015027630[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6454640478171730354) {
   out_6454640478171730354[0] = 0;
   out_6454640478171730354[1] = 0;
   out_6454640478171730354[2] = 0;
   out_6454640478171730354[3] = 0;
   out_6454640478171730354[4] = 0;
   out_6454640478171730354[5] = 0;
   out_6454640478171730354[6] = 1;
   out_6454640478171730354[7] = 0;
   out_6454640478171730354[8] = 0;
}
void h_24(double *state, double *unused, double *out_3318247152895617041) {
   out_3318247152895617041[0] = state[4];
   out_3318247152895617041[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8434177996735498126) {
   out_8434177996735498126[0] = 0;
   out_8434177996735498126[1] = 0;
   out_8434177996735498126[2] = 0;
   out_8434177996735498126[3] = 0;
   out_8434177996735498126[4] = 1;
   out_8434177996735498126[5] = 0;
   out_8434177996735498126[6] = 0;
   out_8434177996735498126[7] = 0;
   out_8434177996735498126[8] = 0;
   out_8434177996735498126[9] = 0;
   out_8434177996735498126[10] = 0;
   out_8434177996735498126[11] = 0;
   out_8434177996735498126[12] = 0;
   out_8434177996735498126[13] = 0;
   out_8434177996735498126[14] = 1;
   out_8434177996735498126[15] = 0;
   out_8434177996735498126[16] = 0;
   out_8434177996735498126[17] = 0;
}
void h_30(double *state, double *unused, double *out_3063100007299533519) {
   out_3063100007299533519[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8972973436678978981) {
   out_8972973436678978981[0] = 0;
   out_8972973436678978981[1] = 0;
   out_8972973436678978981[2] = 0;
   out_8972973436678978981[3] = 0;
   out_8972973436678978981[4] = 1;
   out_8972973436678978981[5] = 0;
   out_8972973436678978981[6] = 0;
   out_8972973436678978981[7] = 0;
   out_8972973436678978981[8] = 0;
}
void h_26(double *state, double *unused, double *out_1583171902725186559) {
   out_1583171902725186559[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2713137159297674130) {
   out_2713137159297674130[0] = 0;
   out_2713137159297674130[1] = 0;
   out_2713137159297674130[2] = 0;
   out_2713137159297674130[3] = 0;
   out_2713137159297674130[4] = 0;
   out_2713137159297674130[5] = 0;
   out_2713137159297674130[6] = 0;
   out_2713137159297674130[7] = 1;
   out_2713137159297674130[8] = 0;
}
void h_27(double *state, double *unused, double *out_6638294716254047544) {
   out_6638294716254047544[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4150538219228065373) {
   out_4150538219228065373[0] = 0;
   out_4150538219228065373[1] = 0;
   out_4150538219228065373[2] = 0;
   out_4150538219228065373[3] = 1;
   out_4150538219228065373[4] = 0;
   out_4150538219228065373[5] = 0;
   out_4150538219228065373[6] = 0;
   out_4150538219228065373[7] = 0;
   out_4150538219228065373[8] = 0;
}
void h_29(double *state, double *unused, double *out_4045184100634831631) {
   out_4045184100634831631[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2437175492358514340) {
   out_2437175492358514340[0] = 0;
   out_2437175492358514340[1] = 1;
   out_2437175492358514340[2] = 0;
   out_2437175492358514340[3] = 0;
   out_2437175492358514340[4] = 0;
   out_2437175492358514340[5] = 0;
   out_2437175492358514340[6] = 0;
   out_2437175492358514340[7] = 0;
   out_2437175492358514340[8] = 0;
}
void h_28(double *state, double *unused, double *out_5409407840041654926) {
   out_5409407840041654926[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4400805763923840591) {
   out_4400805763923840591[0] = 1;
   out_4400805763923840591[1] = 0;
   out_4400805763923840591[2] = 0;
   out_4400805763923840591[3] = 0;
   out_4400805763923840591[4] = 0;
   out_4400805763923840591[5] = 0;
   out_4400805763923840591[6] = 0;
   out_4400805763923840591[7] = 0;
   out_4400805763923840591[8] = 0;
}
void h_31(double *state, double *unused, double *out_2945092613366156775) {
   out_2945092613366156775[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2086929057064322654) {
   out_2086929057064322654[0] = 0;
   out_2086929057064322654[1] = 0;
   out_2086929057064322654[2] = 0;
   out_2086929057064322654[3] = 0;
   out_2086929057064322654[4] = 0;
   out_2086929057064322654[5] = 0;
   out_2086929057064322654[6] = 0;
   out_2086929057064322654[7] = 0;
   out_2086929057064322654[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_3757951423899805493) {
  err_fun(nom_x, delta_x, out_3757951423899805493);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1185494606804549419) {
  inv_err_fun(nom_x, true_x, out_1185494606804549419);
}
void car_H_mod_fun(double *state, double *out_1466697554802129451) {
  H_mod_fun(state, out_1466697554802129451);
}
void car_f_fun(double *state, double dt, double *out_4486103183427186323) {
  f_fun(state,  dt, out_4486103183427186323);
}
void car_F_fun(double *state, double dt, double *out_1014623250982861925) {
  F_fun(state,  dt, out_1014623250982861925);
}
void car_h_25(double *state, double *unused, double *out_2787905945015027630) {
  h_25(state, unused, out_2787905945015027630);
}
void car_H_25(double *state, double *unused, double *out_6454640478171730354) {
  H_25(state, unused, out_6454640478171730354);
}
void car_h_24(double *state, double *unused, double *out_3318247152895617041) {
  h_24(state, unused, out_3318247152895617041);
}
void car_H_24(double *state, double *unused, double *out_8434177996735498126) {
  H_24(state, unused, out_8434177996735498126);
}
void car_h_30(double *state, double *unused, double *out_3063100007299533519) {
  h_30(state, unused, out_3063100007299533519);
}
void car_H_30(double *state, double *unused, double *out_8972973436678978981) {
  H_30(state, unused, out_8972973436678978981);
}
void car_h_26(double *state, double *unused, double *out_1583171902725186559) {
  h_26(state, unused, out_1583171902725186559);
}
void car_H_26(double *state, double *unused, double *out_2713137159297674130) {
  H_26(state, unused, out_2713137159297674130);
}
void car_h_27(double *state, double *unused, double *out_6638294716254047544) {
  h_27(state, unused, out_6638294716254047544);
}
void car_H_27(double *state, double *unused, double *out_4150538219228065373) {
  H_27(state, unused, out_4150538219228065373);
}
void car_h_29(double *state, double *unused, double *out_4045184100634831631) {
  h_29(state, unused, out_4045184100634831631);
}
void car_H_29(double *state, double *unused, double *out_2437175492358514340) {
  H_29(state, unused, out_2437175492358514340);
}
void car_h_28(double *state, double *unused, double *out_5409407840041654926) {
  h_28(state, unused, out_5409407840041654926);
}
void car_H_28(double *state, double *unused, double *out_4400805763923840591) {
  H_28(state, unused, out_4400805763923840591);
}
void car_h_31(double *state, double *unused, double *out_2945092613366156775) {
  h_31(state, unused, out_2945092613366156775);
}
void car_H_31(double *state, double *unused, double *out_2086929057064322654) {
  H_31(state, unused, out_2086929057064322654);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
