//
// Created by oliverw on 19.02.21.
//

#ifndef OW_RISCV_EMU_RISCVCPU_H
#define OW_RISCV_EMU_RISCVCPU_H
#include <cstdint>
#include "instructions.h"
#include "riscvMemory.h"

#include "MemoryMappedIO.h"
#include <vector>

//Register length
#define XLEN 32

//Memory reserved for io
#define IO_MAX 0x20000000



class RISCVCpu {

private:
    // private functions to delegate opcodes
    iec load(iType li);
    iec store(sType si);
    iec branch(bType bi);
    iec jal(jType ji);
    iec jalr (iType jii);
    iec alu_imm(iType aii);
    iec alu(rType ri);
    iec lui(uType ui);
    iec auipc(uType ui);

    // access Memory mapped devices
    uint32_t read_io(F3_LoadOp op, uint32_t addr, iec& excep ) ;
    iec write_io(F3_StoreOp op, uint32_t addr, uint32_t value);

protected:
    RISCVMemory * memory;
    std::vector<MemoryMappedIO*> mmio;
    uint32_t x[32]{};
    uint32_t pc{};
    uint32_t instuction_count{};
    uint32_t csr[0x1000];
    Instruction fetch();
    virtual iec run_instruction(Instruction i);

    void execute(Instruction i);
    void exception(InstructionExceptionCode code);
    int check_local_interrupt();
    void interupt();


public:
    explicit RISCVCpu(RISCVMemory* mem)  {this->memory = mem;}
    void resetCpu();
    void single_step();
    void entry(uint32_t pc_start) { this->pc = pc_start;}
    uint32_t getPC() const {return pc;}
    void add_mmio(MemoryMappedIO * m) {mmio.push_back(m);}



};


#endif //OW_RISCV_EMU_RISCVCPU_H
