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
void err_fun(double *nom_x, double *delta_x, double *out_5891821101885730116) {
   out_5891821101885730116[0] = delta_x[0] + nom_x[0];
   out_5891821101885730116[1] = delta_x[1] + nom_x[1];
   out_5891821101885730116[2] = delta_x[2] + nom_x[2];
   out_5891821101885730116[3] = delta_x[3] + nom_x[3];
   out_5891821101885730116[4] = delta_x[4] + nom_x[4];
   out_5891821101885730116[5] = delta_x[5] + nom_x[5];
   out_5891821101885730116[6] = delta_x[6] + nom_x[6];
   out_5891821101885730116[7] = delta_x[7] + nom_x[7];
   out_5891821101885730116[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6203099983276503616) {
   out_6203099983276503616[0] = -nom_x[0] + true_x[0];
   out_6203099983276503616[1] = -nom_x[1] + true_x[1];
   out_6203099983276503616[2] = -nom_x[2] + true_x[2];
   out_6203099983276503616[3] = -nom_x[3] + true_x[3];
   out_6203099983276503616[4] = -nom_x[4] + true_x[4];
   out_6203099983276503616[5] = -nom_x[5] + true_x[5];
   out_6203099983276503616[6] = -nom_x[6] + true_x[6];
   out_6203099983276503616[7] = -nom_x[7] + true_x[7];
   out_6203099983276503616[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1158501590184924800) {
   out_1158501590184924800[0] = 1.0;
   out_1158501590184924800[1] = 0.0;
   out_1158501590184924800[2] = 0.0;
   out_1158501590184924800[3] = 0.0;
   out_1158501590184924800[4] = 0.0;
   out_1158501590184924800[5] = 0.0;
   out_1158501590184924800[6] = 0.0;
   out_1158501590184924800[7] = 0.0;
   out_1158501590184924800[8] = 0.0;
   out_1158501590184924800[9] = 0.0;
   out_1158501590184924800[10] = 1.0;
   out_1158501590184924800[11] = 0.0;
   out_1158501590184924800[12] = 0.0;
   out_1158501590184924800[13] = 0.0;
   out_1158501590184924800[14] = 0.0;
   out_1158501590184924800[15] = 0.0;
   out_1158501590184924800[16] = 0.0;
   out_1158501590184924800[17] = 0.0;
   out_1158501590184924800[18] = 0.0;
   out_1158501590184924800[19] = 0.0;
   out_1158501590184924800[20] = 1.0;
   out_1158501590184924800[21] = 0.0;
   out_1158501590184924800[22] = 0.0;
   out_1158501590184924800[23] = 0.0;
   out_1158501590184924800[24] = 0.0;
   out_1158501590184924800[25] = 0.0;
   out_1158501590184924800[26] = 0.0;
   out_1158501590184924800[27] = 0.0;
   out_1158501590184924800[28] = 0.0;
   out_1158501590184924800[29] = 0.0;
   out_1158501590184924800[30] = 1.0;
   out_1158501590184924800[31] = 0.0;
   out_1158501590184924800[32] = 0.0;
   out_1158501590184924800[33] = 0.0;
   out_1158501590184924800[34] = 0.0;
   out_1158501590184924800[35] = 0.0;
   out_1158501590184924800[36] = 0.0;
   out_1158501590184924800[37] = 0.0;
   out_1158501590184924800[38] = 0.0;
   out_1158501590184924800[39] = 0.0;
   out_1158501590184924800[40] = 1.0;
   out_1158501590184924800[41] = 0.0;
   out_1158501590184924800[42] = 0.0;
   out_1158501590184924800[43] = 0.0;
   out_1158501590184924800[44] = 0.0;
   out_1158501590184924800[45] = 0.0;
   out_1158501590184924800[46] = 0.0;
   out_1158501590184924800[47] = 0.0;
   out_1158501590184924800[48] = 0.0;
   out_1158501590184924800[49] = 0.0;
   out_1158501590184924800[50] = 1.0;
   out_1158501590184924800[51] = 0.0;
   out_1158501590184924800[52] = 0.0;
   out_1158501590184924800[53] = 0.0;
   out_1158501590184924800[54] = 0.0;
   out_1158501590184924800[55] = 0.0;
   out_1158501590184924800[56] = 0.0;
   out_1158501590184924800[57] = 0.0;
   out_1158501590184924800[58] = 0.0;
   out_1158501590184924800[59] = 0.0;
   out_1158501590184924800[60] = 1.0;
   out_1158501590184924800[61] = 0.0;
   out_1158501590184924800[62] = 0.0;
   out_1158501590184924800[63] = 0.0;
   out_1158501590184924800[64] = 0.0;
   out_1158501590184924800[65] = 0.0;
   out_1158501590184924800[66] = 0.0;
   out_1158501590184924800[67] = 0.0;
   out_1158501590184924800[68] = 0.0;
   out_1158501590184924800[69] = 0.0;
   out_1158501590184924800[70] = 1.0;
   out_1158501590184924800[71] = 0.0;
   out_1158501590184924800[72] = 0.0;
   out_1158501590184924800[73] = 0.0;
   out_1158501590184924800[74] = 0.0;
   out_1158501590184924800[75] = 0.0;
   out_1158501590184924800[76] = 0.0;
   out_1158501590184924800[77] = 0.0;
   out_1158501590184924800[78] = 0.0;
   out_1158501590184924800[79] = 0.0;
   out_1158501590184924800[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2960540939665683529) {
   out_2960540939665683529[0] = state[0];
   out_2960540939665683529[1] = state[1];
   out_2960540939665683529[2] = state[2];
   out_2960540939665683529[3] = state[3];
   out_2960540939665683529[4] = state[4];
   out_2960540939665683529[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2960540939665683529[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2960540939665683529[7] = state[7];
   out_2960540939665683529[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3433503983489643706) {
   out_3433503983489643706[0] = 1;
   out_3433503983489643706[1] = 0;
   out_3433503983489643706[2] = 0;
   out_3433503983489643706[3] = 0;
   out_3433503983489643706[4] = 0;
   out_3433503983489643706[5] = 0;
   out_3433503983489643706[6] = 0;
   out_3433503983489643706[7] = 0;
   out_3433503983489643706[8] = 0;
   out_3433503983489643706[9] = 0;
   out_3433503983489643706[10] = 1;
   out_3433503983489643706[11] = 0;
   out_3433503983489643706[12] = 0;
   out_3433503983489643706[13] = 0;
   out_3433503983489643706[14] = 0;
   out_3433503983489643706[15] = 0;
   out_3433503983489643706[16] = 0;
   out_3433503983489643706[17] = 0;
   out_3433503983489643706[18] = 0;
   out_3433503983489643706[19] = 0;
   out_3433503983489643706[20] = 1;
   out_3433503983489643706[21] = 0;
   out_3433503983489643706[22] = 0;
   out_3433503983489643706[23] = 0;
   out_3433503983489643706[24] = 0;
   out_3433503983489643706[25] = 0;
   out_3433503983489643706[26] = 0;
   out_3433503983489643706[27] = 0;
   out_3433503983489643706[28] = 0;
   out_3433503983489643706[29] = 0;
   out_3433503983489643706[30] = 1;
   out_3433503983489643706[31] = 0;
   out_3433503983489643706[32] = 0;
   out_3433503983489643706[33] = 0;
   out_3433503983489643706[34] = 0;
   out_3433503983489643706[35] = 0;
   out_3433503983489643706[36] = 0;
   out_3433503983489643706[37] = 0;
   out_3433503983489643706[38] = 0;
   out_3433503983489643706[39] = 0;
   out_3433503983489643706[40] = 1;
   out_3433503983489643706[41] = 0;
   out_3433503983489643706[42] = 0;
   out_3433503983489643706[43] = 0;
   out_3433503983489643706[44] = 0;
   out_3433503983489643706[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3433503983489643706[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3433503983489643706[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3433503983489643706[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3433503983489643706[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3433503983489643706[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3433503983489643706[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3433503983489643706[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3433503983489643706[53] = -9.8100000000000005*dt;
   out_3433503983489643706[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3433503983489643706[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3433503983489643706[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3433503983489643706[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3433503983489643706[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3433503983489643706[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3433503983489643706[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3433503983489643706[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3433503983489643706[62] = 0;
   out_3433503983489643706[63] = 0;
   out_3433503983489643706[64] = 0;
   out_3433503983489643706[65] = 0;
   out_3433503983489643706[66] = 0;
   out_3433503983489643706[67] = 0;
   out_3433503983489643706[68] = 0;
   out_3433503983489643706[69] = 0;
   out_3433503983489643706[70] = 1;
   out_3433503983489643706[71] = 0;
   out_3433503983489643706[72] = 0;
   out_3433503983489643706[73] = 0;
   out_3433503983489643706[74] = 0;
   out_3433503983489643706[75] = 0;
   out_3433503983489643706[76] = 0;
   out_3433503983489643706[77] = 0;
   out_3433503983489643706[78] = 0;
   out_3433503983489643706[79] = 0;
   out_3433503983489643706[80] = 1;
}
void h_25(double *state, double *unused, double *out_5763669702333400970) {
   out_5763669702333400970[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3745190234999740040) {
   out_3745190234999740040[0] = 0;
   out_3745190234999740040[1] = 0;
   out_3745190234999740040[2] = 0;
   out_3745190234999740040[3] = 0;
   out_3745190234999740040[4] = 0;
   out_3745190234999740040[5] = 0;
   out_3745190234999740040[6] = 1;
   out_3745190234999740040[7] = 0;
   out_3745190234999740040[8] = 0;
}
void h_24(double *state, double *unused, double *out_27122391976433345) {
   out_27122391976433345[0] = state[4];
   out_27122391976433345[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1123624630027966812) {
   out_1123624630027966812[0] = 0;
   out_1123624630027966812[1] = 0;
   out_1123624630027966812[2] = 0;
   out_1123624630027966812[3] = 0;
   out_1123624630027966812[4] = 1;
   out_1123624630027966812[5] = 0;
   out_1123624630027966812[6] = 0;
   out_1123624630027966812[7] = 0;
   out_1123624630027966812[8] = 0;
   out_1123624630027966812[9] = 0;
   out_1123624630027966812[10] = 0;
   out_1123624630027966812[11] = 0;
   out_1123624630027966812[12] = 0;
   out_1123624630027966812[13] = 0;
   out_1123624630027966812[14] = 1;
   out_1123624630027966812[15] = 0;
   out_1123624630027966812[16] = 0;
   out_1123624630027966812[17] = 0;
}
void h_30(double *state, double *unused, double *out_5606483033982271825) {
   out_5606483033982271825[0] = state[4];
}
void H_30(double *state, double *unused, double *out_782506095127868158) {
   out_782506095127868158[0] = 0;
   out_782506095127868158[1] = 0;
   out_782506095127868158[2] = 0;
   out_782506095127868158[3] = 0;
   out_782506095127868158[4] = 1;
   out_782506095127868158[5] = 0;
   out_782506095127868158[6] = 0;
   out_782506095127868158[7] = 0;
   out_782506095127868158[8] = 0;
}
void h_26(double *state, double *unused, double *out_6549992886883934260) {
   out_6549992886883934260[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3686916125683816) {
   out_3686916125683816[0] = 0;
   out_3686916125683816[1] = 0;
   out_3686916125683816[2] = 0;
   out_3686916125683816[3] = 0;
   out_3686916125683816[4] = 0;
   out_3686916125683816[5] = 0;
   out_3686916125683816[6] = 0;
   out_3686916125683816[7] = 1;
   out_3686916125683816[8] = 0;
}
void h_27(double *state, double *unused, double *out_2726883650889068285) {
   out_2726883650889068285[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2957269406928293069) {
   out_2957269406928293069[0] = 0;
   out_2957269406928293069[1] = 0;
   out_2957269406928293069[2] = 0;
   out_2957269406928293069[3] = 1;
   out_2957269406928293069[4] = 0;
   out_2957269406928293069[5] = 0;
   out_2957269406928293069[6] = 0;
   out_2957269406928293069[7] = 0;
   out_2957269406928293069[8] = 0;
}
void h_29(double *state, double *unused, double *out_3002077713173574174) {
   out_3002077713173574174[0] = state[1];
}
void H_29(double *state, double *unused, double *out_272274750813475974) {
   out_272274750813475974[0] = 0;
   out_272274750813475974[1] = 1;
   out_272274750813475974[2] = 0;
   out_272274750813475974[3] = 0;
   out_272274750813475974[4] = 0;
   out_272274750813475974[5] = 0;
   out_272274750813475974[6] = 0;
   out_272274750813475974[7] = 0;
   out_272274750813475974[8] = 0;
}
void h_28(double *state, double *unused, double *out_3031101263104669671) {
   out_3031101263104669671[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1691355520751850277) {
   out_1691355520751850277[0] = 1;
   out_1691355520751850277[1] = 0;
   out_1691355520751850277[2] = 0;
   out_1691355520751850277[3] = 0;
   out_1691355520751850277[4] = 0;
   out_1691355520751850277[5] = 0;
   out_1691355520751850277[6] = 0;
   out_1691355520751850277[7] = 0;
   out_1691355520751850277[8] = 0;
}
void h_31(double *state, double *unused, double *out_5222515607127262321) {
   out_5222515607127262321[0] = state[8];
}
void H_31(double *state, double *unused, double *out_622521186107667660) {
   out_622521186107667660[0] = 0;
   out_622521186107667660[1] = 0;
   out_622521186107667660[2] = 0;
   out_622521186107667660[3] = 0;
   out_622521186107667660[4] = 0;
   out_622521186107667660[5] = 0;
   out_622521186107667660[6] = 0;
   out_622521186107667660[7] = 0;
   out_622521186107667660[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5891821101885730116) {
  err_fun(nom_x, delta_x, out_5891821101885730116);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6203099983276503616) {
  inv_err_fun(nom_x, true_x, out_6203099983276503616);
}
void car_H_mod_fun(double *state, double *out_1158501590184924800) {
  H_mod_fun(state, out_1158501590184924800);
}
void car_f_fun(double *state, double dt, double *out_2960540939665683529) {
  f_fun(state,  dt, out_2960540939665683529);
}
void car_F_fun(double *state, double dt, double *out_3433503983489643706) {
  F_fun(state,  dt, out_3433503983489643706);
}
void car_h_25(double *state, double *unused, double *out_5763669702333400970) {
  h_25(state, unused, out_5763669702333400970);
}
void car_H_25(double *state, double *unused, double *out_3745190234999740040) {
  H_25(state, unused, out_3745190234999740040);
}
void car_h_24(double *state, double *unused, double *out_27122391976433345) {
  h_24(state, unused, out_27122391976433345);
}
void car_H_24(double *state, double *unused, double *out_1123624630027966812) {
  H_24(state, unused, out_1123624630027966812);
}
void car_h_30(double *state, double *unused, double *out_5606483033982271825) {
  h_30(state, unused, out_5606483033982271825);
}
void car_H_30(double *state, double *unused, double *out_782506095127868158) {
  H_30(state, unused, out_782506095127868158);
}
void car_h_26(double *state, double *unused, double *out_6549992886883934260) {
  h_26(state, unused, out_6549992886883934260);
}
void car_H_26(double *state, double *unused, double *out_3686916125683816) {
  H_26(state, unused, out_3686916125683816);
}
void car_h_27(double *state, double *unused, double *out_2726883650889068285) {
  h_27(state, unused, out_2726883650889068285);
}
void car_H_27(double *state, double *unused, double *out_2957269406928293069) {
  H_27(state, unused, out_2957269406928293069);
}
void car_h_29(double *state, double *unused, double *out_3002077713173574174) {
  h_29(state, unused, out_3002077713173574174);
}
void car_H_29(double *state, double *unused, double *out_272274750813475974) {
  H_29(state, unused, out_272274750813475974);
}
void car_h_28(double *state, double *unused, double *out_3031101263104669671) {
  h_28(state, unused, out_3031101263104669671);
}
void car_H_28(double *state, double *unused, double *out_1691355520751850277) {
  H_28(state, unused, out_1691355520751850277);
}
void car_h_31(double *state, double *unused, double *out_5222515607127262321) {
  h_31(state, unused, out_5222515607127262321);
}
void car_H_31(double *state, double *unused, double *out_622521186107667660) {
  H_31(state, unused, out_622521186107667660);
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
