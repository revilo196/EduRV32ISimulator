//
// Created by oliverw on 25.02.21.
//

#include "RISCVTimer.h"
#include "RISCVCpu.h"
#include <ctime>

RISCVTimer::RISCVTimer(uint32_t address) : MemoryMappedIO(address, address+sizeof(memtime_t)-1) {
    base = address;

    timespec ts{};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    lastUpdateTime =  ts.tv_nsec/64 + (ts.tv_sec*1000000000/64);
}

int RISCVTimer::increment(){
    mem.mtime++;

    if( mem.mtime >= mem.mtimecmp && cpu != nullptr) {
        this->cpu->interrupt(false,7);
    }
    return mem.mtime >= mem.mtimecmp;
}

int RISCVTimer::update(){
    timespec ts{};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    uint64_t current = ts.tv_nsec/64 + (ts.tv_sec*1000000000/64);
    uint64_t inc = - lastUpdateTime;
    lastUpdateTime = current;
    mem.mtime+= inc;

    if( mem.mtime >= mem.mtimecmp && cpu != nullptr) {
        this->cpu->interrupt(false,7);
    }
    return mem.mtime >= mem.mtimecmp;
}

uint32_t RISCVTimer::read(F3_LoadOp op, uint32_t adr) {
    if(in_device(adr)) {
        switch (op) {
            case F3_LoadOp::L_WORD:
                return read32(adr);
            case F3_LoadOp::L_HALF:
                return (int32_t) ((int16_t) read16(adr));
            case F3_LoadOp::L_UHALF:
                return read16(adr);
            case F3_LoadOp::L_BYTE:
                return (int32_t) ((int8_t) read08(adr));
            case F3_LoadOp::L_UBYTE:
                return read08(adr);
        }
    }
}

void RISCVTimer::write(F3_StoreOp op, uint32_t adr, uint32_t value) {

    if(in_device(adr)) {
        switch (op) {
            case F3_StoreOp::S_WORD:
                write32(value, adr);
                return;
            case F3_StoreOp::S_HALF:
                write16(value,adr);
                return;
            case F3_StoreOp::S_BYTE:
                write08(value,adr);
                return;
        }

    }
}

