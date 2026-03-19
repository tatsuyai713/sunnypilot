#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3763521124081322775) {
   out_3763521124081322775[0] = delta_x[0] + nom_x[0];
   out_3763521124081322775[1] = delta_x[1] + nom_x[1];
   out_3763521124081322775[2] = delta_x[2] + nom_x[2];
   out_3763521124081322775[3] = delta_x[3] + nom_x[3];
   out_3763521124081322775[4] = delta_x[4] + nom_x[4];
   out_3763521124081322775[5] = delta_x[5] + nom_x[5];
   out_3763521124081322775[6] = delta_x[6] + nom_x[6];
   out_3763521124081322775[7] = delta_x[7] + nom_x[7];
   out_3763521124081322775[8] = delta_x[8] + nom_x[8];
   out_3763521124081322775[9] = delta_x[9] + nom_x[9];
   out_3763521124081322775[10] = delta_x[10] + nom_x[10];
   out_3763521124081322775[11] = delta_x[11] + nom_x[11];
   out_3763521124081322775[12] = delta_x[12] + nom_x[12];
   out_3763521124081322775[13] = delta_x[13] + nom_x[13];
   out_3763521124081322775[14] = delta_x[14] + nom_x[14];
   out_3763521124081322775[15] = delta_x[15] + nom_x[15];
   out_3763521124081322775[16] = delta_x[16] + nom_x[16];
   out_3763521124081322775[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_177812529109460282) {
   out_177812529109460282[0] = -nom_x[0] + true_x[0];
   out_177812529109460282[1] = -nom_x[1] + true_x[1];
   out_177812529109460282[2] = -nom_x[2] + true_x[2];
   out_177812529109460282[3] = -nom_x[3] + true_x[3];
   out_177812529109460282[4] = -nom_x[4] + true_x[4];
   out_177812529109460282[5] = -nom_x[5] + true_x[5];
   out_177812529109460282[6] = -nom_x[6] + true_x[6];
   out_177812529109460282[7] = -nom_x[7] + true_x[7];
   out_177812529109460282[8] = -nom_x[8] + true_x[8];
   out_177812529109460282[9] = -nom_x[9] + true_x[9];
   out_177812529109460282[10] = -nom_x[10] + true_x[10];
   out_177812529109460282[11] = -nom_x[11] + true_x[11];
   out_177812529109460282[12] = -nom_x[12] + true_x[12];
   out_177812529109460282[13] = -nom_x[13] + true_x[13];
   out_177812529109460282[14] = -nom_x[14] + true_x[14];
   out_177812529109460282[15] = -nom_x[15] + true_x[15];
   out_177812529109460282[16] = -nom_x[16] + true_x[16];
   out_177812529109460282[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6160206684466877958) {
   out_6160206684466877958[0] = 1.0;
   out_6160206684466877958[1] = 0.0;
   out_6160206684466877958[2] = 0.0;
   out_6160206684466877958[3] = 0.0;
   out_6160206684466877958[4] = 0.0;
   out_6160206684466877958[5] = 0.0;
   out_6160206684466877958[6] = 0.0;
   out_6160206684466877958[7] = 0.0;
   out_6160206684466877958[8] = 0.0;
   out_6160206684466877958[9] = 0.0;
   out_6160206684466877958[10] = 0.0;
   out_6160206684466877958[11] = 0.0;
   out_6160206684466877958[12] = 0.0;
   out_6160206684466877958[13] = 0.0;
   out_6160206684466877958[14] = 0.0;
   out_6160206684466877958[15] = 0.0;
   out_6160206684466877958[16] = 0.0;
   out_6160206684466877958[17] = 0.0;
   out_6160206684466877958[18] = 0.0;
   out_6160206684466877958[19] = 1.0;
   out_6160206684466877958[20] = 0.0;
   out_6160206684466877958[21] = 0.0;
   out_6160206684466877958[22] = 0.0;
   out_6160206684466877958[23] = 0.0;
   out_6160206684466877958[24] = 0.0;
   out_6160206684466877958[25] = 0.0;
   out_6160206684466877958[26] = 0.0;
   out_6160206684466877958[27] = 0.0;
   out_6160206684466877958[28] = 0.0;
   out_6160206684466877958[29] = 0.0;
   out_6160206684466877958[30] = 0.0;
   out_6160206684466877958[31] = 0.0;
   out_6160206684466877958[32] = 0.0;
   out_6160206684466877958[33] = 0.0;
   out_6160206684466877958[34] = 0.0;
   out_6160206684466877958[35] = 0.0;
   out_6160206684466877958[36] = 0.0;
   out_6160206684466877958[37] = 0.0;
   out_6160206684466877958[38] = 1.0;
   out_6160206684466877958[39] = 0.0;
   out_6160206684466877958[40] = 0.0;
   out_6160206684466877958[41] = 0.0;
   out_6160206684466877958[42] = 0.0;
   out_6160206684466877958[43] = 0.0;
   out_6160206684466877958[44] = 0.0;
   out_6160206684466877958[45] = 0.0;
   out_6160206684466877958[46] = 0.0;
   out_6160206684466877958[47] = 0.0;
   out_6160206684466877958[48] = 0.0;
   out_6160206684466877958[49] = 0.0;
   out_6160206684466877958[50] = 0.0;
   out_6160206684466877958[51] = 0.0;
   out_6160206684466877958[52] = 0.0;
   out_6160206684466877958[53] = 0.0;
   out_6160206684466877958[54] = 0.0;
   out_6160206684466877958[55] = 0.0;
   out_6160206684466877958[56] = 0.0;
   out_6160206684466877958[57] = 1.0;
   out_6160206684466877958[58] = 0.0;
   out_6160206684466877958[59] = 0.0;
   out_6160206684466877958[60] = 0.0;
   out_6160206684466877958[61] = 0.0;
   out_6160206684466877958[62] = 0.0;
   out_6160206684466877958[63] = 0.0;
   out_6160206684466877958[64] = 0.0;
   out_6160206684466877958[65] = 0.0;
   out_6160206684466877958[66] = 0.0;
   out_6160206684466877958[67] = 0.0;
   out_6160206684466877958[68] = 0.0;
   out_6160206684466877958[69] = 0.0;
   out_6160206684466877958[70] = 0.0;
   out_6160206684466877958[71] = 0.0;
   out_6160206684466877958[72] = 0.0;
   out_6160206684466877958[73] = 0.0;
   out_6160206684466877958[74] = 0.0;
   out_6160206684466877958[75] = 0.0;
   out_6160206684466877958[76] = 1.0;
   out_6160206684466877958[77] = 0.0;
   out_6160206684466877958[78] = 0.0;
   out_6160206684466877958[79] = 0.0;
   out_6160206684466877958[80] = 0.0;
   out_6160206684466877958[81] = 0.0;
   out_6160206684466877958[82] = 0.0;
   out_6160206684466877958[83] = 0.0;
   out_6160206684466877958[84] = 0.0;
   out_6160206684466877958[85] = 0.0;
   out_6160206684466877958[86] = 0.0;
   out_6160206684466877958[87] = 0.0;
   out_6160206684466877958[88] = 0.0;
   out_6160206684466877958[89] = 0.0;
   out_6160206684466877958[90] = 0.0;
   out_6160206684466877958[91] = 0.0;
   out_6160206684466877958[92] = 0.0;
   out_6160206684466877958[93] = 0.0;
   out_6160206684466877958[94] = 0.0;
   out_6160206684466877958[95] = 1.0;
   out_6160206684466877958[96] = 0.0;
   out_6160206684466877958[97] = 0.0;
   out_6160206684466877958[98] = 0.0;
   out_6160206684466877958[99] = 0.0;
   out_6160206684466877958[100] = 0.0;
   out_6160206684466877958[101] = 0.0;
   out_6160206684466877958[102] = 0.0;
   out_6160206684466877958[103] = 0.0;
   out_6160206684466877958[104] = 0.0;
   out_6160206684466877958[105] = 0.0;
   out_6160206684466877958[106] = 0.0;
   out_6160206684466877958[107] = 0.0;
   out_6160206684466877958[108] = 0.0;
   out_6160206684466877958[109] = 0.0;
   out_6160206684466877958[110] = 0.0;
   out_6160206684466877958[111] = 0.0;
   out_6160206684466877958[112] = 0.0;
   out_6160206684466877958[113] = 0.0;
   out_6160206684466877958[114] = 1.0;
   out_6160206684466877958[115] = 0.0;
   out_6160206684466877958[116] = 0.0;
   out_6160206684466877958[117] = 0.0;
   out_6160206684466877958[118] = 0.0;
   out_6160206684466877958[119] = 0.0;
   out_6160206684466877958[120] = 0.0;
   out_6160206684466877958[121] = 0.0;
   out_6160206684466877958[122] = 0.0;
   out_6160206684466877958[123] = 0.0;
   out_6160206684466877958[124] = 0.0;
   out_6160206684466877958[125] = 0.0;
   out_6160206684466877958[126] = 0.0;
   out_6160206684466877958[127] = 0.0;
   out_6160206684466877958[128] = 0.0;
   out_6160206684466877958[129] = 0.0;
   out_6160206684466877958[130] = 0.0;
   out_6160206684466877958[131] = 0.0;
   out_6160206684466877958[132] = 0.0;
   out_6160206684466877958[133] = 1.0;
   out_6160206684466877958[134] = 0.0;
   out_6160206684466877958[135] = 0.0;
   out_6160206684466877958[136] = 0.0;
   out_6160206684466877958[137] = 0.0;
   out_6160206684466877958[138] = 0.0;
   out_6160206684466877958[139] = 0.0;
   out_6160206684466877958[140] = 0.0;
   out_6160206684466877958[141] = 0.0;
   out_6160206684466877958[142] = 0.0;
   out_6160206684466877958[143] = 0.0;
   out_6160206684466877958[144] = 0.0;
   out_6160206684466877958[145] = 0.0;
   out_6160206684466877958[146] = 0.0;
   out_6160206684466877958[147] = 0.0;
   out_6160206684466877958[148] = 0.0;
   out_6160206684466877958[149] = 0.0;
   out_6160206684466877958[150] = 0.0;
   out_6160206684466877958[151] = 0.0;
   out_6160206684466877958[152] = 1.0;
   out_6160206684466877958[153] = 0.0;
   out_6160206684466877958[154] = 0.0;
   out_6160206684466877958[155] = 0.0;
   out_6160206684466877958[156] = 0.0;
   out_6160206684466877958[157] = 0.0;
   out_6160206684466877958[158] = 0.0;
   out_6160206684466877958[159] = 0.0;
   out_6160206684466877958[160] = 0.0;
   out_6160206684466877958[161] = 0.0;
   out_6160206684466877958[162] = 0.0;
   out_6160206684466877958[163] = 0.0;
   out_6160206684466877958[164] = 0.0;
   out_6160206684466877958[165] = 0.0;
   out_6160206684466877958[166] = 0.0;
   out_6160206684466877958[167] = 0.0;
   out_6160206684466877958[168] = 0.0;
   out_6160206684466877958[169] = 0.0;
   out_6160206684466877958[170] = 0.0;
   out_6160206684466877958[171] = 1.0;
   out_6160206684466877958[172] = 0.0;
   out_6160206684466877958[173] = 0.0;
   out_6160206684466877958[174] = 0.0;
   out_6160206684466877958[175] = 0.0;
   out_6160206684466877958[176] = 0.0;
   out_6160206684466877958[177] = 0.0;
   out_6160206684466877958[178] = 0.0;
   out_6160206684466877958[179] = 0.0;
   out_6160206684466877958[180] = 0.0;
   out_6160206684466877958[181] = 0.0;
   out_6160206684466877958[182] = 0.0;
   out_6160206684466877958[183] = 0.0;
   out_6160206684466877958[184] = 0.0;
   out_6160206684466877958[185] = 0.0;
   out_6160206684466877958[186] = 0.0;
   out_6160206684466877958[187] = 0.0;
   out_6160206684466877958[188] = 0.0;
   out_6160206684466877958[189] = 0.0;
   out_6160206684466877958[190] = 1.0;
   out_6160206684466877958[191] = 0.0;
   out_6160206684466877958[192] = 0.0;
   out_6160206684466877958[193] = 0.0;
   out_6160206684466877958[194] = 0.0;
   out_6160206684466877958[195] = 0.0;
   out_6160206684466877958[196] = 0.0;
   out_6160206684466877958[197] = 0.0;
   out_6160206684466877958[198] = 0.0;
   out_6160206684466877958[199] = 0.0;
   out_6160206684466877958[200] = 0.0;
   out_6160206684466877958[201] = 0.0;
   out_6160206684466877958[202] = 0.0;
   out_6160206684466877958[203] = 0.0;
   out_6160206684466877958[204] = 0.0;
   out_6160206684466877958[205] = 0.0;
   out_6160206684466877958[206] = 0.0;
   out_6160206684466877958[207] = 0.0;
   out_6160206684466877958[208] = 0.0;
   out_6160206684466877958[209] = 1.0;
   out_6160206684466877958[210] = 0.0;
   out_6160206684466877958[211] = 0.0;
   out_6160206684466877958[212] = 0.0;
   out_6160206684466877958[213] = 0.0;
   out_6160206684466877958[214] = 0.0;
   out_6160206684466877958[215] = 0.0;
   out_6160206684466877958[216] = 0.0;
   out_6160206684466877958[217] = 0.0;
   out_6160206684466877958[218] = 0.0;
   out_6160206684466877958[219] = 0.0;
   out_6160206684466877958[220] = 0.0;
   out_6160206684466877958[221] = 0.0;
   out_6160206684466877958[222] = 0.0;
   out_6160206684466877958[223] = 0.0;
   out_6160206684466877958[224] = 0.0;
   out_6160206684466877958[225] = 0.0;
   out_6160206684466877958[226] = 0.0;
   out_6160206684466877958[227] = 0.0;
   out_6160206684466877958[228] = 1.0;
   out_6160206684466877958[229] = 0.0;
   out_6160206684466877958[230] = 0.0;
   out_6160206684466877958[231] = 0.0;
   out_6160206684466877958[232] = 0.0;
   out_6160206684466877958[233] = 0.0;
   out_6160206684466877958[234] = 0.0;
   out_6160206684466877958[235] = 0.0;
   out_6160206684466877958[236] = 0.0;
   out_6160206684466877958[237] = 0.0;
   out_6160206684466877958[238] = 0.0;
   out_6160206684466877958[239] = 0.0;
   out_6160206684466877958[240] = 0.0;
   out_6160206684466877958[241] = 0.0;
   out_6160206684466877958[242] = 0.0;
   out_6160206684466877958[243] = 0.0;
   out_6160206684466877958[244] = 0.0;
   out_6160206684466877958[245] = 0.0;
   out_6160206684466877958[246] = 0.0;
   out_6160206684466877958[247] = 1.0;
   out_6160206684466877958[248] = 0.0;
   out_6160206684466877958[249] = 0.0;
   out_6160206684466877958[250] = 0.0;
   out_6160206684466877958[251] = 0.0;
   out_6160206684466877958[252] = 0.0;
   out_6160206684466877958[253] = 0.0;
   out_6160206684466877958[254] = 0.0;
   out_6160206684466877958[255] = 0.0;
   out_6160206684466877958[256] = 0.0;
   out_6160206684466877958[257] = 0.0;
   out_6160206684466877958[258] = 0.0;
   out_6160206684466877958[259] = 0.0;
   out_6160206684466877958[260] = 0.0;
   out_6160206684466877958[261] = 0.0;
   out_6160206684466877958[262] = 0.0;
   out_6160206684466877958[263] = 0.0;
   out_6160206684466877958[264] = 0.0;
   out_6160206684466877958[265] = 0.0;
   out_6160206684466877958[266] = 1.0;
   out_6160206684466877958[267] = 0.0;
   out_6160206684466877958[268] = 0.0;
   out_6160206684466877958[269] = 0.0;
   out_6160206684466877958[270] = 0.0;
   out_6160206684466877958[271] = 0.0;
   out_6160206684466877958[272] = 0.0;
   out_6160206684466877958[273] = 0.0;
   out_6160206684466877958[274] = 0.0;
   out_6160206684466877958[275] = 0.0;
   out_6160206684466877958[276] = 0.0;
   out_6160206684466877958[277] = 0.0;
   out_6160206684466877958[278] = 0.0;
   out_6160206684466877958[279] = 0.0;
   out_6160206684466877958[280] = 0.0;
   out_6160206684466877958[281] = 0.0;
   out_6160206684466877958[282] = 0.0;
   out_6160206684466877958[283] = 0.0;
   out_6160206684466877958[284] = 0.0;
   out_6160206684466877958[285] = 1.0;
   out_6160206684466877958[286] = 0.0;
   out_6160206684466877958[287] = 0.0;
   out_6160206684466877958[288] = 0.0;
   out_6160206684466877958[289] = 0.0;
   out_6160206684466877958[290] = 0.0;
   out_6160206684466877958[291] = 0.0;
   out_6160206684466877958[292] = 0.0;
   out_6160206684466877958[293] = 0.0;
   out_6160206684466877958[294] = 0.0;
   out_6160206684466877958[295] = 0.0;
   out_6160206684466877958[296] = 0.0;
   out_6160206684466877958[297] = 0.0;
   out_6160206684466877958[298] = 0.0;
   out_6160206684466877958[299] = 0.0;
   out_6160206684466877958[300] = 0.0;
   out_6160206684466877958[301] = 0.0;
   out_6160206684466877958[302] = 0.0;
   out_6160206684466877958[303] = 0.0;
   out_6160206684466877958[304] = 1.0;
   out_6160206684466877958[305] = 0.0;
   out_6160206684466877958[306] = 0.0;
   out_6160206684466877958[307] = 0.0;
   out_6160206684466877958[308] = 0.0;
   out_6160206684466877958[309] = 0.0;
   out_6160206684466877958[310] = 0.0;
   out_6160206684466877958[311] = 0.0;
   out_6160206684466877958[312] = 0.0;
   out_6160206684466877958[313] = 0.0;
   out_6160206684466877958[314] = 0.0;
   out_6160206684466877958[315] = 0.0;
   out_6160206684466877958[316] = 0.0;
   out_6160206684466877958[317] = 0.0;
   out_6160206684466877958[318] = 0.0;
   out_6160206684466877958[319] = 0.0;
   out_6160206684466877958[320] = 0.0;
   out_6160206684466877958[321] = 0.0;
   out_6160206684466877958[322] = 0.0;
   out_6160206684466877958[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4800341315034629509) {
   out_4800341315034629509[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4800341315034629509[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4800341315034629509[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4800341315034629509[3] = dt*state[12] + state[3];
   out_4800341315034629509[4] = dt*state[13] + state[4];
   out_4800341315034629509[5] = dt*state[14] + state[5];
   out_4800341315034629509[6] = state[6];
   out_4800341315034629509[7] = state[7];
   out_4800341315034629509[8] = state[8];
   out_4800341315034629509[9] = state[9];
   out_4800341315034629509[10] = state[10];
   out_4800341315034629509[11] = state[11];
   out_4800341315034629509[12] = state[12];
   out_4800341315034629509[13] = state[13];
   out_4800341315034629509[14] = state[14];
   out_4800341315034629509[15] = state[15];
   out_4800341315034629509[16] = state[16];
   out_4800341315034629509[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2115414934888159835) {
   out_2115414934888159835[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2115414934888159835[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2115414934888159835[2] = 0;
   out_2115414934888159835[3] = 0;
   out_2115414934888159835[4] = 0;
   out_2115414934888159835[5] = 0;
   out_2115414934888159835[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2115414934888159835[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2115414934888159835[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2115414934888159835[9] = 0;
   out_2115414934888159835[10] = 0;
   out_2115414934888159835[11] = 0;
   out_2115414934888159835[12] = 0;
   out_2115414934888159835[13] = 0;
   out_2115414934888159835[14] = 0;
   out_2115414934888159835[15] = 0;
   out_2115414934888159835[16] = 0;
   out_2115414934888159835[17] = 0;
   out_2115414934888159835[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2115414934888159835[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2115414934888159835[20] = 0;
   out_2115414934888159835[21] = 0;
   out_2115414934888159835[22] = 0;
   out_2115414934888159835[23] = 0;
   out_2115414934888159835[24] = 0;
   out_2115414934888159835[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2115414934888159835[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2115414934888159835[27] = 0;
   out_2115414934888159835[28] = 0;
   out_2115414934888159835[29] = 0;
   out_2115414934888159835[30] = 0;
   out_2115414934888159835[31] = 0;
   out_2115414934888159835[32] = 0;
   out_2115414934888159835[33] = 0;
   out_2115414934888159835[34] = 0;
   out_2115414934888159835[35] = 0;
   out_2115414934888159835[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2115414934888159835[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2115414934888159835[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2115414934888159835[39] = 0;
   out_2115414934888159835[40] = 0;
   out_2115414934888159835[41] = 0;
   out_2115414934888159835[42] = 0;
   out_2115414934888159835[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2115414934888159835[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2115414934888159835[45] = 0;
   out_2115414934888159835[46] = 0;
   out_2115414934888159835[47] = 0;
   out_2115414934888159835[48] = 0;
   out_2115414934888159835[49] = 0;
   out_2115414934888159835[50] = 0;
   out_2115414934888159835[51] = 0;
   out_2115414934888159835[52] = 0;
   out_2115414934888159835[53] = 0;
   out_2115414934888159835[54] = 0;
   out_2115414934888159835[55] = 0;
   out_2115414934888159835[56] = 0;
   out_2115414934888159835[57] = 1;
   out_2115414934888159835[58] = 0;
   out_2115414934888159835[59] = 0;
   out_2115414934888159835[60] = 0;
   out_2115414934888159835[61] = 0;
   out_2115414934888159835[62] = 0;
   out_2115414934888159835[63] = 0;
   out_2115414934888159835[64] = 0;
   out_2115414934888159835[65] = 0;
   out_2115414934888159835[66] = dt;
   out_2115414934888159835[67] = 0;
   out_2115414934888159835[68] = 0;
   out_2115414934888159835[69] = 0;
   out_2115414934888159835[70] = 0;
   out_2115414934888159835[71] = 0;
   out_2115414934888159835[72] = 0;
   out_2115414934888159835[73] = 0;
   out_2115414934888159835[74] = 0;
   out_2115414934888159835[75] = 0;
   out_2115414934888159835[76] = 1;
   out_2115414934888159835[77] = 0;
   out_2115414934888159835[78] = 0;
   out_2115414934888159835[79] = 0;
   out_2115414934888159835[80] = 0;
   out_2115414934888159835[81] = 0;
   out_2115414934888159835[82] = 0;
   out_2115414934888159835[83] = 0;
   out_2115414934888159835[84] = 0;
   out_2115414934888159835[85] = dt;
   out_2115414934888159835[86] = 0;
   out_2115414934888159835[87] = 0;
   out_2115414934888159835[88] = 0;
   out_2115414934888159835[89] = 0;
   out_2115414934888159835[90] = 0;
   out_2115414934888159835[91] = 0;
   out_2115414934888159835[92] = 0;
   out_2115414934888159835[93] = 0;
   out_2115414934888159835[94] = 0;
   out_2115414934888159835[95] = 1;
   out_2115414934888159835[96] = 0;
   out_2115414934888159835[97] = 0;
   out_2115414934888159835[98] = 0;
   out_2115414934888159835[99] = 0;
   out_2115414934888159835[100] = 0;
   out_2115414934888159835[101] = 0;
   out_2115414934888159835[102] = 0;
   out_2115414934888159835[103] = 0;
   out_2115414934888159835[104] = dt;
   out_2115414934888159835[105] = 0;
   out_2115414934888159835[106] = 0;
   out_2115414934888159835[107] = 0;
   out_2115414934888159835[108] = 0;
   out_2115414934888159835[109] = 0;
   out_2115414934888159835[110] = 0;
   out_2115414934888159835[111] = 0;
   out_2115414934888159835[112] = 0;
   out_2115414934888159835[113] = 0;
   out_2115414934888159835[114] = 1;
   out_2115414934888159835[115] = 0;
   out_2115414934888159835[116] = 0;
   out_2115414934888159835[117] = 0;
   out_2115414934888159835[118] = 0;
   out_2115414934888159835[119] = 0;
   out_2115414934888159835[120] = 0;
   out_2115414934888159835[121] = 0;
   out_2115414934888159835[122] = 0;
   out_2115414934888159835[123] = 0;
   out_2115414934888159835[124] = 0;
   out_2115414934888159835[125] = 0;
   out_2115414934888159835[126] = 0;
   out_2115414934888159835[127] = 0;
   out_2115414934888159835[128] = 0;
   out_2115414934888159835[129] = 0;
   out_2115414934888159835[130] = 0;
   out_2115414934888159835[131] = 0;
   out_2115414934888159835[132] = 0;
   out_2115414934888159835[133] = 1;
   out_2115414934888159835[134] = 0;
   out_2115414934888159835[135] = 0;
   out_2115414934888159835[136] = 0;
   out_2115414934888159835[137] = 0;
   out_2115414934888159835[138] = 0;
   out_2115414934888159835[139] = 0;
   out_2115414934888159835[140] = 0;
   out_2115414934888159835[141] = 0;
   out_2115414934888159835[142] = 0;
   out_2115414934888159835[143] = 0;
   out_2115414934888159835[144] = 0;
   out_2115414934888159835[145] = 0;
   out_2115414934888159835[146] = 0;
   out_2115414934888159835[147] = 0;
   out_2115414934888159835[148] = 0;
   out_2115414934888159835[149] = 0;
   out_2115414934888159835[150] = 0;
   out_2115414934888159835[151] = 0;
   out_2115414934888159835[152] = 1;
   out_2115414934888159835[153] = 0;
   out_2115414934888159835[154] = 0;
   out_2115414934888159835[155] = 0;
   out_2115414934888159835[156] = 0;
   out_2115414934888159835[157] = 0;
   out_2115414934888159835[158] = 0;
   out_2115414934888159835[159] = 0;
   out_2115414934888159835[160] = 0;
   out_2115414934888159835[161] = 0;
   out_2115414934888159835[162] = 0;
   out_2115414934888159835[163] = 0;
   out_2115414934888159835[164] = 0;
   out_2115414934888159835[165] = 0;
   out_2115414934888159835[166] = 0;
   out_2115414934888159835[167] = 0;
   out_2115414934888159835[168] = 0;
   out_2115414934888159835[169] = 0;
   out_2115414934888159835[170] = 0;
   out_2115414934888159835[171] = 1;
   out_2115414934888159835[172] = 0;
   out_2115414934888159835[173] = 0;
   out_2115414934888159835[174] = 0;
   out_2115414934888159835[175] = 0;
   out_2115414934888159835[176] = 0;
   out_2115414934888159835[177] = 0;
   out_2115414934888159835[178] = 0;
   out_2115414934888159835[179] = 0;
   out_2115414934888159835[180] = 0;
   out_2115414934888159835[181] = 0;
   out_2115414934888159835[182] = 0;
   out_2115414934888159835[183] = 0;
   out_2115414934888159835[184] = 0;
   out_2115414934888159835[185] = 0;
   out_2115414934888159835[186] = 0;
   out_2115414934888159835[187] = 0;
   out_2115414934888159835[188] = 0;
   out_2115414934888159835[189] = 0;
   out_2115414934888159835[190] = 1;
   out_2115414934888159835[191] = 0;
   out_2115414934888159835[192] = 0;
   out_2115414934888159835[193] = 0;
   out_2115414934888159835[194] = 0;
   out_2115414934888159835[195] = 0;
   out_2115414934888159835[196] = 0;
   out_2115414934888159835[197] = 0;
   out_2115414934888159835[198] = 0;
   out_2115414934888159835[199] = 0;
   out_2115414934888159835[200] = 0;
   out_2115414934888159835[201] = 0;
   out_2115414934888159835[202] = 0;
   out_2115414934888159835[203] = 0;
   out_2115414934888159835[204] = 0;
   out_2115414934888159835[205] = 0;
   out_2115414934888159835[206] = 0;
   out_2115414934888159835[207] = 0;
   out_2115414934888159835[208] = 0;
   out_2115414934888159835[209] = 1;
   out_2115414934888159835[210] = 0;
   out_2115414934888159835[211] = 0;
   out_2115414934888159835[212] = 0;
   out_2115414934888159835[213] = 0;
   out_2115414934888159835[214] = 0;
   out_2115414934888159835[215] = 0;
   out_2115414934888159835[216] = 0;
   out_2115414934888159835[217] = 0;
   out_2115414934888159835[218] = 0;
   out_2115414934888159835[219] = 0;
   out_2115414934888159835[220] = 0;
   out_2115414934888159835[221] = 0;
   out_2115414934888159835[222] = 0;
   out_2115414934888159835[223] = 0;
   out_2115414934888159835[224] = 0;
   out_2115414934888159835[225] = 0;
   out_2115414934888159835[226] = 0;
   out_2115414934888159835[227] = 0;
   out_2115414934888159835[228] = 1;
   out_2115414934888159835[229] = 0;
   out_2115414934888159835[230] = 0;
   out_2115414934888159835[231] = 0;
   out_2115414934888159835[232] = 0;
   out_2115414934888159835[233] = 0;
   out_2115414934888159835[234] = 0;
   out_2115414934888159835[235] = 0;
   out_2115414934888159835[236] = 0;
   out_2115414934888159835[237] = 0;
   out_2115414934888159835[238] = 0;
   out_2115414934888159835[239] = 0;
   out_2115414934888159835[240] = 0;
   out_2115414934888159835[241] = 0;
   out_2115414934888159835[242] = 0;
   out_2115414934888159835[243] = 0;
   out_2115414934888159835[244] = 0;
   out_2115414934888159835[245] = 0;
   out_2115414934888159835[246] = 0;
   out_2115414934888159835[247] = 1;
   out_2115414934888159835[248] = 0;
   out_2115414934888159835[249] = 0;
   out_2115414934888159835[250] = 0;
   out_2115414934888159835[251] = 0;
   out_2115414934888159835[252] = 0;
   out_2115414934888159835[253] = 0;
   out_2115414934888159835[254] = 0;
   out_2115414934888159835[255] = 0;
   out_2115414934888159835[256] = 0;
   out_2115414934888159835[257] = 0;
   out_2115414934888159835[258] = 0;
   out_2115414934888159835[259] = 0;
   out_2115414934888159835[260] = 0;
   out_2115414934888159835[261] = 0;
   out_2115414934888159835[262] = 0;
   out_2115414934888159835[263] = 0;
   out_2115414934888159835[264] = 0;
   out_2115414934888159835[265] = 0;
   out_2115414934888159835[266] = 1;
   out_2115414934888159835[267] = 0;
   out_2115414934888159835[268] = 0;
   out_2115414934888159835[269] = 0;
   out_2115414934888159835[270] = 0;
   out_2115414934888159835[271] = 0;
   out_2115414934888159835[272] = 0;
   out_2115414934888159835[273] = 0;
   out_2115414934888159835[274] = 0;
   out_2115414934888159835[275] = 0;
   out_2115414934888159835[276] = 0;
   out_2115414934888159835[277] = 0;
   out_2115414934888159835[278] = 0;
   out_2115414934888159835[279] = 0;
   out_2115414934888159835[280] = 0;
   out_2115414934888159835[281] = 0;
   out_2115414934888159835[282] = 0;
   out_2115414934888159835[283] = 0;
   out_2115414934888159835[284] = 0;
   out_2115414934888159835[285] = 1;
   out_2115414934888159835[286] = 0;
   out_2115414934888159835[287] = 0;
   out_2115414934888159835[288] = 0;
   out_2115414934888159835[289] = 0;
   out_2115414934888159835[290] = 0;
   out_2115414934888159835[291] = 0;
   out_2115414934888159835[292] = 0;
   out_2115414934888159835[293] = 0;
   out_2115414934888159835[294] = 0;
   out_2115414934888159835[295] = 0;
   out_2115414934888159835[296] = 0;
   out_2115414934888159835[297] = 0;
   out_2115414934888159835[298] = 0;
   out_2115414934888159835[299] = 0;
   out_2115414934888159835[300] = 0;
   out_2115414934888159835[301] = 0;
   out_2115414934888159835[302] = 0;
   out_2115414934888159835[303] = 0;
   out_2115414934888159835[304] = 1;
   out_2115414934888159835[305] = 0;
   out_2115414934888159835[306] = 0;
   out_2115414934888159835[307] = 0;
   out_2115414934888159835[308] = 0;
   out_2115414934888159835[309] = 0;
   out_2115414934888159835[310] = 0;
   out_2115414934888159835[311] = 0;
   out_2115414934888159835[312] = 0;
   out_2115414934888159835[313] = 0;
   out_2115414934888159835[314] = 0;
   out_2115414934888159835[315] = 0;
   out_2115414934888159835[316] = 0;
   out_2115414934888159835[317] = 0;
   out_2115414934888159835[318] = 0;
   out_2115414934888159835[319] = 0;
   out_2115414934888159835[320] = 0;
   out_2115414934888159835[321] = 0;
   out_2115414934888159835[322] = 0;
   out_2115414934888159835[323] = 1;
}
void h_4(double *state, double *unused, double *out_2892054295359636963) {
   out_2892054295359636963[0] = state[6] + state[9];
   out_2892054295359636963[1] = state[7] + state[10];
   out_2892054295359636963[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4086232505269448891) {
   out_4086232505269448891[0] = 0;
   out_4086232505269448891[1] = 0;
   out_4086232505269448891[2] = 0;
   out_4086232505269448891[3] = 0;
   out_4086232505269448891[4] = 0;
   out_4086232505269448891[5] = 0;
   out_4086232505269448891[6] = 1;
   out_4086232505269448891[7] = 0;
   out_4086232505269448891[8] = 0;
   out_4086232505269448891[9] = 1;
   out_4086232505269448891[10] = 0;
   out_4086232505269448891[11] = 0;
   out_4086232505269448891[12] = 0;
   out_4086232505269448891[13] = 0;
   out_4086232505269448891[14] = 0;
   out_4086232505269448891[15] = 0;
   out_4086232505269448891[16] = 0;
   out_4086232505269448891[17] = 0;
   out_4086232505269448891[18] = 0;
   out_4086232505269448891[19] = 0;
   out_4086232505269448891[20] = 0;
   out_4086232505269448891[21] = 0;
   out_4086232505269448891[22] = 0;
   out_4086232505269448891[23] = 0;
   out_4086232505269448891[24] = 0;
   out_4086232505269448891[25] = 1;
   out_4086232505269448891[26] = 0;
   out_4086232505269448891[27] = 0;
   out_4086232505269448891[28] = 1;
   out_4086232505269448891[29] = 0;
   out_4086232505269448891[30] = 0;
   out_4086232505269448891[31] = 0;
   out_4086232505269448891[32] = 0;
   out_4086232505269448891[33] = 0;
   out_4086232505269448891[34] = 0;
   out_4086232505269448891[35] = 0;
   out_4086232505269448891[36] = 0;
   out_4086232505269448891[37] = 0;
   out_4086232505269448891[38] = 0;
   out_4086232505269448891[39] = 0;
   out_4086232505269448891[40] = 0;
   out_4086232505269448891[41] = 0;
   out_4086232505269448891[42] = 0;
   out_4086232505269448891[43] = 0;
   out_4086232505269448891[44] = 1;
   out_4086232505269448891[45] = 0;
   out_4086232505269448891[46] = 0;
   out_4086232505269448891[47] = 1;
   out_4086232505269448891[48] = 0;
   out_4086232505269448891[49] = 0;
   out_4086232505269448891[50] = 0;
   out_4086232505269448891[51] = 0;
   out_4086232505269448891[52] = 0;
   out_4086232505269448891[53] = 0;
}
void h_10(double *state, double *unused, double *out_1520403981462315862) {
   out_1520403981462315862[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1520403981462315862[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1520403981462315862[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_944059824953988773) {
   out_944059824953988773[0] = 0;
   out_944059824953988773[1] = 9.8100000000000005*cos(state[1]);
   out_944059824953988773[2] = 0;
   out_944059824953988773[3] = 0;
   out_944059824953988773[4] = -state[8];
   out_944059824953988773[5] = state[7];
   out_944059824953988773[6] = 0;
   out_944059824953988773[7] = state[5];
   out_944059824953988773[8] = -state[4];
   out_944059824953988773[9] = 0;
   out_944059824953988773[10] = 0;
   out_944059824953988773[11] = 0;
   out_944059824953988773[12] = 1;
   out_944059824953988773[13] = 0;
   out_944059824953988773[14] = 0;
   out_944059824953988773[15] = 1;
   out_944059824953988773[16] = 0;
   out_944059824953988773[17] = 0;
   out_944059824953988773[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_944059824953988773[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_944059824953988773[20] = 0;
   out_944059824953988773[21] = state[8];
   out_944059824953988773[22] = 0;
   out_944059824953988773[23] = -state[6];
   out_944059824953988773[24] = -state[5];
   out_944059824953988773[25] = 0;
   out_944059824953988773[26] = state[3];
   out_944059824953988773[27] = 0;
   out_944059824953988773[28] = 0;
   out_944059824953988773[29] = 0;
   out_944059824953988773[30] = 0;
   out_944059824953988773[31] = 1;
   out_944059824953988773[32] = 0;
   out_944059824953988773[33] = 0;
   out_944059824953988773[34] = 1;
   out_944059824953988773[35] = 0;
   out_944059824953988773[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_944059824953988773[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_944059824953988773[38] = 0;
   out_944059824953988773[39] = -state[7];
   out_944059824953988773[40] = state[6];
   out_944059824953988773[41] = 0;
   out_944059824953988773[42] = state[4];
   out_944059824953988773[43] = -state[3];
   out_944059824953988773[44] = 0;
   out_944059824953988773[45] = 0;
   out_944059824953988773[46] = 0;
   out_944059824953988773[47] = 0;
   out_944059824953988773[48] = 0;
   out_944059824953988773[49] = 0;
   out_944059824953988773[50] = 1;
   out_944059824953988773[51] = 0;
   out_944059824953988773[52] = 0;
   out_944059824953988773[53] = 1;
}
void h_13(double *state, double *unused, double *out_7929828547441307226) {
   out_7929828547441307226[0] = state[3];
   out_7929828547441307226[1] = state[4];
   out_7929828547441307226[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3524398703047252038) {
   out_3524398703047252038[0] = 0;
   out_3524398703047252038[1] = 0;
   out_3524398703047252038[2] = 0;
   out_3524398703047252038[3] = 1;
   out_3524398703047252038[4] = 0;
   out_3524398703047252038[5] = 0;
   out_3524398703047252038[6] = 0;
   out_3524398703047252038[7] = 0;
   out_3524398703047252038[8] = 0;
   out_3524398703047252038[9] = 0;
   out_3524398703047252038[10] = 0;
   out_3524398703047252038[11] = 0;
   out_3524398703047252038[12] = 0;
   out_3524398703047252038[13] = 0;
   out_3524398703047252038[14] = 0;
   out_3524398703047252038[15] = 0;
   out_3524398703047252038[16] = 0;
   out_3524398703047252038[17] = 0;
   out_3524398703047252038[18] = 0;
   out_3524398703047252038[19] = 0;
   out_3524398703047252038[20] = 0;
   out_3524398703047252038[21] = 0;
   out_3524398703047252038[22] = 1;
   out_3524398703047252038[23] = 0;
   out_3524398703047252038[24] = 0;
   out_3524398703047252038[25] = 0;
   out_3524398703047252038[26] = 0;
   out_3524398703047252038[27] = 0;
   out_3524398703047252038[28] = 0;
   out_3524398703047252038[29] = 0;
   out_3524398703047252038[30] = 0;
   out_3524398703047252038[31] = 0;
   out_3524398703047252038[32] = 0;
   out_3524398703047252038[33] = 0;
   out_3524398703047252038[34] = 0;
   out_3524398703047252038[35] = 0;
   out_3524398703047252038[36] = 0;
   out_3524398703047252038[37] = 0;
   out_3524398703047252038[38] = 0;
   out_3524398703047252038[39] = 0;
   out_3524398703047252038[40] = 0;
   out_3524398703047252038[41] = 1;
   out_3524398703047252038[42] = 0;
   out_3524398703047252038[43] = 0;
   out_3524398703047252038[44] = 0;
   out_3524398703047252038[45] = 0;
   out_3524398703047252038[46] = 0;
   out_3524398703047252038[47] = 0;
   out_3524398703047252038[48] = 0;
   out_3524398703047252038[49] = 0;
   out_3524398703047252038[50] = 0;
   out_3524398703047252038[51] = 0;
   out_3524398703047252038[52] = 0;
   out_3524398703047252038[53] = 0;
}
void h_14(double *state, double *unused, double *out_4827639347712724102) {
   out_4827639347712724102[0] = state[6];
   out_4827639347712724102[1] = state[7];
   out_4827639347712724102[2] = state[8];
}
void H_14(double *state, double *unused, double *out_122991648929964362) {
   out_122991648929964362[0] = 0;
   out_122991648929964362[1] = 0;
   out_122991648929964362[2] = 0;
   out_122991648929964362[3] = 0;
   out_122991648929964362[4] = 0;
   out_122991648929964362[5] = 0;
   out_122991648929964362[6] = 1;
   out_122991648929964362[7] = 0;
   out_122991648929964362[8] = 0;
   out_122991648929964362[9] = 0;
   out_122991648929964362[10] = 0;
   out_122991648929964362[11] = 0;
   out_122991648929964362[12] = 0;
   out_122991648929964362[13] = 0;
   out_122991648929964362[14] = 0;
   out_122991648929964362[15] = 0;
   out_122991648929964362[16] = 0;
   out_122991648929964362[17] = 0;
   out_122991648929964362[18] = 0;
   out_122991648929964362[19] = 0;
   out_122991648929964362[20] = 0;
   out_122991648929964362[21] = 0;
   out_122991648929964362[22] = 0;
   out_122991648929964362[23] = 0;
   out_122991648929964362[24] = 0;
   out_122991648929964362[25] = 1;
   out_122991648929964362[26] = 0;
   out_122991648929964362[27] = 0;
   out_122991648929964362[28] = 0;
   out_122991648929964362[29] = 0;
   out_122991648929964362[30] = 0;
   out_122991648929964362[31] = 0;
   out_122991648929964362[32] = 0;
   out_122991648929964362[33] = 0;
   out_122991648929964362[34] = 0;
   out_122991648929964362[35] = 0;
   out_122991648929964362[36] = 0;
   out_122991648929964362[37] = 0;
   out_122991648929964362[38] = 0;
   out_122991648929964362[39] = 0;
   out_122991648929964362[40] = 0;
   out_122991648929964362[41] = 0;
   out_122991648929964362[42] = 0;
   out_122991648929964362[43] = 0;
   out_122991648929964362[44] = 1;
   out_122991648929964362[45] = 0;
   out_122991648929964362[46] = 0;
   out_122991648929964362[47] = 0;
   out_122991648929964362[48] = 0;
   out_122991648929964362[49] = 0;
   out_122991648929964362[50] = 0;
   out_122991648929964362[51] = 0;
   out_122991648929964362[52] = 0;
   out_122991648929964362[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_3763521124081322775) {
  err_fun(nom_x, delta_x, out_3763521124081322775);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_177812529109460282) {
  inv_err_fun(nom_x, true_x, out_177812529109460282);
}
void pose_H_mod_fun(double *state, double *out_6160206684466877958) {
  H_mod_fun(state, out_6160206684466877958);
}
void pose_f_fun(double *state, double dt, double *out_4800341315034629509) {
  f_fun(state,  dt, out_4800341315034629509);
}
void pose_F_fun(double *state, double dt, double *out_2115414934888159835) {
  F_fun(state,  dt, out_2115414934888159835);
}
void pose_h_4(double *state, double *unused, double *out_2892054295359636963) {
  h_4(state, unused, out_2892054295359636963);
}
void pose_H_4(double *state, double *unused, double *out_4086232505269448891) {
  H_4(state, unused, out_4086232505269448891);
}
void pose_h_10(double *state, double *unused, double *out_1520403981462315862) {
  h_10(state, unused, out_1520403981462315862);
}
void pose_H_10(double *state, double *unused, double *out_944059824953988773) {
  H_10(state, unused, out_944059824953988773);
}
void pose_h_13(double *state, double *unused, double *out_7929828547441307226) {
  h_13(state, unused, out_7929828547441307226);
}
void pose_H_13(double *state, double *unused, double *out_3524398703047252038) {
  H_13(state, unused, out_3524398703047252038);
}
void pose_h_14(double *state, double *unused, double *out_4827639347712724102) {
  h_14(state, unused, out_4827639347712724102);
}
void pose_H_14(double *state, double *unused, double *out_122991648929964362) {
  H_14(state, unused, out_122991648929964362);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
