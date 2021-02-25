//
// Created by oliverw on 19.02.21.
//
#ifndef OW_RISCV_EMU_INSTRUCTIONS_H
#define OW_RISCV_EMU_INSTRUCTIONS_H
#include <cstdint>

/**
 * Defining structs that represent instruction encoding
 */
typedef struct {
    uint32_t opcode : 7;
    uint32_t extension : 25;
} dType;

typedef struct {
    uint32_t opcode : 7;
    uint32_t rd : 5;
    uint32_t imm : 20;
} uType;

typedef struct {
    uint32_t opcode : 7;
    uint32_t rd : 5;
    uint32_t imm : 20;
} jType;

typedef struct {
    uint32_t opcode : 7;
    uint32_t rd : 5;
    uint32_t func3 : 3;
    uint32_t rs1 : 5;
    uint32_t rs2 : 5;
    uint32_t func7 : 7;
} rType;

typedef struct {
    uint32_t opcode : 7;
    uint32_t rd : 5;
    uint32_t func3 : 3;
    uint32_t rs1 : 5;
    uint32_t imm : 12;
} iType;

typedef struct {
    uint32_t opcode : 7;
    uint32_t rd : 5;
    uint32_t func3 : 3;
    uint32_t rs1 : 5;
    uint32_t shamt : 5;
    uint32_t func7 : 7;
} iType_s;


typedef struct {
    uint32_t opcode : 7;
    uint32_t imm_0_4 : 5;
    uint32_t func3 : 3;
    uint32_t rs1 : 5;
    uint32_t rs2 : 5;
    uint32_t imm_5_11 : 7;
} sType;

typedef struct {
    uint32_t opcode : 7;
    uint32_t imm_0_1_11 : 5;
    uint32_t func3 : 3;
    uint32_t rs1 : 5;
    uint32_t rs2 : 5;
    uint32_t imm_12_5_10 : 7;
} bType;

/**
 * union to unite all instructions
 */
typedef union {
    dType  d;
    uType  u;
    jType  j;
    rType  r;
    iType i;
    iType_s is;
    sType s;
    bType b;
    uint32_t  _ui32;
    int32_t  _i32;
} Instruction;

/**
 * Functions for decoding a imm
 * this handles also sign expansion
 */

///
inline uint32_t imm_u(uint32_t imm) {return imm << 12;}
inline uint32_t imm_i(uint32_t imm) {  return (imm & 0x0FFF) | ((imm & 0x0800) ? 0xFFFFF000 : 0x00 ) ;}
inline uint32_t imm_j(uint32_t imm) {
    uint32_t imm_j = 0;
    imm_j |= (imm & 0x000FF) << (12);
    imm_j |= (imm & 0x00100) << (3);
    imm_j |= (imm & 0x7FE00) >> (8);
    imm_j |= (imm & 0x80000) ? 0xFFF80000 : 0x00; //fill with sign
    return imm_j;
}
inline  uint32_t imm_s(uint32_t imm_0_4, uint32_t imm5_12) {
    uint32_t imm_s = 0;
    imm_s |= imm_0_4;
    imm_s |= (imm5_12 << 5);
    imm_s |= (imm5_12 & 0x40) ? 0xFFFFF000 : 0x00; // fill with sign
    return imm_s;
}
inline  uint32_t imm_b(uint32_t imm_1_4_11, uint32_t imm_12_5_10) {
    uint32_t imm_s = 0;
    imm_s |= imm_1_4_11 & 0x1E;
    imm_s |= (imm_12_5_10 & 0x3F) << 5;
    imm_s |= (imm_1_4_11 & 0x01) << 11;
    imm_s |= (imm_12_5_10 & 0x40) ? 0xFFFFF000 : 0x00; //fill with sign
    return imm_s;
}


/**
 * Opcode Enumerations, with corresponding integer/opcode values
 */

typedef enum {LOAD = 0x03, ALU_IMM = 0x13, STORE=0x23, ALU=0x33, BRANCH=0x63,
              LUI = 0x37, AUIPC = 0x17, JAL = 0x6F, JALR = 0x67, CSR = 0x73} Opcode;

/**
 * Func3 enumerations with corresponding integer values
 */
typedef enum {A_ADD = 0, A_SLL=1, A_SLT = 2, A_SLTU = 3, A_XOR = 4, A_SRL =5, A_OR=6, A_AND=7} F3_AluOp;
typedef enum {L_BYTE = 0, L_HALF = 1, L_WORD = 2, L_UBYTE = 4, L_UHALF = 5} F3_LoadOp;
typedef enum {S_BYTE = 0, S_HALF = 1, S_WORD = 2} F3_StoreOp;
typedef enum {B_BEQ = 0, B_BNE = 1, B_BLT = 4, B_BGE = 5, B_BLTU = 6, B_BGEU = 7} F3_BranchOp;

/**
 * enum for Exception cause (-1 used for no Exception)
 */

enum InstructionExceptionCode {IEC_OK = -1, Inst_Misaligned = 0, Inst_AccessFault=1, Illegal =2, Breakpoint=3,
    L_Misaligned=4, L_AccessFault=5 ,S_Misaligned=6, S_AccessFault=7,
    ECALL_U =8, ECALL_S =9, ECALL_H=10, ECALL_M=11,
    Inst_PageFault=12, L_PageFault=13, S_PageFault=15};

typedef InstructionExceptionCode iec;

#endif //OW_RISCV_EMU_INSTRUCTIONS_H
