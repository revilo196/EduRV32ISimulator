//
// Created by oliverw on 23.02.21.
//

#ifndef OW_RISCV_EMU_SERIALPORT_H
#define OW_RISCV_EMU_SERIALPORT_H

#include <MemoryMappedIO.h>
#include <iostream>

/**
 * Simulating a SerialPort as a very simple MemoryMapped device
 * using istream and ostream for in and output
 * writing to its one address will put char in the istream
 * reading from its one address will get char from the ostream
 */
class SerialPort : public MemoryMappedIO{
    std::istream * in;
    std::ostream * out;
public:
    uint32_t read(F3_LoadOp op, uint32_t adr) override;
    void write(F3_StoreOp op, uint32_t adr, uint32_t value) override;

    /**
     * creates a SerialPort MemoryMapped device
     * @param address in memory (default:0x10000000)
     * @param in istream* for input (default:std::cin)
     * @param out ostream* for output (defautl:std::cout)
     */
    explicit SerialPort(uint32_t address = 0x10000000, std::istream * in = &std::cin, std::ostream * out = &std::cout)
    : MemoryMappedIO(address,address+1) {
        this->in = in;
        this->out = out;
    }
};


#endif //OW_RISCV_EMU_SERIALPORT_H
