//
// Created by oliverw on 28.02.21.
//

#include "ring_ready_list.h"

int ready_list_empty() {
    return ready_list.read_idx == ready_list.write_idx;
}

int ready_list_full() {
    return ready_list.read_idx == ready_list.write_idx+1 ||
           ready_list.read_idx+MAX_PROC_COUNT == ready_list.write_idx+1;
}

pcb_t* ready_list_get() {
    //ASSERT ready_list.read_idx != ready_list.write_idx //Buffer empty
    pcb_t* value = ready_list.buffer[ready_list.read_idx];
    ready_list.read_idx++;
    if(ready_list.read_idx >= MAX_PROC_COUNT) {ready_list.read_idx= 0;}
    return value;
}

void ready_list_put(pcb_t* p){
    ready_list.buffer[ready_list.write_idx] = p;
    ready_list.write_idx++;
    if(ready_list.write_idx >= MAX_PROC_COUNT) {ready_list.write_idx= 0;}
}