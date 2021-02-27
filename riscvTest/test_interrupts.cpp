//
// Created by oliverw on 27.02.21.
//

#include "RiscCpuBaseTest.h"

class InterruptTest : public RiscCpuBaseTest {
public:
};

TEST_F(InterruptTest, Software_Interput_TEST) {

    csr[CSR_MTVEC] = 0xBEEB;   //set trap vector
    csr[CSR_MIE] = 0xFFFFFFFF; //enalbe alle interrupts
    pc = 0x80000000;


    iType nop = NOP_INST;
    i.i = nop;
    execute(i);
    ASSERT_EQ(pc, 0x80000004);

    csr[CSR_MIP] = 1 << 3; //M-Software Interrupt

    execute(i);
    ASSERT_EQ(pc, 0xBEEB);
}

TEST_F(InterruptTest, ECALL_Interput_TEST) {

    csr[CSR_MTVEC] = 0xBEEB;   //set trap vector
    csr[CSR_MIE] = 0x0000000; //eexeptions are not filtered
    pc = 0x80000000;


    iType ecall = {CSR, 0,F3_System::ECALL,0,0};
    i.i = ecall;
    execute(i);
    ASSERT_EQ(pc, 0xBEEB);

}

TEST_F(InterruptTest, Iligale_Instruction_exeptin) {

    csr[CSR_MTVEC] = 0xBEEB;   //set trap vector
    csr[CSR_MIE] = 0x0000000; //eexeptions are not filtered
    pc = 0x80000000;


    iType iligal;
    iligal.opcode = 127;
    i.i = iligal;
    execute(i);
    ASSERT_EQ(pc, 0xBEEB);

}