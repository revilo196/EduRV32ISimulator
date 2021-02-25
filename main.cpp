//
// Created by oliverw on 21.02.21.
//
#include "SingleElfMemory.h"
#include "RISCVCpu.h"
#include <string>
#include <sstream>

int main(int argc, char const *argv[])
{
    if(argc < 2) {return 1;}

    size_t s = 64;
    if (argc == 3) {
        std::string size(argv[2]);
        std::stringstream str(size);
        str >> s;
        if (!str) {return 2;}
    }


    SingleElfMemory mem(argv[1], MB(s));
    RISCVCpu cpu(&mem);

    cpu.resetCpu();
    cpu.entry(mem.entry);

    while (cpu.getPC() != 0) {
        printf("PC: %x\n", cpu.getPC());
        cpu.single_step();
    }

    return 0;
}
