//
// Created by oliverw on 24.02.21.
//

#ifndef OW_RISCV_EMU_CSR_H
#define OW_RISCV_EMU_CSR_H

/**
 * Collection of all CSR_Registers and their number.
 * can also be used in risc target
 */

#define CSR_USTATUS      0x000
#define CSR_USTATUS      0x000
#define CSR_USTATUS      0x000
#define CSR_UIE          0x004
#define CSR_UTVEC        0x005

#define CSR_USCRATCH     0x040
#define CSR_UEPC         0x041
#define CSR_UCAUSE       0x042
#define CSR_UTVAL        0x043
#define CSR_UIP          0x044

#define CSR_FFLAGS       0x001
#define CSR_FRM          0x002
#define CSR_FCSR         0x003

#define CSR_CYCLE           0xC00
#define CSR_TIME            0xC01
#define CSR_INSTRET         0xC02
#define CSR_HPMCOUNTER3     0xC03
#define CSR_HPMCOUNTER4     0xC04

#define CSR_HPMCOUNTER31    0xC1F
#define CSR_CYCLEH          0xC80
#define CSR_TIMEH           0xC81
#define CSR_INSTRETH        0xC82
#define CSR_HPMCOUNTER3H    0xC83
#define CSR_HPMCOUNTER4H    0xC84

#define CSR_SSTATUS      0x100
#define CSR_SEDELEG      0x102
#define CSR_SIDELEG      0x103
#define CSR_SIE          0x104
#define CSR_STVEC        0x105
#define CSR_SCOUNTEREN   0x106

#define CSR_SSCRATCH     0x140
#define CSR_SEPC         0x141
#define CSR_SCAUSE       0x142
#define CSR_STVAL        0x143
#define CSR_SIP          0x144

#define CSR_HSTATUS      0x600
#define CSR_HEDELEG      0x602
#define CSR_HIDELEG      0x603
#define CSR_HIE          0x604
#define CSR_HCOUNTEREN   0x606
#define CSR_HGEIE        0x607

#define CSR_HTVAL        0x643
#define CSR_HIP          0x644
#define CSR_HVIP         0x645
#define CSR_HTINST       0x64A
#define CSR_HGEIP        0xE12

#define CSR_VSSTATUS     0x200
#define CSR_VSIE         0x204
#define CSR_VSTVEC       0x205
#define CSR_VSSCRATCH    0x240
#define CSR_VSEPC        0x241
#define CSR_VSCAUSE      0x242
#define CSR_VSTVAL       0x243
#define CSR_VSIP         0x244
#define CSR_VSATP        0x280


#endif //OW_RISCV_EMU_CSR_H
