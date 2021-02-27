//
// Created by oliverw on 26.02.21.
//

#include "RISCVTimer.h"
#include "RiscCpuBaseTest.h"



class RISCVTimerTest : public RiscCpuBaseTest, public RISCVTimer{
public:
    static constexpr uint32_t  timerBaseAdr = 0x00004000;

    RISCVTimerTest() : RISCVTimer(timerBaseAdr){}

    void SetUp() override {
        RiscCpuBaseTest::SetUp();
        RISCVTimer::mem.mtime = 0;
        RISCVTimer::mem.mtimecmp= 0;
    }

    void TearDown() override {
        RiscCpuBaseTest::TearDown();
        RISCVTimer::mem.mtime = 0;
        RISCVTimer::mem.mtimecmp= 0;
    }
};

TEST_F(RISCVTimerTest, Timer_Write) {

    uint64_t time_in = 0xAAAABBBBCCCCDDDD;
    uint64_t timecmp_in = 0xFFFFEEEEDDDDCCCC;
    uint32_t time_inL = time_in;
    uint32_t time_inH = time_in >> 32;
    uint32_t timecmp_inL = timecmp_in;
    uint32_t timecmp_inH = timecmp_in >> 32;

    this->write(F3_StoreOp::S_WORD, timerBaseAdr, time_inL);
    this->write(F3_StoreOp::S_WORD, timerBaseAdr+4, time_inH);
    this->write(F3_StoreOp::S_WORD, timerBaseAdr+8, timecmp_inL);
    this->write(F3_StoreOp::S_WORD, timerBaseAdr+12, timecmp_inH);

    ASSERT_EQ(RISCVTimer::mem.mtime, time_in);
    ASSERT_EQ(RISCVTimer::mem.mtimecmp, timecmp_in);

}

TEST_F(RISCVTimerTest, Timer_read) {
    RISCVTimer::mem.mtime =    0x0123456789ABCDEF;
    RISCVTimer::mem.mtimecmp = 0xFFEEDDCCDDBBAA99;

    uint32_t time_inL =  this->read(F3_LoadOp::L_WORD, timerBaseAdr+0);
    uint32_t time_inH = this->read(F3_LoadOp::L_WORD, timerBaseAdr+4);
    uint32_t timecmp_inL = this->read(F3_LoadOp::L_WORD, timerBaseAdr+8);
    uint32_t timecmp_inH = this->read(F3_LoadOp::L_WORD, timerBaseAdr+12);


    ASSERT_EQ( time_inL + ((uint64_t)time_inH<<32) ,RISCVTimer::mem.mtime);
    ASSERT_EQ( timecmp_inL + ((uint64_t)timecmp_inH<<32) ,RISCVTimer::mem.mtimecmp);
}

TEST_F(RISCVTimerTest, Timer_update) {

    //given timer == 0;

    //when
    this->update();
    //then
    ASSERT_GT(this->read(F3_LoadOp::L_WORD, timerBaseAdr+0), 0);
}

TEST_F(RISCVTimerTest, Timer_increment) {

    //given timer == 0;

    //when
    this->increment();

    //then
    ASSERT_EQ(this->read(F3_LoadOp::L_WORD, timerBaseAdr+0), 1);
}

TEST_F(RISCVTimerTest, Timer_interrupt) {

    //given timer == 0;
    // timecmp ==0

    //when
    int interr = this->update();

    //then
    ASSERT_EQ(interr, 1);
}

TEST_F(RISCVTimerTest, Timer_interrupt_toCPU) {

    //given timer == 0;
    // timecmp ==0
    csr[CSR_MTVEC] = 0xBEEB;   //set trap vector
    csr[CSR_MIE] = 0xFFFFFFFF; //enalbe alle interrupts
    this->attach_cpu(this);

    //when
    this->update();

    //then
    ASSERT_EQ(pc,  0xBEEB);
    ASSERT_EQ(csr[CSR_MSCAUSE], 7);

}
