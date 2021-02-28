//
// Created by oliverw on 28.02.21.
//

#ifndef OW_RISCV_EMU_RING_READY_LIST_H
#define OW_RISCV_EMU_RING_READY_LIST_H
#include "rvos_types.h"

typedef struct{
    pcb_t * buffer[MAX_PROC_COUNT];
    uint32_t write_idx;
    uint32_t read_idx;
} ready_ring_list_type;

extern ready_ring_list_type ready_list;

int ready_list_empty();
int ready_list_full();
pcb_t * ready_list_get();
void ready_list_put(pcb_t * p);

#endif //OW_RISCV_EMU_RING_READY_LIST_H
