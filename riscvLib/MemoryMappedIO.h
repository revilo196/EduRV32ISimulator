//
// Created by oliverw on 23.02.21.
//

#ifndef OW_RISCV_EMU_MEMORYMAPPEDIO_H
#define OW_RISCV_EMU_MEMORYMAPPEDIO_H
#include <cstdint>
#include "instructions.h"

/**
 * MemoryMappedIO describes an Abstract class to read or write into a MemoryMapped device
 *
 */
class MemoryMappedIO {
private:
    uint32_t minAdr;
    uint32_t maxAdr;
public:
    /**
     * Constructor that sets the min and max memory range of the device
     *
     * @param start memory address start of the device
     * @param end memory address end of the device
     */
    MemoryMappedIO(uint32_t start, uint32_t end) {minAdr = start; maxAdr=end;}

    /**
     * reading from a MemoryMappedIO device
     * @param op F3_LoadOp to give the size and type the load instruction (byte,half,word,unsigned)
     * @param adr address to read from
     * @return value returned from device
     */
    virtual uint32_t read(F3_LoadOp op, uint32_t adr) = 0;

    /**
     * writing to a MemoryMappedIO device
     * @param op F3_StoreOp to give the size and type the store instruction (byte,half,word,unsigned)
     * @param adr address to write to
     * @param value value that should be written
     */
    virtual void write(F3_StoreOp op, uint32_t adr, uint32_t value) = 0;

    /**
     * checks if the given address lays in the memory space of this device
     * @param adr address for checking
     * @return true if the device contains this address else false
     */
    bool in_device(uint32_t adr)  {return  minAdr <= adr && adr <= maxAdr; }

};




#endif //OW_RISCV_EMU_MEMORYMAPPEDIO_H
