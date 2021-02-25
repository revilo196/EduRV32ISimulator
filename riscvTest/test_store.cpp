//
// Created by oliverw on 22.02.21.
//
#include "RiscCpuBaseTest.h"

class StoreTest : public RiscCpuBaseTest {
public:
    void execute_store(uint rs1, uint rs2, F3_StoreOp op, int imm) {
        constexpr  uint32_t imm_mask = 0x1F;
        uint32_t imm0 = imm & imm_mask;
        uint32_t imm1 = (imm & (~imm_mask)) >> 5;
        ASSERT_LT(imm, 1 << 13);
        sType si = {STORE,imm0,op,rs1,rs2,imm1};
        i.s = si;
        execute(i);
    }
};

TEST_F(StoreTest, Store32Check) {
    constexpr uint32_t value = 0x0AAAAAA;
    x[1] = 0xAB00;
    x[2] = value;
    uint32_t imm = 0xCD;

    execute_store(1, 2, S_WORD, imm);

    ASSERT_EQ(mem[0xABCD], value);
}

TEST_F(StoreTest, Store16Check) {
    constexpr uint16_t value = 0xAAAA;
    x[1] = 0xAB00;
    x[2] = value;
    uint32_t imm = 0xCD;

    execute_store(1, 2, S_HALF, imm);

    ASSERT_EQ(mem.read16(0xABCD), value);
}

TEST_F(StoreTest, Store8Check) {
    constexpr uint16_t value = 0xAA;
    x[1] = 0xAB00;
    x[2] = value;
    uint32_t imm = 0xCD;

    execute_store(1, 2, S_BYTE, imm);

    ASSERT_EQ(mem.read08(0xABCD), value);
}

TEST_F(StoreTest, Store8CheckSurrounding) {
    constexpr uint16_t value = 0xAA;
    x[1] = 0xAB00;
    x[2] = value;
    uint32_t imm = 0xCD;

    execute_store(1, 2, S_BYTE, imm);

    ASSERT_EQ(mem.read08(0xABCD), value);
    ASSERT_EQ(mem.read08(0xABCD+1), 0xFF); //next slot
    ASSERT_EQ(mem.read08(0xABCD-1), 0xFF); //prev slot

}