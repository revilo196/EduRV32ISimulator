//
// Created by oliverw on 28.02.21.
//

#include "rvos.h"

int data = 0;

void task0 (int32_t argc, int32_t arcv []) {
    halt(123,321);
}


_Noreturn void task1 (int32_t argc, int32_t arcv []) {
    while (1) {
        data++;
        yield();
    }
}

_Noreturn void task2(int32_t argc, int32_t arcv []) {
    while (1) {
        data --;
        yield();
    }
}


int main() {
    init_os();
    //create(&task0, 0,0,0);
    create(&task1, 0,0,0);
    create(&task2, 0,0,0);

    start();
    return 0;
}


