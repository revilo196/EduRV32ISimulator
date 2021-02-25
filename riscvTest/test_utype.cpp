//
// Created by oliverw on 22.02.21.
//
#include "RiscCpuBaseTest.h"
class UTypeTest : public RiscCpuBaseTest{
public:

};

TEST_F(UTypeTest, LuiTest) {

    constexpr uint32_t imm = 0x000ABCDE;
    constexpr uint32_t rd = 2;

    uType u = {LUI,rd,imm};
    i.u = u;
    execute(i);

    ASSERT_EQ(x[rd], imm << 12);
}

TEST_F(UTypeTest, AuipcTest) {

    constexpr uint32_t  imm = 0x000ABCDE;
    constexpr uint32_t rd = 2;

    uType u = {AUIPC,rd,imm};
    i.u = u;
    execute(i);

    ASSERT_EQ(x[rd], (imm << 12) +(pc-4));
}