cmake_minimum_required(VERSION 3.7)
project(ow_riscv_emu)




add_library(riscvLib RISCVCpu.cpp RISCVCpu.h riscvMemory.cpp riscvMemory.h SingleElfMemory.cpp SingleElfMemory.h instructions.h MemoryMappedIO.h SerialPort.cpp SerialPort.h csr.h)
target_include_directories ( riscvLib PUBLIC "${PROJECT_SOURCE_DIR}")
target_link_libraries (riscvLib elf)