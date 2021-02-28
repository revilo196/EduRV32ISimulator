//
// Created by oliverw on 28.02.21.
//

#ifndef OW_RISCV_EMU_RVOS_H
#define OW_RISCV_EMU_RVOS_H
#include "rvos_types.h"

void init_os(void);
void start();
pid_t create(void (*func)(int32_t argc, int32_t argv[]), int32_t argc, int32_t argv[], uint16_t interval);

void halt(int code_a, int code_b);

void yield();
void wait(unsigned int t);
void stop();

#endif //OW_RISCV_EMU_RVOS_H
