//
// Created by oliverw on 27.02.21.
//

#ifndef OW_RISCV_EMU_RVOS_TYPES_H
#define OW_RISCV_EMU_RVOS_TYPES_H
#include <stdint.h>

#define MAX_PROC_COUNT 10
#define STACK_SIZE 2048

extern uint32_t sys_tick_counter;

typedef int32_t pid_t;

typedef enum {Init, Ready, Running, Waiting, Terminated} p_state_t;
typedef enum {WTime, WLock, WResource} p_wait_t;

typedef struct {
    uint32_t * sp;
    uint32_t * gp;
    pid_t pid;
    uint32_t interval;
    uint32_t lastrun;
    p_state_t state;
    p_wait_t waitfor;
    int32_t argc;
    int32_t *argv;
    void (*func)(int32_t argc, int32_t argv[]);

    //Memory map
    uint32_t * sp_begin;
    uint32_t * sp_end;
    //For dynamic range checking
    uint32_t * text_begin;
    uint32_t * text_end;
    uint32_t * data_begin;
    uint32_t * data_end;
} pcb_t;



#endif //OW_RISCV_EMU_RVOS_TYPES_H
