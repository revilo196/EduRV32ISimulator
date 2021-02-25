//
// Created by oliverw on 22.02.21.
//

#ifndef OW_RISCV_EMU_RISCCPUBASETEST_H
#define OW_RISCV_EMU_RISCCPUBASETEST_H

#include <riscvMemory.h>
#include <RISCVCpu.h>
#include <gtest/gtest.h>

#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

class RiscCpuBaseTest : public testing::Test , public RISCVCpu {
public:
    static constexpr uint32_t msize = MB(8);
    Instruction i{};
    RISCVBasicMemory mem;
    RiscCpuBaseTest() : RISCVCpu(&mem), mem(msize) {}

    /**
     * init memory to max 0xFFFFFFFF
     */
    void init_mem(){
        for (unsigned int j = 0; j < msize ; j+=4 ) {
            mem[j] = 0xFFFFFFFF;
        }
    }
    void SetUp() override {
        init_mem();
        entry(0x0000);
    }
    void TearDown() override {
        resetCpu();
    }

};




#endif //OW_RISCV_EMU_RISCCPUBASETEST_H
