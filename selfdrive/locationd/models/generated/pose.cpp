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
void err_fun(double *nom_x, double *delta_x, double *out_7475867757860580655) {
   out_7475867757860580655[0] = delta_x[0] + nom_x[0];
   out_7475867757860580655[1] = delta_x[1] + nom_x[1];
   out_7475867757860580655[2] = delta_x[2] + nom_x[2];
   out_7475867757860580655[3] = delta_x[3] + nom_x[3];
   out_7475867757860580655[4] = delta_x[4] + nom_x[4];
   out_7475867757860580655[5] = delta_x[5] + nom_x[5];
   out_7475867757860580655[6] = delta_x[6] + nom_x[6];
   out_7475867757860580655[7] = delta_x[7] + nom_x[7];
   out_7475867757860580655[8] = delta_x[8] + nom_x[8];
   out_7475867757860580655[9] = delta_x[9] + nom_x[9];
   out_7475867757860580655[10] = delta_x[10] + nom_x[10];
   out_7475867757860580655[11] = delta_x[11] + nom_x[11];
   out_7475867757860580655[12] = delta_x[12] + nom_x[12];
   out_7475867757860580655[13] = delta_x[13] + nom_x[13];
   out_7475867757860580655[14] = delta_x[14] + nom_x[14];
   out_7475867757860580655[15] = delta_x[15] + nom_x[15];
   out_7475867757860580655[16] = delta_x[16] + nom_x[16];
   out_7475867757860580655[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6907412215356863750) {
   out_6907412215356863750[0] = -nom_x[0] + true_x[0];
   out_6907412215356863750[1] = -nom_x[1] + true_x[1];
   out_6907412215356863750[2] = -nom_x[2] + true_x[2];
   out_6907412215356863750[3] = -nom_x[3] + true_x[3];
   out_6907412215356863750[4] = -nom_x[4] + true_x[4];
   out_6907412215356863750[5] = -nom_x[5] + true_x[5];
   out_6907412215356863750[6] = -nom_x[6] + true_x[6];
   out_6907412215356863750[7] = -nom_x[7] + true_x[7];
   out_6907412215356863750[8] = -nom_x[8] + true_x[8];
   out_6907412215356863750[9] = -nom_x[9] + true_x[9];
   out_6907412215356863750[10] = -nom_x[10] + true_x[10];
   out_6907412215356863750[11] = -nom_x[11] + true_x[11];
   out_6907412215356863750[12] = -nom_x[12] + true_x[12];
   out_6907412215356863750[13] = -nom_x[13] + true_x[13];
   out_6907412215356863750[14] = -nom_x[14] + true_x[14];
   out_6907412215356863750[15] = -nom_x[15] + true_x[15];
   out_6907412215356863750[16] = -nom_x[16] + true_x[16];
   out_6907412215356863750[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3605623673578465873) {
   out_3605623673578465873[0] = 1.0;
   out_3605623673578465873[1] = 0.0;
   out_3605623673578465873[2] = 0.0;
   out_3605623673578465873[3] = 0.0;
   out_3605623673578465873[4] = 0.0;
   out_3605623673578465873[5] = 0.0;
   out_3605623673578465873[6] = 0.0;
   out_3605623673578465873[7] = 0.0;
   out_3605623673578465873[8] = 0.0;
   out_3605623673578465873[9] = 0.0;
   out_3605623673578465873[10] = 0.0;
   out_3605623673578465873[11] = 0.0;
   out_3605623673578465873[12] = 0.0;
   out_3605623673578465873[13] = 0.0;
   out_3605623673578465873[14] = 0.0;
   out_3605623673578465873[15] = 0.0;
   out_3605623673578465873[16] = 0.0;
   out_3605623673578465873[17] = 0.0;
   out_3605623673578465873[18] = 0.0;
   out_3605623673578465873[19] = 1.0;
   out_3605623673578465873[20] = 0.0;
   out_3605623673578465873[21] = 0.0;
   out_3605623673578465873[22] = 0.0;
   out_3605623673578465873[23] = 0.0;
   out_3605623673578465873[24] = 0.0;
   out_3605623673578465873[25] = 0.0;
   out_3605623673578465873[26] = 0.0;
   out_3605623673578465873[27] = 0.0;
   out_3605623673578465873[28] = 0.0;
   out_3605623673578465873[29] = 0.0;
   out_3605623673578465873[30] = 0.0;
   out_3605623673578465873[31] = 0.0;
   out_3605623673578465873[32] = 0.0;
   out_3605623673578465873[33] = 0.0;
   out_3605623673578465873[34] = 0.0;
   out_3605623673578465873[35] = 0.0;
   out_3605623673578465873[36] = 0.0;
   out_3605623673578465873[37] = 0.0;
   out_3605623673578465873[38] = 1.0;
   out_3605623673578465873[39] = 0.0;
   out_3605623673578465873[40] = 0.0;
   out_3605623673578465873[41] = 0.0;
   out_3605623673578465873[42] = 0.0;
   out_3605623673578465873[43] = 0.0;
   out_3605623673578465873[44] = 0.0;
   out_3605623673578465873[45] = 0.0;
   out_3605623673578465873[46] = 0.0;
   out_3605623673578465873[47] = 0.0;
   out_3605623673578465873[48] = 0.0;
   out_3605623673578465873[49] = 0.0;
   out_3605623673578465873[50] = 0.0;
   out_3605623673578465873[51] = 0.0;
   out_3605623673578465873[52] = 0.0;
   out_3605623673578465873[53] = 0.0;
   out_3605623673578465873[54] = 0.0;
   out_3605623673578465873[55] = 0.0;
   out_3605623673578465873[56] = 0.0;
   out_3605623673578465873[57] = 1.0;
   out_3605623673578465873[58] = 0.0;
   out_3605623673578465873[59] = 0.0;
   out_3605623673578465873[60] = 0.0;
   out_3605623673578465873[61] = 0.0;
   out_3605623673578465873[62] = 0.0;
   out_3605623673578465873[63] = 0.0;
   out_3605623673578465873[64] = 0.0;
   out_3605623673578465873[65] = 0.0;
   out_3605623673578465873[66] = 0.0;
   out_3605623673578465873[67] = 0.0;
   out_3605623673578465873[68] = 0.0;
   out_3605623673578465873[69] = 0.0;
   out_3605623673578465873[70] = 0.0;
   out_3605623673578465873[71] = 0.0;
   out_3605623673578465873[72] = 0.0;
   out_3605623673578465873[73] = 0.0;
   out_3605623673578465873[74] = 0.0;
   out_3605623673578465873[75] = 0.0;
   out_3605623673578465873[76] = 1.0;
   out_3605623673578465873[77] = 0.0;
   out_3605623673578465873[78] = 0.0;
   out_3605623673578465873[79] = 0.0;
   out_3605623673578465873[80] = 0.0;
   out_3605623673578465873[81] = 0.0;
   out_3605623673578465873[82] = 0.0;
   out_3605623673578465873[83] = 0.0;
   out_3605623673578465873[84] = 0.0;
   out_3605623673578465873[85] = 0.0;
   out_3605623673578465873[86] = 0.0;
   out_3605623673578465873[87] = 0.0;
   out_3605623673578465873[88] = 0.0;
   out_3605623673578465873[89] = 0.0;
   out_3605623673578465873[90] = 0.0;
   out_3605623673578465873[91] = 0.0;
   out_3605623673578465873[92] = 0.0;
   out_3605623673578465873[93] = 0.0;
   out_3605623673578465873[94] = 0.0;
   out_3605623673578465873[95] = 1.0;
   out_3605623673578465873[96] = 0.0;
   out_3605623673578465873[97] = 0.0;
   out_3605623673578465873[98] = 0.0;
   out_3605623673578465873[99] = 0.0;
   out_3605623673578465873[100] = 0.0;
   out_3605623673578465873[101] = 0.0;
   out_3605623673578465873[102] = 0.0;
   out_3605623673578465873[103] = 0.0;
   out_3605623673578465873[104] = 0.0;
   out_3605623673578465873[105] = 0.0;
   out_3605623673578465873[106] = 0.0;
   out_3605623673578465873[107] = 0.0;
   out_3605623673578465873[108] = 0.0;
   out_3605623673578465873[109] = 0.0;
   out_3605623673578465873[110] = 0.0;
   out_3605623673578465873[111] = 0.0;
   out_3605623673578465873[112] = 0.0;
   out_3605623673578465873[113] = 0.0;
   out_3605623673578465873[114] = 1.0;
   out_3605623673578465873[115] = 0.0;
   out_3605623673578465873[116] = 0.0;
   out_3605623673578465873[117] = 0.0;
   out_3605623673578465873[118] = 0.0;
   out_3605623673578465873[119] = 0.0;
   out_3605623673578465873[120] = 0.0;
   out_3605623673578465873[121] = 0.0;
   out_3605623673578465873[122] = 0.0;
   out_3605623673578465873[123] = 0.0;
   out_3605623673578465873[124] = 0.0;
   out_3605623673578465873[125] = 0.0;
   out_3605623673578465873[126] = 0.0;
   out_3605623673578465873[127] = 0.0;
   out_3605623673578465873[128] = 0.0;
   out_3605623673578465873[129] = 0.0;
   out_3605623673578465873[130] = 0.0;
   out_3605623673578465873[131] = 0.0;
   out_3605623673578465873[132] = 0.0;
   out_3605623673578465873[133] = 1.0;
   out_3605623673578465873[134] = 0.0;
   out_3605623673578465873[135] = 0.0;
   out_3605623673578465873[136] = 0.0;
   out_3605623673578465873[137] = 0.0;
   out_3605623673578465873[138] = 0.0;
   out_3605623673578465873[139] = 0.0;
   out_3605623673578465873[140] = 0.0;
   out_3605623673578465873[141] = 0.0;
   out_3605623673578465873[142] = 0.0;
   out_3605623673578465873[143] = 0.0;
   out_3605623673578465873[144] = 0.0;
   out_3605623673578465873[145] = 0.0;
   out_3605623673578465873[146] = 0.0;
   out_3605623673578465873[147] = 0.0;
   out_3605623673578465873[148] = 0.0;
   out_3605623673578465873[149] = 0.0;
   out_3605623673578465873[150] = 0.0;
   out_3605623673578465873[151] = 0.0;
   out_3605623673578465873[152] = 1.0;
   out_3605623673578465873[153] = 0.0;
   out_3605623673578465873[154] = 0.0;
   out_3605623673578465873[155] = 0.0;
   out_3605623673578465873[156] = 0.0;
   out_3605623673578465873[157] = 0.0;
   out_3605623673578465873[158] = 0.0;
   out_3605623673578465873[159] = 0.0;
   out_3605623673578465873[160] = 0.0;
   out_3605623673578465873[161] = 0.0;
   out_3605623673578465873[162] = 0.0;
   out_3605623673578465873[163] = 0.0;
   out_3605623673578465873[164] = 0.0;
   out_3605623673578465873[165] = 0.0;
   out_3605623673578465873[166] = 0.0;
   out_3605623673578465873[167] = 0.0;
   out_3605623673578465873[168] = 0.0;
   out_3605623673578465873[169] = 0.0;
   out_3605623673578465873[170] = 0.0;
   out_3605623673578465873[171] = 1.0;
   out_3605623673578465873[172] = 0.0;
   out_3605623673578465873[173] = 0.0;
   out_3605623673578465873[174] = 0.0;
   out_3605623673578465873[175] = 0.0;
   out_3605623673578465873[176] = 0.0;
   out_3605623673578465873[177] = 0.0;
   out_3605623673578465873[178] = 0.0;
   out_3605623673578465873[179] = 0.0;
   out_3605623673578465873[180] = 0.0;
   out_3605623673578465873[181] = 0.0;
   out_3605623673578465873[182] = 0.0;
   out_3605623673578465873[183] = 0.0;
   out_3605623673578465873[184] = 0.0;
   out_3605623673578465873[185] = 0.0;
   out_3605623673578465873[186] = 0.0;
   out_3605623673578465873[187] = 0.0;
   out_3605623673578465873[188] = 0.0;
   out_3605623673578465873[189] = 0.0;
   out_3605623673578465873[190] = 1.0;
   out_3605623673578465873[191] = 0.0;
   out_3605623673578465873[192] = 0.0;
   out_3605623673578465873[193] = 0.0;
   out_3605623673578465873[194] = 0.0;
   out_3605623673578465873[195] = 0.0;
   out_3605623673578465873[196] = 0.0;
   out_3605623673578465873[197] = 0.0;
   out_3605623673578465873[198] = 0.0;
   out_3605623673578465873[199] = 0.0;
   out_3605623673578465873[200] = 0.0;
   out_3605623673578465873[201] = 0.0;
   out_3605623673578465873[202] = 0.0;
   out_3605623673578465873[203] = 0.0;
   out_3605623673578465873[204] = 0.0;
   out_3605623673578465873[205] = 0.0;
   out_3605623673578465873[206] = 0.0;
   out_3605623673578465873[207] = 0.0;
   out_3605623673578465873[208] = 0.0;
   out_3605623673578465873[209] = 1.0;
   out_3605623673578465873[210] = 0.0;
   out_3605623673578465873[211] = 0.0;
   out_3605623673578465873[212] = 0.0;
   out_3605623673578465873[213] = 0.0;
   out_3605623673578465873[214] = 0.0;
   out_3605623673578465873[215] = 0.0;
   out_3605623673578465873[216] = 0.0;
   out_3605623673578465873[217] = 0.0;
   out_3605623673578465873[218] = 0.0;
   out_3605623673578465873[219] = 0.0;
   out_3605623673578465873[220] = 0.0;
   out_3605623673578465873[221] = 0.0;
   out_3605623673578465873[222] = 0.0;
   out_3605623673578465873[223] = 0.0;
   out_3605623673578465873[224] = 0.0;
   out_3605623673578465873[225] = 0.0;
   out_3605623673578465873[226] = 0.0;
   out_3605623673578465873[227] = 0.0;
   out_3605623673578465873[228] = 1.0;
   out_3605623673578465873[229] = 0.0;
   out_3605623673578465873[230] = 0.0;
   out_3605623673578465873[231] = 0.0;
   out_3605623673578465873[232] = 0.0;
   out_3605623673578465873[233] = 0.0;
   out_3605623673578465873[234] = 0.0;
   out_3605623673578465873[235] = 0.0;
   out_3605623673578465873[236] = 0.0;
   out_3605623673578465873[237] = 0.0;
   out_3605623673578465873[238] = 0.0;
   out_3605623673578465873[239] = 0.0;
   out_3605623673578465873[240] = 0.0;
   out_3605623673578465873[241] = 0.0;
   out_3605623673578465873[242] = 0.0;
   out_3605623673578465873[243] = 0.0;
   out_3605623673578465873[244] = 0.0;
   out_3605623673578465873[245] = 0.0;
   out_3605623673578465873[246] = 0.0;
   out_3605623673578465873[247] = 1.0;
   out_3605623673578465873[248] = 0.0;
   out_3605623673578465873[249] = 0.0;
   out_3605623673578465873[250] = 0.0;
   out_3605623673578465873[251] = 0.0;
   out_3605623673578465873[252] = 0.0;
   out_3605623673578465873[253] = 0.0;
   out_3605623673578465873[254] = 0.0;
   out_3605623673578465873[255] = 0.0;
   out_3605623673578465873[256] = 0.0;
   out_3605623673578465873[257] = 0.0;
   out_3605623673578465873[258] = 0.0;
   out_3605623673578465873[259] = 0.0;
   out_3605623673578465873[260] = 0.0;
   out_3605623673578465873[261] = 0.0;
   out_3605623673578465873[262] = 0.0;
   out_3605623673578465873[263] = 0.0;
   out_3605623673578465873[264] = 0.0;
   out_3605623673578465873[265] = 0.0;
   out_3605623673578465873[266] = 1.0;
   out_3605623673578465873[267] = 0.0;
   out_3605623673578465873[268] = 0.0;
   out_3605623673578465873[269] = 0.0;
   out_3605623673578465873[270] = 0.0;
   out_3605623673578465873[271] = 0.0;
   out_3605623673578465873[272] = 0.0;
   out_3605623673578465873[273] = 0.0;
   out_3605623673578465873[274] = 0.0;
   out_3605623673578465873[275] = 0.0;
   out_3605623673578465873[276] = 0.0;
   out_3605623673578465873[277] = 0.0;
   out_3605623673578465873[278] = 0.0;
   out_3605623673578465873[279] = 0.0;
   out_3605623673578465873[280] = 0.0;
   out_3605623673578465873[281] = 0.0;
   out_3605623673578465873[282] = 0.0;
   out_3605623673578465873[283] = 0.0;
   out_3605623673578465873[284] = 0.0;
   out_3605623673578465873[285] = 1.0;
   out_3605623673578465873[286] = 0.0;
   out_3605623673578465873[287] = 0.0;
   out_3605623673578465873[288] = 0.0;
   out_3605623673578465873[289] = 0.0;
   out_3605623673578465873[290] = 0.0;
   out_3605623673578465873[291] = 0.0;
   out_3605623673578465873[292] = 0.0;
   out_3605623673578465873[293] = 0.0;
   out_3605623673578465873[294] = 0.0;
   out_3605623673578465873[295] = 0.0;
   out_3605623673578465873[296] = 0.0;
   out_3605623673578465873[297] = 0.0;
   out_3605623673578465873[298] = 0.0;
   out_3605623673578465873[299] = 0.0;
   out_3605623673578465873[300] = 0.0;
   out_3605623673578465873[301] = 0.0;
   out_3605623673578465873[302] = 0.0;
   out_3605623673578465873[303] = 0.0;
   out_3605623673578465873[304] = 1.0;
   out_3605623673578465873[305] = 0.0;
   out_3605623673578465873[306] = 0.0;
   out_3605623673578465873[307] = 0.0;
   out_3605623673578465873[308] = 0.0;
   out_3605623673578465873[309] = 0.0;
   out_3605623673578465873[310] = 0.0;
   out_3605623673578465873[311] = 0.0;
   out_3605623673578465873[312] = 0.0;
   out_3605623673578465873[313] = 0.0;
   out_3605623673578465873[314] = 0.0;
   out_3605623673578465873[315] = 0.0;
   out_3605623673578465873[316] = 0.0;
   out_3605623673578465873[317] = 0.0;
   out_3605623673578465873[318] = 0.0;
   out_3605623673578465873[319] = 0.0;
   out_3605623673578465873[320] = 0.0;
   out_3605623673578465873[321] = 0.0;
   out_3605623673578465873[322] = 0.0;
   out_3605623673578465873[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8195462837691250934) {
   out_8195462837691250934[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8195462837691250934[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8195462837691250934[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8195462837691250934[3] = dt*state[12] + state[3];
   out_8195462837691250934[4] = dt*state[13] + state[4];
   out_8195462837691250934[5] = dt*state[14] + state[5];
   out_8195462837691250934[6] = state[6];
   out_8195462837691250934[7] = state[7];
   out_8195462837691250934[8] = state[8];
   out_8195462837691250934[9] = state[9];
   out_8195462837691250934[10] = state[10];
   out_8195462837691250934[11] = state[11];
   out_8195462837691250934[12] = state[12];
   out_8195462837691250934[13] = state[13];
   out_8195462837691250934[14] = state[14];
   out_8195462837691250934[15] = state[15];
   out_8195462837691250934[16] = state[16];
   out_8195462837691250934[17] = state[17];
}
void F_fun(double *state, double dt, double *out_613318021964956292) {
   out_613318021964956292[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_613318021964956292[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_613318021964956292[2] = 0;
   out_613318021964956292[3] = 0;
   out_613318021964956292[4] = 0;
   out_613318021964956292[5] = 0;
   out_613318021964956292[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_613318021964956292[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_613318021964956292[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_613318021964956292[9] = 0;
   out_613318021964956292[10] = 0;
   out_613318021964956292[11] = 0;
   out_613318021964956292[12] = 0;
   out_613318021964956292[13] = 0;
   out_613318021964956292[14] = 0;
   out_613318021964956292[15] = 0;
   out_613318021964956292[16] = 0;
   out_613318021964956292[17] = 0;
   out_613318021964956292[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_613318021964956292[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_613318021964956292[20] = 0;
   out_613318021964956292[21] = 0;
   out_613318021964956292[22] = 0;
   out_613318021964956292[23] = 0;
   out_613318021964956292[24] = 0;
   out_613318021964956292[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_613318021964956292[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_613318021964956292[27] = 0;
   out_613318021964956292[28] = 0;
   out_613318021964956292[29] = 0;
   out_613318021964956292[30] = 0;
   out_613318021964956292[31] = 0;
   out_613318021964956292[32] = 0;
   out_613318021964956292[33] = 0;
   out_613318021964956292[34] = 0;
   out_613318021964956292[35] = 0;
   out_613318021964956292[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_613318021964956292[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_613318021964956292[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_613318021964956292[39] = 0;
   out_613318021964956292[40] = 0;
   out_613318021964956292[41] = 0;
   out_613318021964956292[42] = 0;
   out_613318021964956292[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_613318021964956292[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_613318021964956292[45] = 0;
   out_613318021964956292[46] = 0;
   out_613318021964956292[47] = 0;
   out_613318021964956292[48] = 0;
   out_613318021964956292[49] = 0;
   out_613318021964956292[50] = 0;
   out_613318021964956292[51] = 0;
   out_613318021964956292[52] = 0;
   out_613318021964956292[53] = 0;
   out_613318021964956292[54] = 0;
   out_613318021964956292[55] = 0;
   out_613318021964956292[56] = 0;
   out_613318021964956292[57] = 1;
   out_613318021964956292[58] = 0;
   out_613318021964956292[59] = 0;
   out_613318021964956292[60] = 0;
   out_613318021964956292[61] = 0;
   out_613318021964956292[62] = 0;
   out_613318021964956292[63] = 0;
   out_613318021964956292[64] = 0;
   out_613318021964956292[65] = 0;
   out_613318021964956292[66] = dt;
   out_613318021964956292[67] = 0;
   out_613318021964956292[68] = 0;
   out_613318021964956292[69] = 0;
   out_613318021964956292[70] = 0;
   out_613318021964956292[71] = 0;
   out_613318021964956292[72] = 0;
   out_613318021964956292[73] = 0;
   out_613318021964956292[74] = 0;
   out_613318021964956292[75] = 0;
   out_613318021964956292[76] = 1;
   out_613318021964956292[77] = 0;
   out_613318021964956292[78] = 0;
   out_613318021964956292[79] = 0;
   out_613318021964956292[80] = 0;
   out_613318021964956292[81] = 0;
   out_613318021964956292[82] = 0;
   out_613318021964956292[83] = 0;
   out_613318021964956292[84] = 0;
   out_613318021964956292[85] = dt;
   out_613318021964956292[86] = 0;
   out_613318021964956292[87] = 0;
   out_613318021964956292[88] = 0;
   out_613318021964956292[89] = 0;
   out_613318021964956292[90] = 0;
   out_613318021964956292[91] = 0;
   out_613318021964956292[92] = 0;
   out_613318021964956292[93] = 0;
   out_613318021964956292[94] = 0;
   out_613318021964956292[95] = 1;
   out_613318021964956292[96] = 0;
   out_613318021964956292[97] = 0;
   out_613318021964956292[98] = 0;
   out_613318021964956292[99] = 0;
   out_613318021964956292[100] = 0;
   out_613318021964956292[101] = 0;
   out_613318021964956292[102] = 0;
   out_613318021964956292[103] = 0;
   out_613318021964956292[104] = dt;
   out_613318021964956292[105] = 0;
   out_613318021964956292[106] = 0;
   out_613318021964956292[107] = 0;
   out_613318021964956292[108] = 0;
   out_613318021964956292[109] = 0;
   out_613318021964956292[110] = 0;
   out_613318021964956292[111] = 0;
   out_613318021964956292[112] = 0;
   out_613318021964956292[113] = 0;
   out_613318021964956292[114] = 1;
   out_613318021964956292[115] = 0;
   out_613318021964956292[116] = 0;
   out_613318021964956292[117] = 0;
   out_613318021964956292[118] = 0;
   out_613318021964956292[119] = 0;
   out_613318021964956292[120] = 0;
   out_613318021964956292[121] = 0;
   out_613318021964956292[122] = 0;
   out_613318021964956292[123] = 0;
   out_613318021964956292[124] = 0;
   out_613318021964956292[125] = 0;
   out_613318021964956292[126] = 0;
   out_613318021964956292[127] = 0;
   out_613318021964956292[128] = 0;
   out_613318021964956292[129] = 0;
   out_613318021964956292[130] = 0;
   out_613318021964956292[131] = 0;
   out_613318021964956292[132] = 0;
   out_613318021964956292[133] = 1;
   out_613318021964956292[134] = 0;
   out_613318021964956292[135] = 0;
   out_613318021964956292[136] = 0;
   out_613318021964956292[137] = 0;
   out_613318021964956292[138] = 0;
   out_613318021964956292[139] = 0;
   out_613318021964956292[140] = 0;
   out_613318021964956292[141] = 0;
   out_613318021964956292[142] = 0;
   out_613318021964956292[143] = 0;
   out_613318021964956292[144] = 0;
   out_613318021964956292[145] = 0;
   out_613318021964956292[146] = 0;
   out_613318021964956292[147] = 0;
   out_613318021964956292[148] = 0;
   out_613318021964956292[149] = 0;
   out_613318021964956292[150] = 0;
   out_613318021964956292[151] = 0;
   out_613318021964956292[152] = 1;
   out_613318021964956292[153] = 0;
   out_613318021964956292[154] = 0;
   out_613318021964956292[155] = 0;
   out_613318021964956292[156] = 0;
   out_613318021964956292[157] = 0;
   out_613318021964956292[158] = 0;
   out_613318021964956292[159] = 0;
   out_613318021964956292[160] = 0;
   out_613318021964956292[161] = 0;
   out_613318021964956292[162] = 0;
   out_613318021964956292[163] = 0;
   out_613318021964956292[164] = 0;
   out_613318021964956292[165] = 0;
   out_613318021964956292[166] = 0;
   out_613318021964956292[167] = 0;
   out_613318021964956292[168] = 0;
   out_613318021964956292[169] = 0;
   out_613318021964956292[170] = 0;
   out_613318021964956292[171] = 1;
   out_613318021964956292[172] = 0;
   out_613318021964956292[173] = 0;
   out_613318021964956292[174] = 0;
   out_613318021964956292[175] = 0;
   out_613318021964956292[176] = 0;
   out_613318021964956292[177] = 0;
   out_613318021964956292[178] = 0;
   out_613318021964956292[179] = 0;
   out_613318021964956292[180] = 0;
   out_613318021964956292[181] = 0;
   out_613318021964956292[182] = 0;
   out_613318021964956292[183] = 0;
   out_613318021964956292[184] = 0;
   out_613318021964956292[185] = 0;
   out_613318021964956292[186] = 0;
   out_613318021964956292[187] = 0;
   out_613318021964956292[188] = 0;
   out_613318021964956292[189] = 0;
   out_613318021964956292[190] = 1;
   out_613318021964956292[191] = 0;
   out_613318021964956292[192] = 0;
   out_613318021964956292[193] = 0;
   out_613318021964956292[194] = 0;
   out_613318021964956292[195] = 0;
   out_613318021964956292[196] = 0;
   out_613318021964956292[197] = 0;
   out_613318021964956292[198] = 0;
   out_613318021964956292[199] = 0;
   out_613318021964956292[200] = 0;
   out_613318021964956292[201] = 0;
   out_613318021964956292[202] = 0;
   out_613318021964956292[203] = 0;
   out_613318021964956292[204] = 0;
   out_613318021964956292[205] = 0;
   out_613318021964956292[206] = 0;
   out_613318021964956292[207] = 0;
   out_613318021964956292[208] = 0;
   out_613318021964956292[209] = 1;
   out_613318021964956292[210] = 0;
   out_613318021964956292[211] = 0;
   out_613318021964956292[212] = 0;
   out_613318021964956292[213] = 0;
   out_613318021964956292[214] = 0;
   out_613318021964956292[215] = 0;
   out_613318021964956292[216] = 0;
   out_613318021964956292[217] = 0;
   out_613318021964956292[218] = 0;
   out_613318021964956292[219] = 0;
   out_613318021964956292[220] = 0;
   out_613318021964956292[221] = 0;
   out_613318021964956292[222] = 0;
   out_613318021964956292[223] = 0;
   out_613318021964956292[224] = 0;
   out_613318021964956292[225] = 0;
   out_613318021964956292[226] = 0;
   out_613318021964956292[227] = 0;
   out_613318021964956292[228] = 1;
   out_613318021964956292[229] = 0;
   out_613318021964956292[230] = 0;
   out_613318021964956292[231] = 0;
   out_613318021964956292[232] = 0;
   out_613318021964956292[233] = 0;
   out_613318021964956292[234] = 0;
   out_613318021964956292[235] = 0;
   out_613318021964956292[236] = 0;
   out_613318021964956292[237] = 0;
   out_613318021964956292[238] = 0;
   out_613318021964956292[239] = 0;
   out_613318021964956292[240] = 0;
   out_613318021964956292[241] = 0;
   out_613318021964956292[242] = 0;
   out_613318021964956292[243] = 0;
   out_613318021964956292[244] = 0;
   out_613318021964956292[245] = 0;
   out_613318021964956292[246] = 0;
   out_613318021964956292[247] = 1;
   out_613318021964956292[248] = 0;
   out_613318021964956292[249] = 0;
   out_613318021964956292[250] = 0;
   out_613318021964956292[251] = 0;
   out_613318021964956292[252] = 0;
   out_613318021964956292[253] = 0;
   out_613318021964956292[254] = 0;
   out_613318021964956292[255] = 0;
   out_613318021964956292[256] = 0;
   out_613318021964956292[257] = 0;
   out_613318021964956292[258] = 0;
   out_613318021964956292[259] = 0;
   out_613318021964956292[260] = 0;
   out_613318021964956292[261] = 0;
   out_613318021964956292[262] = 0;
   out_613318021964956292[263] = 0;
   out_613318021964956292[264] = 0;
   out_613318021964956292[265] = 0;
   out_613318021964956292[266] = 1;
   out_613318021964956292[267] = 0;
   out_613318021964956292[268] = 0;
   out_613318021964956292[269] = 0;
   out_613318021964956292[270] = 0;
   out_613318021964956292[271] = 0;
   out_613318021964956292[272] = 0;
   out_613318021964956292[273] = 0;
   out_613318021964956292[274] = 0;
   out_613318021964956292[275] = 0;
   out_613318021964956292[276] = 0;
   out_613318021964956292[277] = 0;
   out_613318021964956292[278] = 0;
   out_613318021964956292[279] = 0;
   out_613318021964956292[280] = 0;
   out_613318021964956292[281] = 0;
   out_613318021964956292[282] = 0;
   out_613318021964956292[283] = 0;
   out_613318021964956292[284] = 0;
   out_613318021964956292[285] = 1;
   out_613318021964956292[286] = 0;
   out_613318021964956292[287] = 0;
   out_613318021964956292[288] = 0;
   out_613318021964956292[289] = 0;
   out_613318021964956292[290] = 0;
   out_613318021964956292[291] = 0;
   out_613318021964956292[292] = 0;
   out_613318021964956292[293] = 0;
   out_613318021964956292[294] = 0;
   out_613318021964956292[295] = 0;
   out_613318021964956292[296] = 0;
   out_613318021964956292[297] = 0;
   out_613318021964956292[298] = 0;
   out_613318021964956292[299] = 0;
   out_613318021964956292[300] = 0;
   out_613318021964956292[301] = 0;
   out_613318021964956292[302] = 0;
   out_613318021964956292[303] = 0;
   out_613318021964956292[304] = 1;
   out_613318021964956292[305] = 0;
   out_613318021964956292[306] = 0;
   out_613318021964956292[307] = 0;
   out_613318021964956292[308] = 0;
   out_613318021964956292[309] = 0;
   out_613318021964956292[310] = 0;
   out_613318021964956292[311] = 0;
   out_613318021964956292[312] = 0;
   out_613318021964956292[313] = 0;
   out_613318021964956292[314] = 0;
   out_613318021964956292[315] = 0;
   out_613318021964956292[316] = 0;
   out_613318021964956292[317] = 0;
   out_613318021964956292[318] = 0;
   out_613318021964956292[319] = 0;
   out_613318021964956292[320] = 0;
   out_613318021964956292[321] = 0;
   out_613318021964956292[322] = 0;
   out_613318021964956292[323] = 1;
}
void h_4(double *state, double *unused, double *out_7408733835662868600) {
   out_7408733835662868600[0] = state[6] + state[9];
   out_7408733835662868600[1] = state[7] + state[10];
   out_7408733835662868600[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_166183536265441699) {
   out_166183536265441699[0] = 0;
   out_166183536265441699[1] = 0;
   out_166183536265441699[2] = 0;
   out_166183536265441699[3] = 0;
   out_166183536265441699[4] = 0;
   out_166183536265441699[5] = 0;
   out_166183536265441699[6] = 1;
   out_166183536265441699[7] = 0;
   out_166183536265441699[8] = 0;
   out_166183536265441699[9] = 1;
   out_166183536265441699[10] = 0;
   out_166183536265441699[11] = 0;
   out_166183536265441699[12] = 0;
   out_166183536265441699[13] = 0;
   out_166183536265441699[14] = 0;
   out_166183536265441699[15] = 0;
   out_166183536265441699[16] = 0;
   out_166183536265441699[17] = 0;
   out_166183536265441699[18] = 0;
   out_166183536265441699[19] = 0;
   out_166183536265441699[20] = 0;
   out_166183536265441699[21] = 0;
   out_166183536265441699[22] = 0;
   out_166183536265441699[23] = 0;
   out_166183536265441699[24] = 0;
   out_166183536265441699[25] = 1;
   out_166183536265441699[26] = 0;
   out_166183536265441699[27] = 0;
   out_166183536265441699[28] = 1;
   out_166183536265441699[29] = 0;
   out_166183536265441699[30] = 0;
   out_166183536265441699[31] = 0;
   out_166183536265441699[32] = 0;
   out_166183536265441699[33] = 0;
   out_166183536265441699[34] = 0;
   out_166183536265441699[35] = 0;
   out_166183536265441699[36] = 0;
   out_166183536265441699[37] = 0;
   out_166183536265441699[38] = 0;
   out_166183536265441699[39] = 0;
   out_166183536265441699[40] = 0;
   out_166183536265441699[41] = 0;
   out_166183536265441699[42] = 0;
   out_166183536265441699[43] = 0;
   out_166183536265441699[44] = 1;
   out_166183536265441699[45] = 0;
   out_166183536265441699[46] = 0;
   out_166183536265441699[47] = 1;
   out_166183536265441699[48] = 0;
   out_166183536265441699[49] = 0;
   out_166183536265441699[50] = 0;
   out_166183536265441699[51] = 0;
   out_166183536265441699[52] = 0;
   out_166183536265441699[53] = 0;
}
void h_10(double *state, double *unused, double *out_5309858706066724578) {
   out_5309858706066724578[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5309858706066724578[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5309858706066724578[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4037125241597057406) {
   out_4037125241597057406[0] = 0;
   out_4037125241597057406[1] = 9.8100000000000005*cos(state[1]);
   out_4037125241597057406[2] = 0;
   out_4037125241597057406[3] = 0;
   out_4037125241597057406[4] = -state[8];
   out_4037125241597057406[5] = state[7];
   out_4037125241597057406[6] = 0;
   out_4037125241597057406[7] = state[5];
   out_4037125241597057406[8] = -state[4];
   out_4037125241597057406[9] = 0;
   out_4037125241597057406[10] = 0;
   out_4037125241597057406[11] = 0;
   out_4037125241597057406[12] = 1;
   out_4037125241597057406[13] = 0;
   out_4037125241597057406[14] = 0;
   out_4037125241597057406[15] = 1;
   out_4037125241597057406[16] = 0;
   out_4037125241597057406[17] = 0;
   out_4037125241597057406[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4037125241597057406[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4037125241597057406[20] = 0;
   out_4037125241597057406[21] = state[8];
   out_4037125241597057406[22] = 0;
   out_4037125241597057406[23] = -state[6];
   out_4037125241597057406[24] = -state[5];
   out_4037125241597057406[25] = 0;
   out_4037125241597057406[26] = state[3];
   out_4037125241597057406[27] = 0;
   out_4037125241597057406[28] = 0;
   out_4037125241597057406[29] = 0;
   out_4037125241597057406[30] = 0;
   out_4037125241597057406[31] = 1;
   out_4037125241597057406[32] = 0;
   out_4037125241597057406[33] = 0;
   out_4037125241597057406[34] = 1;
   out_4037125241597057406[35] = 0;
   out_4037125241597057406[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4037125241597057406[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4037125241597057406[38] = 0;
   out_4037125241597057406[39] = -state[7];
   out_4037125241597057406[40] = state[6];
   out_4037125241597057406[41] = 0;
   out_4037125241597057406[42] = state[4];
   out_4037125241597057406[43] = -state[3];
   out_4037125241597057406[44] = 0;
   out_4037125241597057406[45] = 0;
   out_4037125241597057406[46] = 0;
   out_4037125241597057406[47] = 0;
   out_4037125241597057406[48] = 0;
   out_4037125241597057406[49] = 0;
   out_4037125241597057406[50] = 1;
   out_4037125241597057406[51] = 0;
   out_4037125241597057406[52] = 0;
   out_4037125241597057406[53] = 1;
}
void h_13(double *state, double *unused, double *out_7326591431181517962) {
   out_7326591431181517962[0] = state[3];
   out_7326591431181517962[1] = state[4];
   out_7326591431181517962[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3378457361597774500) {
   out_3378457361597774500[0] = 0;
   out_3378457361597774500[1] = 0;
   out_3378457361597774500[2] = 0;
   out_3378457361597774500[3] = 1;
   out_3378457361597774500[4] = 0;
   out_3378457361597774500[5] = 0;
   out_3378457361597774500[6] = 0;
   out_3378457361597774500[7] = 0;
   out_3378457361597774500[8] = 0;
   out_3378457361597774500[9] = 0;
   out_3378457361597774500[10] = 0;
   out_3378457361597774500[11] = 0;
   out_3378457361597774500[12] = 0;
   out_3378457361597774500[13] = 0;
   out_3378457361597774500[14] = 0;
   out_3378457361597774500[15] = 0;
   out_3378457361597774500[16] = 0;
   out_3378457361597774500[17] = 0;
   out_3378457361597774500[18] = 0;
   out_3378457361597774500[19] = 0;
   out_3378457361597774500[20] = 0;
   out_3378457361597774500[21] = 0;
   out_3378457361597774500[22] = 1;
   out_3378457361597774500[23] = 0;
   out_3378457361597774500[24] = 0;
   out_3378457361597774500[25] = 0;
   out_3378457361597774500[26] = 0;
   out_3378457361597774500[27] = 0;
   out_3378457361597774500[28] = 0;
   out_3378457361597774500[29] = 0;
   out_3378457361597774500[30] = 0;
   out_3378457361597774500[31] = 0;
   out_3378457361597774500[32] = 0;
   out_3378457361597774500[33] = 0;
   out_3378457361597774500[34] = 0;
   out_3378457361597774500[35] = 0;
   out_3378457361597774500[36] = 0;
   out_3378457361597774500[37] = 0;
   out_3378457361597774500[38] = 0;
   out_3378457361597774500[39] = 0;
   out_3378457361597774500[40] = 0;
   out_3378457361597774500[41] = 1;
   out_3378457361597774500[42] = 0;
   out_3378457361597774500[43] = 0;
   out_3378457361597774500[44] = 0;
   out_3378457361597774500[45] = 0;
   out_3378457361597774500[46] = 0;
   out_3378457361597774500[47] = 0;
   out_3378457361597774500[48] = 0;
   out_3378457361597774500[49] = 0;
   out_3378457361597774500[50] = 0;
   out_3378457361597774500[51] = 0;
   out_3378457361597774500[52] = 0;
   out_3378457361597774500[53] = 0;
}
void h_14(double *state, double *unused, double *out_153623312624921138) {
   out_153623312624921138[0] = state[6];
   out_153623312624921138[1] = state[7];
   out_153623312624921138[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4129424392604926228) {
   out_4129424392604926228[0] = 0;
   out_4129424392604926228[1] = 0;
   out_4129424392604926228[2] = 0;
   out_4129424392604926228[3] = 0;
   out_4129424392604926228[4] = 0;
   out_4129424392604926228[5] = 0;
   out_4129424392604926228[6] = 1;
   out_4129424392604926228[7] = 0;
   out_4129424392604926228[8] = 0;
   out_4129424392604926228[9] = 0;
   out_4129424392604926228[10] = 0;
   out_4129424392604926228[11] = 0;
   out_4129424392604926228[12] = 0;
   out_4129424392604926228[13] = 0;
   out_4129424392604926228[14] = 0;
   out_4129424392604926228[15] = 0;
   out_4129424392604926228[16] = 0;
   out_4129424392604926228[17] = 0;
   out_4129424392604926228[18] = 0;
   out_4129424392604926228[19] = 0;
   out_4129424392604926228[20] = 0;
   out_4129424392604926228[21] = 0;
   out_4129424392604926228[22] = 0;
   out_4129424392604926228[23] = 0;
   out_4129424392604926228[24] = 0;
   out_4129424392604926228[25] = 1;
   out_4129424392604926228[26] = 0;
   out_4129424392604926228[27] = 0;
   out_4129424392604926228[28] = 0;
   out_4129424392604926228[29] = 0;
   out_4129424392604926228[30] = 0;
   out_4129424392604926228[31] = 0;
   out_4129424392604926228[32] = 0;
   out_4129424392604926228[33] = 0;
   out_4129424392604926228[34] = 0;
   out_4129424392604926228[35] = 0;
   out_4129424392604926228[36] = 0;
   out_4129424392604926228[37] = 0;
   out_4129424392604926228[38] = 0;
   out_4129424392604926228[39] = 0;
   out_4129424392604926228[40] = 0;
   out_4129424392604926228[41] = 0;
   out_4129424392604926228[42] = 0;
   out_4129424392604926228[43] = 0;
   out_4129424392604926228[44] = 1;
   out_4129424392604926228[45] = 0;
   out_4129424392604926228[46] = 0;
   out_4129424392604926228[47] = 0;
   out_4129424392604926228[48] = 0;
   out_4129424392604926228[49] = 0;
   out_4129424392604926228[50] = 0;
   out_4129424392604926228[51] = 0;
   out_4129424392604926228[52] = 0;
   out_4129424392604926228[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7475867757860580655) {
  err_fun(nom_x, delta_x, out_7475867757860580655);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6907412215356863750) {
  inv_err_fun(nom_x, true_x, out_6907412215356863750);
}
void pose_H_mod_fun(double *state, double *out_3605623673578465873) {
  H_mod_fun(state, out_3605623673578465873);
}
void pose_f_fun(double *state, double dt, double *out_8195462837691250934) {
  f_fun(state,  dt, out_8195462837691250934);
}
void pose_F_fun(double *state, double dt, double *out_613318021964956292) {
  F_fun(state,  dt, out_613318021964956292);
}
void pose_h_4(double *state, double *unused, double *out_7408733835662868600) {
  h_4(state, unused, out_7408733835662868600);
}
void pose_H_4(double *state, double *unused, double *out_166183536265441699) {
  H_4(state, unused, out_166183536265441699);
}
void pose_h_10(double *state, double *unused, double *out_5309858706066724578) {
  h_10(state, unused, out_5309858706066724578);
}
void pose_H_10(double *state, double *unused, double *out_4037125241597057406) {
  H_10(state, unused, out_4037125241597057406);
}
void pose_h_13(double *state, double *unused, double *out_7326591431181517962) {
  h_13(state, unused, out_7326591431181517962);
}
void pose_H_13(double *state, double *unused, double *out_3378457361597774500) {
  H_13(state, unused, out_3378457361597774500);
}
void pose_h_14(double *state, double *unused, double *out_153623312624921138) {
  h_14(state, unused, out_153623312624921138);
}
void pose_H_14(double *state, double *unused, double *out_4129424392604926228) {
  H_14(state, unused, out_4129424392604926228);
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
