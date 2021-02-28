//
// Created by oliverw on 22.02.21.
//
#include "RiscCpuBaseTest.h"
#include "SingleElfMemory.h"
#include "cmath"
#include "SerialPort.h"
#define INFO_INSTRUCT(ic)  GTEST_COUT << "Competed after " <<  ic << " instructions" << std::endl
#include <algorithm>    // std::any_of
#include "register.h"

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

uint32_t testpc = 0;

bool testbreak_pc(uint32_t i) {return  testpc == i;}


TEST_F(IntegrationTest, OSTest){

    //lets 2 cooperative tasks count against each other
    auto * mem = new SingleElfMemory("riscv-elf/os_test.rv32", MB(64));
    this->memory = mem;
    entry(mem->entry);

    std::vector<uint32_t> breakpoints = {0x0, 0x84000030, 0x84000080, 0x840000a4, 0x8400009c, 0x840000c0, 0x840004fc};
    int counter = 0;
    while (pc != 0x00) {
        testpc = pc;
      /*  if(std::any_of( breakpoints.begin(), breakpoints.end(), &testbreak_pc )) {
            GTEST_COUT << "BREAKPOINT" << std::endl;
        }*/

        single_step();
        if(++counter > 1000000) {break;}
    }

    INFO_INSTRUCT(instuction_count);
    ASSERT_LE(mem->read32(0x84000ad0),1);
    delete mem;
}