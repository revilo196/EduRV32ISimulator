//
// Created by oliverw on 22.02.21.
//
#include "RiscCpuBaseTest.h"
#include <random>

uint32_t rev_imm_j(uint32_t imm) {
    uint32_t r_imm = 0;
    r_imm |= (imm << 11) &  0x80000000;  //MSB
    r_imm |= (imm << 20) &  0x7FE00000;  // 30 - 21
    r_imm |= (imm << 9)  &  0x00100000;  // 20
    r_imm |= (imm) &        0x000FF000;  // 19-12

    r_imm = r_imm >> 12;
    return r_imm;
}


class JumpTest : public RiscCpuBaseTest {
public:
};

TEST_F(JumpTest, r_immBitmaskOk) {
    constexpr uint32_t value = 0xFFFFFFFF;
    constexpr uint32_t expected = 0xFFFFF;
    uint32_t r_immj = rev_imm_j(value);

    ASSERT_EQ(r_immj, expected);
}

TEST_F(JumpTest, r_immFixedOk) {
    constexpr uint32_t value = 0x23456;
    constexpr uint32_t expected = 0x45623;
    uint32_t r_immj = rev_imm_j(value);

    ASSERT_EQ(r_immj, expected);
}

TEST_F(JumpTest, r_immFixed1Ok) {
    constexpr uint32_t value = 0x3B5BA;
    constexpr uint32_t expected = 0x5BA3B;
    uint32_t r_immj = rev_imm_j(value);

    ASSERT_EQ(r_immj, expected);
}

TEST_F(JumpTest, r_immReverseOk) {
    for(uint32_t i = 0; i< 512; i++) {
        uint32_t value = random() & 0xFFFFE;
        uint32_t r_immj = rev_imm_j(value);
        uint32_t _value = imm_j(r_immj);
        ASSERT_EQ(value, _value);
    }
}

TEST_F(JumpTest, JumpAndLinkRelativeTest) {
    //given
    constexpr uint32_t  jumpto = 0x00AABCDE;
    constexpr uint32_t  imm_mask = 0x7FF;
    constexpr uint32_t  rd = 2;
    uint32_t  imm = jumpto & imm_mask;
    x[1] = jumpto & (~imm_mask);

    pc = 0x12345678;

    iType jarl = {JALR, rd,0,1,imm};
    i.i = jarl;
    execute(i);

    ASSERT_EQ(jumpto, pc); //jump destinaiton
    ASSERT_EQ(x[rd], 0x12345678+4); // link register

}

TEST_F(JumpTest, JumpAndLinkRelativeNegativeTest) {
    //given
    constexpr uint32_t  adr = 0x009ABCDE;
    constexpr uint32_t  rd = 2;
    uint32_t  imm = -1234;
    x[1] = adr;

    pc = 0x12345678;

    iType jarl = {JALR, rd,0,1,imm};
    i.i = jarl;
    execute(i);

    ASSERT_EQ(adr+imm, pc); //jump destinaiton
    ASSERT_EQ(x[rd], 0x12345678+4); // link register

}

TEST_F(JumpTest, JumpAndLinkRelativeSameRegisterTest) {
    //given
    constexpr uint32_t  jumpto = 0x009ABCDE;
    constexpr uint32_t  imm_mask = 0x7FF;
    constexpr uint32_t  rd = 2;
    uint32_t  imm = jumpto & imm_mask;
    x[rd] = jumpto & (~imm_mask);

    pc = 0x12345678;

    iType jarl = {JALR, rd,0,rd,imm};
    i.i = jarl;
    execute(i);

    ASSERT_EQ(jumpto, pc); //jump destinaiton
    ASSERT_EQ(x[rd], 0x12345678+4); // link register

}

TEST_F(JumpTest, JumpAndLink) {
    constexpr uint32_t  jumpto = 0x0000BCDE;
    constexpr uint32_t  rd = 2;
    uint32_t rimm_j = rev_imm_j(jumpto);
    uint32_t pc_prev = (pc = 0x12345678);

    jType jal = {JAL, rd,rimm_j};
    i.j = jal;
    execute(i);

    ASSERT_EQ(pc_prev+jumpto, pc); //jump destinaiton
    ASSERT_EQ(x[rd], 0x12345678+4); // link register
}