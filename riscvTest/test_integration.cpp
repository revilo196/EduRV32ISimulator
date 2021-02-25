//
// Created by oliverw on 22.02.21.
//
#include "RiscCpuBaseTest.h"
#include "SingleElfMemory.h"
#include "cmath"
#include "SerialPort.h"
#define INFO_INSTRUCT(ic)  GTEST_COUT << "Competed after " <<  ic << " instructions" << std::endl

class IntegrationTest : public testing::Test, public RISCVCpu{
public:
    SerialPort port;
    IntegrationTest() : RISCVCpu(nullptr) { this->add_mmio(&port);  }

    void SetUp() override {
        entry(0x0000);
    }
    void TearDown() override {
        resetCpu();
    }
};

TEST_F(IntegrationTest, ReturnExecutonTest){

    auto * mem = new SingleElfMemory("riscv-elf/basic.rv32", MB(64));
    this->memory = mem;
    entry(mem->entry);

    while (pc != 0x00) {
        single_step();
    }

    INFO_INSTRUCT(instuction_count);
    ASSERT_EQ(x[10], 96);
    delete mem;
}

TEST_F(IntegrationTest, ReturnAdditonTest){

    auto * mem = new SingleElfMemory("riscv-elf/add.rv32", MB(64));
    this->memory = mem;
    entry(mem->entry);
    constexpr int32_t a = 54;
    constexpr int32_t b = 61;

    while (pc != 0x00) {
        single_step();
    }

    INFO_INSTRUCT(instuction_count);
    ASSERT_EQ(x[10], a+b);
    delete mem;
}

TEST_F(IntegrationTest, ReturnMultiplicationTest){

    auto * mem = new SingleElfMemory("riscv-elf/mul.rv32", MB(64));
    this->memory = mem;
    entry(mem->entry);
    constexpr int a = 55;
    constexpr int b = 49;

    while (pc != 0x00) {
        single_step();
    }

    INFO_INSTRUCT(instuction_count);
    ASSERT_EQ(x[10], a*b);
    delete mem;
}

TEST_F(IntegrationTest, ReturnRecursiveMultiplicationTest){

    auto * mem = new SingleElfMemory("riscv-elf/add_double.rv32", MB(64));
    this->memory = mem;
    entry(mem->entry);
    constexpr int a = 55;
    constexpr int b = 49;

    while (pc != 0x00) {
        single_step();
    }

    INFO_INSTRUCT(instuction_count);
    ASSERT_EQ(x[10], a*b);
    delete mem;
}

TEST_F(IntegrationTest, ReturnRecursivePowTest){

    auto * mem = new SingleElfMemory("riscv-elf/sqare_mul.rv32", MB(64));
    this->memory = mem;
    entry(mem->entry);
    constexpr int a = 3;
    constexpr int b = 18;

    while (pc != 0x00) {
        single_step();
    }

    INFO_INSTRUCT(instuction_count);
    ASSERT_EQ(x[10],387420489);
    delete mem;
}

TEST_F(IntegrationTest, SerialDiverTest){

    auto * mem = new SingleElfMemory("riscv-elf/serial.rv32", MB(64));
    this->memory = mem;
    entry(mem->entry);

    while (pc != 0x00) {
        single_step();
    }

    INFO_INSTRUCT(instuction_count);
    ASSERT_EQ(x[10],96);
    delete mem;
}