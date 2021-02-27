//
// Created by oliverw on 27.02.21.
//


#include "interrupts.h"

int data = 0;

int main() {

    clear_interrupts();
    enable_interrupt_status();
    enable_interrupt(MSIT);

    soft_trap();

    return data;

}

void softTrapHandler(int a) {
    data = 1;
    clear_interrupts();
}