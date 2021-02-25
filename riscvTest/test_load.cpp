//
// Created by oliverw on 21.02.21.
//
#include "RiscCpuBaseTest.h"

class LoadTest : public RiscCpuBaseTest{
public:

    Address test_adr_32{};
    Address test_adr_u16{};
    Address test_adr_u8{};
    Address test_adr_16{};
    Address test_adr_8{};

    static constexpr uint32_t v_32 = 0xAAAAAAAA;
    static constexpr uint16_t v_u16 = 0x0AAA;
    static constexpr uint16_t v_16 = 0xAAAA;
    static constexpr uint8_t v_u8 = 0x7A;
    static constexpr uint8_t v_8 = 0xAA;

    uint32_t rd1{};
    uint32_t rd2{};
    uint32_t rd3{};
    uint32_t rs1{};

    void SetUp() override {
        RiscCpuBaseTest::SetUp();
        test_adr_32  = 0x10;
        test_adr_u16 = test_adr_32 + 8;
        test_adr_u8  = test_adr_u16 + 8;
        test_adr_16  = test_adr_u8 + 8;
        test_adr_8   = test_adr_16 + 8;

        mem.write32(v_32,test_adr_32);
        mem.write16(v_u16,test_adr_u16);
        mem.write16(v_16,test_adr_16);
        mem.write08(v_u8,test_adr_u8);
        mem.write08(v_8,test_adr_8);
        rd1 = 1;
        rd2 = 2;
        rd3 = 3;
        rs1 = 4;
    }

    /**
     * Load via 11 bit imm value (since the addresses here are small)
     */
    void execute_loadImm(uint rd,uint mode,Address adr) {
        iType lw = {LOAD,rd,mode,0, adr};
        i.i = lw;
        execute(i);
    }
    /**
     * Load via register and 0 offset imm
     */
    void execute_loadReg(uint rd,uint mode,Address adr) {
        x[rs1] = adr;
        iType lw = {LOAD,rd,mode,rs1, 0};
        i.i = lw;
        execute(i);
    }
    /**
     * load using register and imm using adr/2 in get and adr/2 in imm
     */
    void execute_loadImmReg(uint rd,uint mode,Address adr) {
        x[rs1] = adr/2;
        iType lw = {LOAD,rd,mode,rs1, adr/2};
        i.i = lw;
        execute(i);
    }

};

TEST_F(LoadTest, LoadImm32AndCheck) {
    //given v_32 = 0xAAAAAAAA
    //when
    execute_loadImm(rd1,F3_LoadOp::L_WORD,test_adr_32);
    execute_loadReg(rd2,F3_LoadOp::L_WORD,test_adr_32);
    execute_loadImmReg(rd3,F3_LoadOp::L_WORD,test_adr_32);

    //then
    ASSERT_EQ(x[rd1],v_32);
    ASSERT_EQ(x[rd2],v_32);
    ASSERT_EQ(x[rd3],v_32);
}
TEST_F(LoadTest, LoadImm16AndCheck) {
    //given v_u16 = 0x0AAA
    //when
    execute_loadImm(rd1,F3_LoadOp::L_HALF, test_adr_u16);
    execute_loadReg(rd2,F3_LoadOp::L_HALF, test_adr_u16);
    execute_loadImmReg(rd3,F3_LoadOp::L_HALF, test_adr_u16);

    //then
    ASSERT_EQ(x[rd1],v_u16);
    ASSERT_EQ(x[rd2],v_u16);
    ASSERT_EQ(x[rd3],v_u16);
}

TEST_F(LoadTest, LoadImm16AndCheckExpansion) {
    //given v_16 = 0xAAAA
    //when
    execute_loadImm(rd1,F3_LoadOp::L_HALF, test_adr_16);
    execute_loadReg(rd2,F3_LoadOp::L_HALF, test_adr_16);
    execute_loadImmReg(rd3,F3_LoadOp::L_HALF, test_adr_16);

    //then
    ASSERT_EQ(x[rd1],(int32_t)((int16_t)v_16));
    ASSERT_EQ(x[rd2],(int32_t)((int16_t)v_16));
    ASSERT_EQ(x[rd3],(int32_t)((int16_t)v_16));
}

TEST_F(LoadTest, LoadImmU16AndCheckNoExpansion) {
    //given v_16 = 0xAAAA
    //when
    execute_loadImm(rd1,F3_LoadOp::L_UHALF, test_adr_16);
    execute_loadReg(rd2,F3_LoadOp::L_UHALF, test_adr_16);
    execute_loadImmReg(rd3,F3_LoadOp::L_UHALF, test_adr_16);

    //then
    ASSERT_EQ(x[rd1],v_16);
    ASSERT_EQ(x[rd2],v_16);
    ASSERT_EQ(x[rd3],v_16);
}

TEST_F(LoadTest, LoadImm8AndCheck) {
    //given v_u8 = 0x7A
    //when
    execute_loadImm(rd1,F3_LoadOp::L_BYTE, test_adr_u8);
    execute_loadReg(rd2,F3_LoadOp::L_BYTE, test_adr_u8);
    execute_loadImmReg(rd3,F3_LoadOp::L_BYTE, test_adr_u8);

    //then    execute_loadImm(rd1,F3_LoadOp::L_BYTE, test_adr_8);

    ASSERT_EQ(x[rd1],v_u8);
    ASSERT_EQ(x[rd2],v_u8);
    ASSERT_EQ(x[rd3],v_u8);
}

TEST_F(LoadTest, LoadImm8AndCheckExpansion) {
    //given v_8 = 0xAA
    //when
    execute_loadImm(rd1,F3_LoadOp::L_BYTE, test_adr_8);
    execute_loadReg(rd2,F3_LoadOp::L_BYTE, test_adr_8);
    execute_loadImmReg(rd3,F3_LoadOp::L_BYTE, test_adr_8);

    //then
    ASSERT_EQ(x[rd1],(int32_t)((int8_t)v_8));
    ASSERT_EQ(x[rd2],(int32_t)((int8_t)v_8));
    ASSERT_EQ(x[rd3],(int32_t)((int8_t)v_8));
}

TEST_F(LoadTest, LoadImmU8AndCheckNoExpansion) {
    //given  v_8 = 0xAA
    //when
    execute_loadImm(rd1,F3_LoadOp::L_UBYTE,test_adr_8);
    execute_loadReg(rd2,F3_LoadOp::L_UBYTE,test_adr_8);
    execute_loadImmReg(rd3,F3_LoadOp::L_UBYTE,test_adr_8);
    //then
    ASSERT_EQ(x[rd1],v_8);
    ASSERT_EQ(x[rd2],v_8);
    ASSERT_EQ(x[rd3],v_8);
}

TEST_F(LoadTest, LoadReg32AndCheck) {
    //given v_32 = 0xAAAAAAAA @ test_adr_32
    //when
    execute_loadImm(rd1,F3_LoadOp::L_WORD,test_adr_32);
    execute_loadReg(rd2,F3_LoadOp::L_WORD,test_adr_32);
    execute_loadImmReg(rd3,F3_LoadOp::L_WORD,test_adr_32);

    //then
    ASSERT_EQ(x[rd1],v_32);
    ASSERT_EQ(x[rd2],v_32);
    ASSERT_EQ(x[rd3],v_32);
}

TEST_F(LoadTest, LoadBigAddress) {
    //load big address using register and imm offset
    Address adr = msize - 0x1234;
    constexpr  uint32_t value = 0xABABABAB;
    mem[adr] = value;
    constexpr  uint32_t mask = 0xFFFFF800;

    x[rs1] = adr & mask;
    iType lw = {LOAD,rd1,F3_LoadOp::L_WORD,rs1, adr&(~mask)};
    i.i = lw;
    execute(i);

    ASSERT_EQ(x[rd1],value);
}