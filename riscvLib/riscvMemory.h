//
// Created by oliverw on 19.02.21.
//

#ifndef OW_RISCV_EMU_RISCVMEMORY_H
#define OW_RISCV_EMU_RISCVMEMORY_H

#include <cstdint>
#include <cstddef>

#define KB(x) 1024*x
#define MB(x) KB(x)*1024

typedef uint32_t Address;

/**
 * Abstract class for defining a Memory, using a easy to implement lookup function
 * the lookup funtion takes an address from the RISC-V memoryspace and gives back a pointer to where this values is in
 * this simulated memory
 */
class RISCVMemory {
protected:
    [[nodiscard]] virtual char *lookup(Address adr) const = 0;
public:
    /** read a 32bit value from memory at given address */
    virtual uint32_t read32(Address adr)  {return *(uint32_t*)(lookup(adr)); }
    /** read a 16bit value from memory at given address */
    virtual uint16_t read16(Address adr)  {return *((uint16_t*)(lookup(adr)));}
    /** read a 8bit value from memory at given address */
    virtual uint8_t  read08(Address adr)  {return *lookup(adr);}

    /** writes a 32bit value to memory ad given address */
    virtual void write32(uint32_t value, Address adr)  {*((uint32_t *)(lookup(adr))) = value;};
    /** writes a 16bit value to memory ad given address */
    virtual void write16(uint16_t value, Address adr)  { *((uint16_t*)(lookup(adr))) = value;};
    /** writes a 8bit value to memory ad given address */
    virtual void write08(uint8_t value, Address adr)  {(*lookup(adr))=value;};

    /** operator[] for easy 32bit access to the memory  -- address is still in bytes! */
    virtual uint32_t operator[] (Address adr) const  {return *(uint32_t*)(lookup(adr));};

    /** operator[] for easy 32bit access to the memory  -- address is still in bytes! */
    virtual uint32_t& operator[] (Address adr)  {return *(uint32_t*)(lookup(adr)); };

};

/**
 * Simple RISCVMemory memory implementations, RISC-V address as index of an char array in memory
 */
class RISCVBasicMemory : public RISCVMemory {
private:
    char * data;
protected:
    [[nodiscard]] char * lookup(Address adr) const override {return  (data+adr);}
public:
    explicit RISCVBasicMemory(size_t size);
    ~RISCVBasicMemory();

};


#endif //OW_RISCV_EMU_RISCVMEMORY_H
