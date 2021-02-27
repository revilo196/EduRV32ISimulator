//
// Created by oliverw on 26.02.21.
//
#include "RiscCpuBaseTest.h"

class CSRegisterTest : public RiscCpuBaseTest {
public:
    static constexpr int rs1 = 1;
    static  constexpr int rd = 2;
};

TEST_F(CSRegisterTest, CSR_Reset_Value) {
    //when
    resetCpu();

    //then
    ASSERT_EQ(csr[CSR_MIP], 0);
    ASSERT_EQ(csr[CSR_MIE], 0);
    ASSERT_EQ(csr[CSR_MSCRATCH], 0);
    ASSERT_EQ(csr[CSR_MEPC], 0);
    ASSERT_EQ(csr[CSR_MTVEC], 0x0000000);
}

TEST_F(CSRegisterTest, CSR_RW) {
    //given
    csr[CSR_MSCRATCH] = 0x12345678;
    uint16_t csreg = CSR_MSCRATCH;
    iType icsr = {CSR,rd,F3_System::CSR_RW,rs1,csreg};
    x[rs1] = 0x87654321;

    //when
    i.i = icsr;
    execute(i);

    //then registers are swapped
    ASSERT_EQ(x[rd], 0x12345678);
    ASSERT_EQ(csr[CSR_MSCRATCH], 0x87654321);
}

TEST_F(CSRegisterTest, CSR_RS) {
    //given
    csr[CSR_MSCRATCH] = 0x12345678;
    uint16_t csreg = CSR_MSCRATCH;
    iType icsr = {CSR,rd,F3_System::CSR_RS,rs1,csreg};
    x[rs1] = 0x87654321;

    //when
    i.i = icsr;
    execute(i);

    //then bits in register are set
    ASSERT_EQ(x[rd], 0x12345678);
    ASSERT_EQ(csr[CSR_MSCRATCH], 0x87654321 | 0x12345678);
}

TEST_F(CSRegisterTest, CSR_RC) {
    //given
    csr[CSR_MSCRATCH] = 0x12345678;
    uint16_t csreg = CSR_MSCRATCH;
    iType icsr = {CSR,rd,F3_System::CSR_RC,rs1,csreg};
    x[rs1] = 0x87654321;

    //when
    i.i = icsr;
    execute(i);

    //then bits in register are cleared
    ASSERT_EQ(x[rd], 0x12345678);
    ASSERT_EQ(csr[CSR_MSCRATCH], 0x87654321 ^ 0x12345678);
}