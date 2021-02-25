//
// Created by oliverw on 20.02.21.
//

#include "SingleElfMemory.h"
#include <libelf.h>
#include <cstdio>
#include <string>
#include <cstring>

SingleElfMemory::SingleElfMemory(const char * name, uint32_t min_mem_size)  {

    FILE * fd ;
    Elf * e ;
    std::string  k ;

    elf_version ( EV_CURRENT ) ;
    fd = std::fopen(name, "r");
    e = elf_begin(fd->_fileno, ELF_C_READ, nullptr);
    elf_kind(e); //K_ELF

    Elf32_Ehdr * h = elf32_getehdr(e);
    h->e_machine == 0xf3; //riscv
    this->entry = h->e_entry;

    GElf_Phdr phdr;
    gelf_getphdr(e, 0 ,&phdr);

    memory = new MemSegment(fd, &phdr, min_mem_size);


}

char *SingleElfMemory::lookup(uint32_t adr) const {
    char * ret = (*memory)[adr];
    return ret;
}

MemSegment::MemSegment(FILE *fd, GElf_Phdr *phdr, uint32_t min_length) {
    uint32_t length = phdr->p_align + ((min_length > phdr->p_memsz) ? min_length : phdr->p_memsz);
    data = new char[length];
    std::memset(data, 0, length);
    std::fseek(fd, phdr->p_offset, SEEK_SET);
    std::fread(data,phdr->p_filesz,1,fd);

    adr_begin = phdr->p_vaddr;
    adr_end = phdr->p_vaddr + length;
    flags = phdr->p_flags;
}


char *MemSegment::operator[](uint32_t adr) const{
    if(!in(adr)){return nullptr;}

    uint32_t index = adr-adr_begin;
    char * address = data+index;
    return address;
}

bool MemSegment::in(uint32_t adr) const {
    return (adr_begin <= adr && adr <= adr_end);
}

MemSegment::~MemSegment() {
    delete data;
}

