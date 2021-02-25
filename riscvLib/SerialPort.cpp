//
// Created by oliverw on 23.02.21.
//

#include "SerialPort.h"
#include <iostream>

uint32_t SerialPort::read(F3_LoadOp op, uint32_t adr) {
    char c;
    this->in->readsome(&c, 1);
    return c;
}

void SerialPort::write(F3_StoreOp op, uint32_t adr, uint32_t value) {
    this->out->put((char)value);
}

