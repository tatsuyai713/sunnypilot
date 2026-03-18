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
void err_fun(double *nom_x, double *delta_x, double *out_1368921087911862561) {
   out_1368921087911862561[0] = delta_x[0] + nom_x[0];
   out_1368921087911862561[1] = delta_x[1] + nom_x[1];
   out_1368921087911862561[2] = delta_x[2] + nom_x[2];
   out_1368921087911862561[3] = delta_x[3] + nom_x[3];
   out_1368921087911862561[4] = delta_x[4] + nom_x[4];
   out_1368921087911862561[5] = delta_x[5] + nom_x[5];
   out_1368921087911862561[6] = delta_x[6] + nom_x[6];
   out_1368921087911862561[7] = delta_x[7] + nom_x[7];
   out_1368921087911862561[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5068271539113922038) {
   out_5068271539113922038[0] = -nom_x[0] + true_x[0];
   out_5068271539113922038[1] = -nom_x[1] + true_x[1];
   out_5068271539113922038[2] = -nom_x[2] + true_x[2];
   out_5068271539113922038[3] = -nom_x[3] + true_x[3];
   out_5068271539113922038[4] = -nom_x[4] + true_x[4];
   out_5068271539113922038[5] = -nom_x[5] + true_x[5];
   out_5068271539113922038[6] = -nom_x[6] + true_x[6];
   out_5068271539113922038[7] = -nom_x[7] + true_x[7];
   out_5068271539113922038[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6583180257677944448) {
   out_6583180257677944448[0] = 1.0;
   out_6583180257677944448[1] = 0.0;
   out_6583180257677944448[2] = 0.0;
   out_6583180257677944448[3] = 0.0;
   out_6583180257677944448[4] = 0.0;
   out_6583180257677944448[5] = 0.0;
   out_6583180257677944448[6] = 0.0;
   out_6583180257677944448[7] = 0.0;
   out_6583180257677944448[8] = 0.0;
   out_6583180257677944448[9] = 0.0;
   out_6583180257677944448[10] = 1.0;
   out_6583180257677944448[11] = 0.0;
   out_6583180257677944448[12] = 0.0;
   out_6583180257677944448[13] = 0.0;
   out_6583180257677944448[14] = 0.0;
   out_6583180257677944448[15] = 0.0;
   out_6583180257677944448[16] = 0.0;
   out_6583180257677944448[17] = 0.0;
   out_6583180257677944448[18] = 0.0;
   out_6583180257677944448[19] = 0.0;
   out_6583180257677944448[20] = 1.0;
   out_6583180257677944448[21] = 0.0;
   out_6583180257677944448[22] = 0.0;
   out_6583180257677944448[23] = 0.0;
   out_6583180257677944448[24] = 0.0;
   out_6583180257677944448[25] = 0.0;
   out_6583180257677944448[26] = 0.0;
   out_6583180257677944448[27] = 0.0;
   out_6583180257677944448[28] = 0.0;
   out_6583180257677944448[29] = 0.0;
   out_6583180257677944448[30] = 1.0;
   out_6583180257677944448[31] = 0.0;
   out_6583180257677944448[32] = 0.0;
   out_6583180257677944448[33] = 0.0;
   out_6583180257677944448[34] = 0.0;
   out_6583180257677944448[35] = 0.0;
   out_6583180257677944448[36] = 0.0;
   out_6583180257677944448[37] = 0.0;
   out_6583180257677944448[38] = 0.0;
   out_6583180257677944448[39] = 0.0;
   out_6583180257677944448[40] = 1.0;
   out_6583180257677944448[41] = 0.0;
   out_6583180257677944448[42] = 0.0;
   out_6583180257677944448[43] = 0.0;
   out_6583180257677944448[44] = 0.0;
   out_6583180257677944448[45] = 0.0;
   out_6583180257677944448[46] = 0.0;
   out_6583180257677944448[47] = 0.0;
   out_6583180257677944448[48] = 0.0;
   out_6583180257677944448[49] = 0.0;
   out_6583180257677944448[50] = 1.0;
   out_6583180257677944448[51] = 0.0;
   out_6583180257677944448[52] = 0.0;
   out_6583180257677944448[53] = 0.0;
   out_6583180257677944448[54] = 0.0;
   out_6583180257677944448[55] = 0.0;
   out_6583180257677944448[56] = 0.0;
   out_6583180257677944448[57] = 0.0;
   out_6583180257677944448[58] = 0.0;
   out_6583180257677944448[59] = 0.0;
   out_6583180257677944448[60] = 1.0;
   out_6583180257677944448[61] = 0.0;
   out_6583180257677944448[62] = 0.0;
   out_6583180257677944448[63] = 0.0;
   out_6583180257677944448[64] = 0.0;
   out_6583180257677944448[65] = 0.0;
   out_6583180257677944448[66] = 0.0;
   out_6583180257677944448[67] = 0.0;
   out_6583180257677944448[68] = 0.0;
   out_6583180257677944448[69] = 0.0;
   out_6583180257677944448[70] = 1.0;
   out_6583180257677944448[71] = 0.0;
   out_6583180257677944448[72] = 0.0;
   out_6583180257677944448[73] = 0.0;
   out_6583180257677944448[74] = 0.0;
   out_6583180257677944448[75] = 0.0;
   out_6583180257677944448[76] = 0.0;
   out_6583180257677944448[77] = 0.0;
   out_6583180257677944448[78] = 0.0;
   out_6583180257677944448[79] = 0.0;
   out_6583180257677944448[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4660837736289282129) {
   out_4660837736289282129[0] = state[0];
   out_4660837736289282129[1] = state[1];
   out_4660837736289282129[2] = state[2];
   out_4660837736289282129[3] = state[3];
   out_4660837736289282129[4] = state[4];
   out_4660837736289282129[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4660837736289282129[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4660837736289282129[7] = state[7];
   out_4660837736289282129[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6235844391847691033) {
   out_6235844391847691033[0] = 1;
   out_6235844391847691033[1] = 0;
   out_6235844391847691033[2] = 0;
   out_6235844391847691033[3] = 0;
   out_6235844391847691033[4] = 0;
   out_6235844391847691033[5] = 0;
   out_6235844391847691033[6] = 0;
   out_6235844391847691033[7] = 0;
   out_6235844391847691033[8] = 0;
   out_6235844391847691033[9] = 0;
   out_6235844391847691033[10] = 1;
   out_6235844391847691033[11] = 0;
   out_6235844391847691033[12] = 0;
   out_6235844391847691033[13] = 0;
   out_6235844391847691033[14] = 0;
   out_6235844391847691033[15] = 0;
   out_6235844391847691033[16] = 0;
   out_6235844391847691033[17] = 0;
   out_6235844391847691033[18] = 0;
   out_6235844391847691033[19] = 0;
   out_6235844391847691033[20] = 1;
   out_6235844391847691033[21] = 0;
   out_6235844391847691033[22] = 0;
   out_6235844391847691033[23] = 0;
   out_6235844391847691033[24] = 0;
   out_6235844391847691033[25] = 0;
   out_6235844391847691033[26] = 0;
   out_6235844391847691033[27] = 0;
   out_6235844391847691033[28] = 0;
   out_6235844391847691033[29] = 0;
   out_6235844391847691033[30] = 1;
   out_6235844391847691033[31] = 0;
   out_6235844391847691033[32] = 0;
   out_6235844391847691033[33] = 0;
   out_6235844391847691033[34] = 0;
   out_6235844391847691033[35] = 0;
   out_6235844391847691033[36] = 0;
   out_6235844391847691033[37] = 0;
   out_6235844391847691033[38] = 0;
   out_6235844391847691033[39] = 0;
   out_6235844391847691033[40] = 1;
   out_6235844391847691033[41] = 0;
   out_6235844391847691033[42] = 0;
   out_6235844391847691033[43] = 0;
   out_6235844391847691033[44] = 0;
   out_6235844391847691033[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6235844391847691033[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6235844391847691033[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6235844391847691033[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6235844391847691033[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6235844391847691033[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6235844391847691033[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6235844391847691033[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6235844391847691033[53] = -9.8100000000000005*dt;
   out_6235844391847691033[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6235844391847691033[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6235844391847691033[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6235844391847691033[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6235844391847691033[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6235844391847691033[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6235844391847691033[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6235844391847691033[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6235844391847691033[62] = 0;
   out_6235844391847691033[63] = 0;
   out_6235844391847691033[64] = 0;
   out_6235844391847691033[65] = 0;
   out_6235844391847691033[66] = 0;
   out_6235844391847691033[67] = 0;
   out_6235844391847691033[68] = 0;
   out_6235844391847691033[69] = 0;
   out_6235844391847691033[70] = 1;
   out_6235844391847691033[71] = 0;
   out_6235844391847691033[72] = 0;
   out_6235844391847691033[73] = 0;
   out_6235844391847691033[74] = 0;
   out_6235844391847691033[75] = 0;
   out_6235844391847691033[76] = 0;
   out_6235844391847691033[77] = 0;
   out_6235844391847691033[78] = 0;
   out_6235844391847691033[79] = 0;
   out_6235844391847691033[80] = 1;
}
void h_25(double *state, double *unused, double *out_2251326960498493501) {
   out_2251326960498493501[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7458489002016947428) {
   out_7458489002016947428[0] = 0;
   out_7458489002016947428[1] = 0;
   out_7458489002016947428[2] = 0;
   out_7458489002016947428[3] = 0;
   out_7458489002016947428[4] = 0;
   out_7458489002016947428[5] = 0;
   out_7458489002016947428[6] = 1;
   out_7458489002016947428[7] = 0;
   out_7458489002016947428[8] = 0;
}
void h_24(double *state, double *unused, double *out_6394965051889365613) {
   out_6394965051889365613[0] = state[4];
   out_6394965051889365613[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7430329472890281052) {
   out_7430329472890281052[0] = 0;
   out_7430329472890281052[1] = 0;
   out_7430329472890281052[2] = 0;
   out_7430329472890281052[3] = 0;
   out_7430329472890281052[4] = 1;
   out_7430329472890281052[5] = 0;
   out_7430329472890281052[6] = 0;
   out_7430329472890281052[7] = 0;
   out_7430329472890281052[8] = 0;
   out_7430329472890281052[9] = 0;
   out_7430329472890281052[10] = 0;
   out_7430329472890281052[11] = 0;
   out_7430329472890281052[12] = 0;
   out_7430329472890281052[13] = 0;
   out_7430329472890281052[14] = 1;
   out_7430329472890281052[15] = 0;
   out_7430329472890281052[16] = 0;
   out_7430329472890281052[17] = 0;
}
void h_30(double *state, double *unused, double *out_6388550516220048383) {
   out_6388550516220048383[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8469922113185355561) {
   out_8469922113185355561[0] = 0;
   out_8469922113185355561[1] = 0;
   out_8469922113185355561[2] = 0;
   out_8469922113185355561[3] = 0;
   out_8469922113185355561[4] = 1;
   out_8469922113185355561[5] = 0;
   out_8469922113185355561[6] = 0;
   out_8469922113185355561[7] = 0;
   out_8469922113185355561[8] = 0;
}
void h_26(double *state, double *unused, double *out_2331220623150867177) {
   out_2331220623150867177[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7683729101931803587) {
   out_7683729101931803587[0] = 0;
   out_7683729101931803587[1] = 0;
   out_7683729101931803587[2] = 0;
   out_7683729101931803587[3] = 0;
   out_7683729101931803587[4] = 0;
   out_7683729101931803587[5] = 0;
   out_7683729101931803587[6] = 0;
   out_7683729101931803587[7] = 1;
   out_7683729101931803587[8] = 0;
}
void h_27(double *state, double *unused, double *out_7894056831579450336) {
   out_7894056831579450336[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7802058648723771144) {
   out_7802058648723771144[0] = 0;
   out_7802058648723771144[1] = 0;
   out_7802058648723771144[2] = 0;
   out_7802058648723771144[3] = 1;
   out_7802058648723771144[4] = 0;
   out_7802058648723771144[5] = 0;
   out_7802058648723771144[6] = 0;
   out_7802058648723771144[7] = 0;
   out_7802058648723771144[8] = 0;
}
void h_29(double *state, double *unused, double *out_1243660453104400846) {
   out_1243660453104400846[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7959690768870963377) {
   out_7959690768870963377[0] = 0;
   out_7959690768870963377[1] = 1;
   out_7959690768870963377[2] = 0;
   out_7959690768870963377[3] = 0;
   out_7959690768870963377[4] = 0;
   out_7959690768870963377[5] = 0;
   out_7959690768870963377[6] = 0;
   out_7959690768870963377[7] = 0;
   out_7959690768870963377[8] = 0;
}
void h_28(double *state, double *unused, double *out_3836726938510269130) {
   out_3836726938510269130[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5404654287769057665) {
   out_5404654287769057665[0] = 1;
   out_5404654287769057665[1] = 0;
   out_5404654287769057665[2] = 0;
   out_5404654287769057665[3] = 0;
   out_5404654287769057665[4] = 0;
   out_5404654287769057665[5] = 0;
   out_5404654287769057665[6] = 0;
   out_5404654287769057665[7] = 0;
   out_5404654287769057665[8] = 0;
}
void h_31(double *state, double *unused, double *out_1976132898213987612) {
   out_1976132898213987612[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8309937204165155063) {
   out_8309937204165155063[0] = 0;
   out_8309937204165155063[1] = 0;
   out_8309937204165155063[2] = 0;
   out_8309937204165155063[3] = 0;
   out_8309937204165155063[4] = 0;
   out_8309937204165155063[5] = 0;
   out_8309937204165155063[6] = 0;
   out_8309937204165155063[7] = 0;
   out_8309937204165155063[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_1368921087911862561) {
  err_fun(nom_x, delta_x, out_1368921087911862561);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5068271539113922038) {
  inv_err_fun(nom_x, true_x, out_5068271539113922038);
}
void car_H_mod_fun(double *state, double *out_6583180257677944448) {
  H_mod_fun(state, out_6583180257677944448);
}
void car_f_fun(double *state, double dt, double *out_4660837736289282129) {
  f_fun(state,  dt, out_4660837736289282129);
}
void car_F_fun(double *state, double dt, double *out_6235844391847691033) {
  F_fun(state,  dt, out_6235844391847691033);
}
void car_h_25(double *state, double *unused, double *out_2251326960498493501) {
  h_25(state, unused, out_2251326960498493501);
}
void car_H_25(double *state, double *unused, double *out_7458489002016947428) {
  H_25(state, unused, out_7458489002016947428);
}
void car_h_24(double *state, double *unused, double *out_6394965051889365613) {
  h_24(state, unused, out_6394965051889365613);
}
void car_H_24(double *state, double *unused, double *out_7430329472890281052) {
  H_24(state, unused, out_7430329472890281052);
}
void car_h_30(double *state, double *unused, double *out_6388550516220048383) {
  h_30(state, unused, out_6388550516220048383);
}
void car_H_30(double *state, double *unused, double *out_8469922113185355561) {
  H_30(state, unused, out_8469922113185355561);
}
void car_h_26(double *state, double *unused, double *out_2331220623150867177) {
  h_26(state, unused, out_2331220623150867177);
}
void car_H_26(double *state, double *unused, double *out_7683729101931803587) {
  H_26(state, unused, out_7683729101931803587);
}
void car_h_27(double *state, double *unused, double *out_7894056831579450336) {
  h_27(state, unused, out_7894056831579450336);
}
void car_H_27(double *state, double *unused, double *out_7802058648723771144) {
  H_27(state, unused, out_7802058648723771144);
}
void car_h_29(double *state, double *unused, double *out_1243660453104400846) {
  h_29(state, unused, out_1243660453104400846);
}
void car_H_29(double *state, double *unused, double *out_7959690768870963377) {
  H_29(state, unused, out_7959690768870963377);
}
void car_h_28(double *state, double *unused, double *out_3836726938510269130) {
  h_28(state, unused, out_3836726938510269130);
}
void car_H_28(double *state, double *unused, double *out_5404654287769057665) {
  H_28(state, unused, out_5404654287769057665);
}
void car_h_31(double *state, double *unused, double *out_1976132898213987612) {
  h_31(state, unused, out_1976132898213987612);
}
void car_H_31(double *state, double *unused, double *out_8309937204165155063) {
  H_31(state, unused, out_8309937204165155063);
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
