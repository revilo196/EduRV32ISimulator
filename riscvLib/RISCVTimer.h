//
// Created by oliverw on 25.02.21.
//

#ifndef OW_RISCV_EMU_RISCVTIMER_H
#define OW_RISCV_EMU_RISCVTIMER_H
#include "MemoryMappedIO.h"
#include "riscvMemory.h"

typedef struct memtime_s {
    uint64_t mtime;
    uint64_t mtimecmp;
} memtime_t;

/**
 * Simulated mtime mtimecmp mmio timer
 * can be run with signals/interrupts using the increment functions
 * or updated each instruction by polling system time
 */
class RISCVTimer : public MemoryMappedIO, private RISCVMemory {
protected:
    memtime_t mem; // <- this is accessible to the simulated proc via mmio
    Address base;  // <- accessible at this address

    uint64_t lastUpdateTime;
    [[nodiscard]] char * lookup(Address adr) const override {return (((char*)&mem)+(adr-base));}
public:
    uint32_t read(F3_LoadOp op, uint32_t adr) override;
    void write(F3_StoreOp op, uint32_t adr, uint32_t value) override;
    explicit RISCVTimer(uint32_t address = 0x00004000);

    int increment();
    int update();
};


#endif //OW_RISCV_EMU_RISCVTIMER_H
