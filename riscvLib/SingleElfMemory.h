//
// Created by oliverw on 20.02.21.
//

#ifndef OW_RISCV_EMU_SINGLEELFMEMORY_H
#define OW_RISCV_EMU_SINGLEELFMEMORY_H
#include "riscvMemory.h"
#include <gelf.h>
#include <cstdio>
#include <vector>


/**
 * class handeling a program memory segment of an ELF-File
 *
 * - decoding the program header
 * - loading the segment from ELF-File
 * - providing access to this memory
 */
class MemSegment {
private:
    char * data{};
    uint32_t adr_begin{};
    uint32_t adr_end{};
    uint32_t flags{};
public:
    MemSegment() = default;
    MemSegment(FILE* fd, GElf_Phdr *phdr, uint32_t min_length);
    ~MemSegment();
    [[nodiscard]] bool in(uint32_t adr) const;
    char * operator[](uint32_t adr) const;
    [[nodiscard]] bool can_read() const { return flags&PF_R ;}
    [[nodiscard]] bool can_write() const { return flags&PF_W;}
    [[nodiscard]] bool can_execute() const { return flags&PF_X;}
};


/**
 * RISCVMemory generated from a ELF file linked to have a single RAM segment
 * the in .ld script configures MEMORY size should be given as argument
 */
class SingleElfMemory : public RISCVMemory {
private:
    MemSegment * memory;
    [[nodiscard]] char * lookup(uint32_t adr) const override;
public:
    /**
     * @param elf_filename elf filepath to load
     * @param min_mem_size MEMORY size defined in  .ld script
     */
    SingleElfMemory(const char *elf_filename, uint32_t min_mem_size);
    ~SingleElfMemory(){delete memory;}
    uint32_t entry;

};


#endif //OW_RISCV_EMU_SINGLEELFMEMORY_H
