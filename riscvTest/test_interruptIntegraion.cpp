//
// Created by oliverw on 27.02.21.
//

#include "RiscCpuBaseTest.h"
#include "SingleElfMemory.h"
#include "RISCVTimer.h"
#include "SerialPort.h"
#define INFO_INSTRUCT(ic)  GTEST_COUT << "Competed after " <<  ic << " instructions" << std::endl

class InterruptIntegrationTest : public testing::Test, public RISCVCpu{
public:
    SerialPort port;
    RISCVTimer rvTimer;
    InterruptIntegrationTest() : rvTimer(0x0004000), RISCVCpu(nullptr)
    { this->add_mmio(&port); this->add_mmio(&rvTimer); }

    void SetUp() override {
        entry(0x0000);
    }
    void TearDown() override {
        resetCpu();
    }
};

TEST_F(InterruptIntegrationTest, ReturnExecutonTest){

    auto * mem = new SingleElfMemory("riscv-elf/env_call.rv32", MB(64));
    this->memory = mem;
    entry(mem->entry);

    while (pc != 0x00) {
        rvTimer.update();
        single_step();
    }

    INFO_INSTRUCT(instuction_count);
    ASSERT_EQ(x[10], 150);
    delete mem;
}

TEST_F(InterruptIntegrationTest, ReturnTimerTest){

    auto * mem = new SingleElfMemory("riscv-elf/timer_intr.rv32", MB(64));
    this->memory = mem;
    entry(mem->entry);

    while (pc != 0x00) {
        rvTimer.update();
        single_step();
    }

    INFO_INSTRUCT(instuction_count);
    ASSERT_GT(x[10], 32);
    delete mem;
}

TEST_F(InterruptIntegrationTest, ReturnSoftTest){

    auto * mem = new SingleElfMemory("riscv-elf/sw_trap.rv32", MB(64));
    this->memory = mem;
    entry(mem->entry);

    while (pc != 0x00) {
        rvTimer.update();
        single_step();
    }

    INFO_INSTRUCT(instuction_count);
    ASSERT_EQ(x[10], 1);
    delete mem;
}