//
// Created by oliverw on 25.02.21.
//

#ifndef OW_RISCV_EMU_REGISTER_H
#define OW_RISCV_EMU_REGISTER_H

#define r_zero x[0]
#define r_ra x[1]
#define r_sp x[2]
#define r_gp x[3]
#define r_tp x[4]
#define r_t0 x[5]
#define r_t1 x[6]
#define r_t2 x[7]
#define r_s0 x[8]
#define r_fp x[8]
#define r_s1 x[9]
#define r_a(i) x[i+10]
#define r_s2 x[18]
#define r_s3 x[19]
#define r_s4 x[20]
#define r_s5 x[21]
#define r_s6 x[22]
#define r_s7 x[23]
#define r_s8 x[24]
#define r_s9 x[25]
#define r_s10 x[26]
#define r_s11 x[27]
#define r_t3 x[28]
#define r_t4 x[29]
#define r_t5 x[30]
#define r_t6 x[31]

#endif //OW_RISCV_EMU_REGISTER_H
