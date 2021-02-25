//
// Created by oliverw on 19.02.21.
//

#include "riscvMemory.h"

RISCVBasicMemory::RISCVBasicMemory(size_t size) {
    data = new char [size];
}

RISCVBasicMemory::~RISCVBasicMemory() {
    delete[] data;
}
