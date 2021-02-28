//
// Created by oliverw on 28.02.21.
//

#include "rvos_types.h"
#include "ring_ready_list.h"
#include "HardwareTimer.h"


uint32_t sys_tick_counter = 0;
uint32_t stack_memory[MAX_PROC_COUNT][STACK_SIZE];
pcb_t proc_table[MAX_PROC_COUNT];
ready_ring_list_type ready_list;

pcb_t * current_task;
pcb_t * next_task;
pcb_t * last_task;

void switchContext(pcb_t * old, pcb_t * new);
void firstContext(pcb_t * new);


void init_os(void) {
    for(int  i = 0; i < MAX_PROC_COUNT; i++) {
        proc_table[i].pid = -1;
        proc_table[i].func = 0;
    }
}


void update_proc(){
    uint32_t current_time = (uint32_t)TIMER->mtime;
    //update waiting tasks from the tick counter
    for(int  i = 0; i < MAX_PROC_COUNT; i++) {
        // check all waiting proc for changes
        if(proc_table[i].pid  > -1 && proc_table[i].state == Waiting) {
            if (proc_table[i].lastrun + proc_table[i].interval <= current_time ) {
                if (!ready_list_full()) {
                    ready_list_put(proc_table+i);
                    proc_table[i].state = Ready;
                }
            }
        }
    }
}

void yield() {
    uint32_t current_time = (uint32_t)TIMER->mtime;
    update_proc();

    while (ready_list_empty()) {
        update_proc();
        //idle task;
    }

    next_task = ready_list_get();

    if (current_task->interval > 0) {
        current_task->state = Waiting;
        current_task->lastrun = current_time;
    } else {
        current_task->state = Ready;
        ready_list_put(current_task);
    }

    last_task = current_task;
    current_task = next_task;

    switchContext(last_task, current_task);
}

void wait(unsigned int t) {
    current_task->interval = t;
    yield();
}

void stop() {
    current_task->state = Terminated;
    yield();
}

pid_t create(void (*func)(int32_t argc, int32_t argv[]), int32_t argc, int32_t argv[], uint16_t interval) {
    for(int  i = 0; i < MAX_PROC_COUNT; i++) {
        if(proc_table[i].pid == -1) {
            proc_table[i].pid = i;
            proc_table[i].func = func;
            proc_table[i].interval = interval;
            proc_table[i].argc = argc;
            proc_table[i].argv = argv;
            proc_table[i].sp = &stack_memory[i][STACK_SIZE-1];
            proc_table[i].sp_end =  &stack_memory[i][STACK_SIZE-1];
            proc_table[i].sp_begin =  &stack_memory[i][0];
            proc_table[i].state = Init;
            proc_table[i].sp  = proc_table[i].sp +32; //increment to fit a full stack frame

            proc_table[i].sp[0] = (uint32_t)func; //pc;
            proc_table[i].sp[1] = (uint32_t)&stop; //ra
            proc_table[i].sp[2] = 0; //t0
            proc_table[i].sp[3] = 0; //t1
            proc_table[i].sp[4] = 0; //t3
            proc_table[i].sp[5] = (uint32_t)argc; //a0
            proc_table[i].sp[6] = (uint32_t)argv; //a1
            //rest is left as zero

            proc_table[i].state = Ready;
            ready_list_put(&proc_table[i]);
            return i;
        }
    }
    return 0;
    }

    void start() {
        current_task = ready_list_get();
        current_task->state = Running;
        firstContext(current_task);
    }
