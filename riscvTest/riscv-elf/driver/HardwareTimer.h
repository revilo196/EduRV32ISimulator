//
// Created by oliverw on 27.02.21.
//

#ifndef OW_RISCV_EMU_HARDWARETIMER_H
#define OW_RISCV_EMU_HARDWARETIMER_H

typedef struct {
    uint64_t mtime;
    uint64_t mtimecmp;
} memtime_t;

#define TIMER ((memtime_t*)(0x00004000))

#endif //OW_RISCV_EMU_HARDWARETIMER_H
