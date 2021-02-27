//
// Created by oliverw on 27.02.21.
//

#ifndef OW_RISCV_EMU_INTERRUPTS_H
#define OW_RISCV_EMU_INTERRUPTS_H

#define MTIM 7
#define MSIT 3
#define MEIT 11

void enable_interrupt_status();
void enable_interrupt(unsigned int num);
void disable_interrupt_status();
void disable_interrupt(unsigned int num);
void clear_interrupts();
void soft_trap();

#endif //OW_RISCV_EMU_INTERRUPTS_H
