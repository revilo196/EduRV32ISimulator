//
// Created by oliverw on 23.02.21.
//
#include "SerialPortDriver.h"
#include "stdio.h"

char buffer[64];

int main()
{
    print("Hello World from RISCV32I\n");
    sprintf(buffer, "Let's do some FPRINT Action 0x%x\n", 0x20FFAAB);
    print(buffer);
    return 96;
}
