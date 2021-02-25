//
// Created by oliverw on 19.02.21.
//

#include <gtest/gtest.h>
#include "RISCVCpu.h"

class ALUTest : public testing::Test , public RISCVCpu {
public:
    Instruction i{};
    ALUTest();
    void SetUp() override {
        entry(0x8000);
    };
    void TearDown() override {
        resetCpu();
    };

    uint32_t test_alu(uint32_t f3, uint32_t f7, uint32_t c1, uint32_t c2);
    uint32_t test_alui(uint32_t f3, uint32_t f7, uint32_t c1, uint32_t c2);

};

ALUTest::ALUTest() :RISCVCpu(nullptr) {}

uint32_t ALUTest::test_alu(uint32_t f3, uint32_t f7, uint32_t c1, uint32_t c2) {
    constexpr uint32_t r1 = 1;
    constexpr uint32_t r2 = 2;
    constexpr uint32_t rd = 3;

    x[r1] = c1;
    x[r2] = c2;
    rType r = {0x33,rd,f3,r1,r2,f7};
    i.r = r;

    //when
    execute(i);

    return x[rd];
}

uint32_t ALUTest::test_alui(uint32_t f3, uint32_t f7, uint32_t c1, uint32_t c2) {
    constexpr uint32_t r1 = 1;
    constexpr uint32_t rd = 3;
    x[r1] = c1;

    if (f7 != 0x20) {
        iType aii = {0x13, rd, f3, r1, c2};
        i.i = aii;
    } else {
        iType aii = {0x13, rd, f3, r1, 0x400| c2 & 0x1F};
        i.i = aii;
    }
    execute(i);
    return x[rd];
}

#define ALU_TEST_(test_name ,a,b,f3,f7, op ) TEST_F(ALUTest, test_name) { ASSERT_EQ(test_alu(f3,f7,a,b), a op b  );  }

ALU_TEST_(AdditionTest, 0x24,0x42,0,0, +);
ALU_TEST_(SubtractTest, 123,321,0,0x20, -);
ALU_TEST_(ShiftLeftLogicalTest, 0x24,5,1,0,  << );
ALU_TEST_(SetLessThenTest, 41,-42,2,0, <);
ALU_TEST_(SetLessThenUnsignedTest, 0x24,0x42,3,0, <);
ALU_TEST_(XORTest, 0x24,0x42,4,0, ^);
ALU_TEST_(ShiftRightLogicalTest, 0x24,2,5,0, >>);
ALU_TEST_(ShiftRightArithmeticTest, -124,2,5,0x20,  >> );
ALU_TEST_(OrTest, 0x24,0x42,6,0x0,  ^ );
ALU_TEST_(AndTest, 0x24,0x42,7,0x0,  & );


#define ALU_TEST_I_(test_name ,a,b,f3,f7, op ) TEST_F(ALUTest, test_name) { ASSERT_EQ(test_alui(f3,f7,a,b), a op b  );  }

ALU_TEST_I_(AdditionTestImm, 0x24,0x42,0,0, +);
ALU_TEST_I_(ShiftLeftLogicalTestImm, 0x24,5,1,0,  << );
ALU_TEST_I_(SetLessThenTestImm, 41,-42,2,0, <);
ALU_TEST_I_(SetLessThenUnsignedTestImm, 0x24,0x42,3,0, <);
ALU_TEST_I_(XORTestImm, 0x24,0x42,4,0, ^);
ALU_TEST_I_(ShiftRightLogicalTestImm, 0x24,2,5,0, >>);
ALU_TEST_I_(ShiftRightArithmeticTestImm, -124,2,5,0x20,  >> );
ALU_TEST_I_(OrTestImm, 0x24,0x42,6,0x0,  ^ );
ALU_TEST_I_(AndTestImm, 0x24,0x42,7,0x0,  & );