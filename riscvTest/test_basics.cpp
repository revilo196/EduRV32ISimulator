//
// Created by oliverw on 19.02.21.
//

//
// Created by oliverw on 19.02.21.
//

#include <gtest/gtest.h>
#include "RISCVCpu.h"

class BasicCpuTest : public testing::Test , public RISCVCpu {
public:
    iType  nop = {0x13,0,0,0,0};
    Instruction i;

    BasicCpuTest();
    void SetUp() override {
        start(0x0000);
    };
    void TearDown() override {
        resetCpu();
    };
};

BasicCpuTest::BasicCpuTest() :RISCVCpu(nullptr) {}


TEST_F(BasicCpuTest, nop_increment_pc) {
    // given
    uint32_t  start = this->pc;
    Instruction i;
    iType  nop = {0x13,0,0,0,0};
    i.i = nop;

    //when
    execute(i);

    //then
    ASSERT_EQ(this->pc, start+4);
}

TEST_F(BasicCpuTest, x0_resets_to_zero) {
    // given
    x[0] = 1;
    i.i = nop;

    //when
    execute(i);

    //then
    ASSERT_EQ(this->x[0],0);
}

TEST_F(BasicCpuTest, addi_x0_stays_zero) {
    // given range
    for (int j = 1; j < 100; ++j) {
        iType addi = {0x13, 0, 0, 0, static_cast<uint32_t>(j)};
        i.i = addi;

        //when
        execute(i);

        //then
        ASSERT_EQ(this->x[0], 0);
    }
}

TEST_F(BasicCpuTest, test_decoding_nop) {
    //given
    uint32_t code = 0x00000013;

    //when
    i._ui32 = code;

    //then
    ASSERT_EQ(i.i.opcode, 0x13);
    ASSERT_EQ(i.i.imm, 0x0);
    ASSERT_EQ(i.i.rs1, 0x0);
    ASSERT_EQ(i.i.rd, 0x0);
    ASSERT_EQ(i.i.func3, 0x0);
}

TEST_F(BasicCpuTest, test_decoding_type_i) {
    //given
    uint32_t code = 0x12F19093;  //0x13(alu) | 0x80(rd=1) | 0x00000(func3) |  0x18000(r1=3) | 0x00F00000(imm)

    //when
    i._ui32 = code;

    //then
    ASSERT_EQ(i.i.opcode, 0x13);
    ASSERT_EQ(i.i.imm, 0x12F);
    ASSERT_EQ(i.i.rs1, 0x03);
    ASSERT_EQ(i.i.rd, 0x01);
    ASSERT_EQ(i.i.func3, 0x01);
    ASSERT_EQ(imm_i(i.i.imm), 0x12F );
}

TEST_F(BasicCpuTest, test_decoding_type_r) {
    //given
    uint32_t code = 0x00519133;  //0x33(alu) | 0x200(rd=2) | 0x00000(func3) |  0x18000(r1=3) | 0x00500000(r2)

    //when
    i._ui32 = code;

    //then
    ASSERT_EQ(i.r.opcode, 0x33);
    ASSERT_EQ(i.r.rs2, 5);
    ASSERT_EQ(i.i.rs1, 3);
    ASSERT_EQ(i.i.rd, 2);
    ASSERT_EQ(i.i.func3, 0x01);
}

TEST_F(BasicCpuTest, test_decoding_type_s) {
    //given
    uint32_t code = 0x2A30AD23;  //

    //when
    i._ui32 = code;

    //then
    ASSERT_EQ(i.s.opcode, 0x23);
    ASSERT_EQ(i.s.imm_0_4, 0x1A);
    ASSERT_EQ(i.s.func3, 0x02);
    ASSERT_EQ(i.s.rs1, 0x01);
    ASSERT_EQ(i.s.rs2, 0x03);
    ASSERT_EQ(i.s.imm_5_11, 0x15);
    ASSERT_EQ(imm_s(i.s.imm_0_4,i.s.imm_5_11), 0x2BA);
}

TEST_F(BasicCpuTest, test_decoding_type_b) {
    //given
    uint32_t code = 0x2A30AD63;  //

    //when
    i._ui32 = code;

    //then
    ASSERT_EQ(i.b.opcode, 0x63);
    ASSERT_EQ(i.b.imm_0_1_11, 0x1A);
    ASSERT_EQ(i.b.func3, 0x02);
    ASSERT_EQ(i.b.rs1, 0x01);
    ASSERT_EQ(i.b.rs2, 0x03);
    ASSERT_EQ(i.b.imm_12_5_10, 0x15);
    ASSERT_EQ(imm_b(i.b.imm_0_1_11,i.b.imm_12_5_10), 0x2BA);
}

TEST_F(BasicCpuTest, test_decoding_type_u) {
    //given
    uint32_t code = 0x12345D37;  //

    //when
    i._ui32 = code;

    //then
    ASSERT_EQ(i.u.opcode, 0x37);
    ASSERT_EQ(i.u.rd, 0x1A);
    ASSERT_EQ(i.u.imm, 0x12345);
    ASSERT_EQ(imm_u(i.u.imm), 0x12345000);
}

TEST_F(BasicCpuTest, test_decoding_type_j) {
    //given
    uint32_t code = 0x12345D6F;  //

    //when
    i._ui32 = code;

    //then
    ASSERT_EQ(i.j.opcode, 0x6F);
    ASSERT_EQ(i.j.rd, 0x1A);
    ASSERT_EQ(i.j.imm, 0x12345);
    ASSERT_EQ(imm_j(i.j.imm), 0x045922);
}

TEST_F(BasicCpuTest, Integer_MATH) {

    uint32_t V1 = 0x923;
    uint32_t V2 = 0xFFFFF823;

    ASSERT_EQ(V1 + V2, ((int32_t) V1) + ((int32_t)V2));

}