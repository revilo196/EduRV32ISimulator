//
// Created by oliverw on 27.02.21.
//
#include "ecall.h"

int data;

int main () {
    data = 0;

    while (data == 0) {
        envcall();
    }
    return data;
}

int exceptionHandler(int a) {
    data = 150;
}