//
// Created by oliverw on 22.02.21.
//
#include "RiscCpuBaseTest.h"

void rev_imm_b(uint32_t imm, uint32_t& imm_L, uint32_t& imm_U) {
    imm_L =  imm & 0x1E;
    imm_L |= (imm >> 11) & 0x01;
    imm_U = (imm >> 5)  & 0x3f;
    imm_U |= (imm >> 6) & 0x40;
}

#define ASSERT_BRANCH(rel) ASSERT_EQ(pc, pc_s+rel);
#define ASSERT_NO_BRANCH() ASSERT_EQ(pc, pc_s+4);


class BranchTest : public RiscCpuBaseTest {
public:
    static constexpr uint32_t r1 = 1;
    static constexpr uint32_t r2 = 2;
    static constexpr uint32_t pc_s = 0x800;
    static constexpr uint32_t rel = 0xA0;
    static constexpr uint32_t n_rel = -4*7;

    void execute_branch(F3_BranchOp op, uint32_t rs1, uint32_t rs2, uint32_t relative) {
        uint32_t imm_L, imm_U;
        rev_imm_b(relative, imm_L, imm_U);
        bType b = {BRANCH, imm_L, op, rs1,rs2, imm_U};
        i.b = b;
        execute(i);
    }

};

TEST_F(BranchTest, TestRevImmB) {
        uint32_t value = 0x5d2;
        uint32_t imm_L, imm_U;
        rev_imm_b(value, imm_L, imm_U);

        ASSERT_EQ(0x12, imm_L);
        ASSERT_EQ( 0x2E, imm_U);
}

TEST_F(BranchTest, TestRevLoopImmB) {
    for (int j = 0; j < 512; ++j) {
        uint32_t value = random() & 0xFFE;
        uint32_t imm_L, imm_U;
        rev_imm_b(value, imm_L, imm_U);
        uint32_t _value = imm_b(imm_L, imm_U);
        ASSERT_EQ(value,_value);
    }
}



TEST_F(BranchTest, TestDoBrachBEQ) {
    //given
    x[r1] = (x[r2] = 64);
    pc = pc_s;

    //when
    execute_branch(B_BEQ,r1,r2,rel);

    //then
    ASSERT_BRANCH(rel);
}

TEST_F(BranchTest, TestDoBrachNegativeBEQ) {
    //given
    x[r1] = (x[r2] = 64);
    pc = pc_s;

    //when
    execute_branch(B_BEQ,r1,r2,n_rel);

    //then
    ASSERT_BRANCH(n_rel);
}

TEST_F(BranchTest, TestNoBrachBEQ) {
    //given
    x[r1] = (x[r2] = 64)+1;
    pc = pc_s;

    //when
    execute_branch(B_BEQ,r1,r2,rel);

    //then
    ASSERT_NO_BRANCH();
}

TEST_F(BranchTest, TestDoBrachBNE) {
    //given
    x[r1] = (x[r2] = 64)+1;
    pc = pc_s;

    //when
    execute_branch(B_BNE,r1,r2,rel);

    //then
    ASSERT_BRANCH(rel);
}

TEST_F(BranchTest, TestDoBLT) {
    //given
    x[r1] = (x[r2] = 64)- 1;
    pc = pc_s;

    //when
    execute_branch(B_BLT,r1,r2,rel);

    //then
    ASSERT_BRANCH(rel);
}

TEST_F(BranchTest, TestNoBLT) {
    //given
    x[r1] = (x[r2] = 64);
    pc = pc_s;

    //when
    execute_branch(B_BLT,r1,r2,rel);

    //then
    ASSERT_NO_BRANCH();
}

TEST_F(BranchTest, TestDoBGE) {
    //given
    x[r1] = 59;
    x[r2] = -123;
    pc = pc_s;

    //when
    execute_branch(B_BGE,r1,r2,rel);

    //then
    ASSERT_BRANCH(rel);

}
TEST_F(BranchTest, TestDoBGE_EQ) {
    //given
    x[r1] = 123;
    x[r2] = 123;
    pc = pc_s;

    //when
    execute_branch(B_BGE,r1,r2,rel);

    //then
    ASSERT_BRANCH(rel);
}
TEST_F(BranchTest, TestNoBGE) {
    //given
    x[r1] = -25;
    x[r2] = 123;
    pc = pc_s;

    //when
    execute_branch(B_BGE,r1,r2,rel);

    //then
    ASSERT_NO_BRANCH();
}

TEST_F(BranchTest, TestDoBGEU) {
    //given
    x[r1] = 0x55;
    x[r2] = 0x21;
    pc = pc_s;

    //when
    execute_branch(B_BGEU,r1,r2,rel);

    //then
    ASSERT_BRANCH(rel);
}

TEST_F(BranchTest, TestNoBGEU) {
    //given
    x[r1] = 0x55;
    x[r2] = 0x123;
    pc = pc_s;

    //when
    execute_branch(B_BGEU,r1,r2,rel);

    //then
    ASSERT_NO_BRANCH();
}

TEST_F(BranchTest, TestDoBLTU) {
    //given
    x[r1] = 0x02;
    x[r2] = 0x21;
    pc = pc_s;

    //when
    execute_branch(B_BLTU,r1,r2,rel);

    //then
    ASSERT_BRANCH(rel);
}

TEST_F(BranchTest, TestNoBLUT) {
    //given
    x[r1] = 0x55;
    x[r2] = 0x55;
    pc = pc_s;

    //when
    execute_branch(B_BLTU,r1,r2,rel);

    //then
    ASSERT_NO_BRANCH();
}