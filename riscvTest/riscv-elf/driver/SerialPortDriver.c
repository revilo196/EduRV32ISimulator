//
// Created by oliverw on 23.02.21.
//
#include "SerialPortDriver.h"

int print(const char * s) {
    char c;
    unsigned int i = 0;
    while ((c = s[i]) != 0) {
        (*SERIAL_PORT) = c;
        i++;
    }
}