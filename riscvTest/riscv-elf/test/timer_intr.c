//
// Created by oliverw on 27.02.21.
//
#include <stdint.h>
#include "interrupts.h"
#include "HardwareTimer.h"

int data = 0;

int main() {
    TIMER->mtimecmp = 0x100000;
    TIMER->mtime = 0;
    clear_interrupts();
    enable_interrupt_status();
    enable_interrupt(MTIM);

    int a = 0;
    while (data == 0) {
        a+=64;
    }
    return a+data;
}

void timerHandler(int a) {
    TIMER->mtimecmp = 0xFFFFFFFFFFFFFFFF;
    TIMER->mtime = 0;
    data = 32;
    clear_interrupts();
}