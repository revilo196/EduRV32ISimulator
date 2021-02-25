# Building for this Simulation
this part is for building test RV32I test programs for 
this simulation using the risc-gnu-toolchain.

Here I provide a _start assembly file for setting up stack/frame/global pointers
and a linker script to link with a pre defined MEMORY segment


## Drives 
this also contains some simple drives for accessing hardware special to this simulation
- SerialPortDriver

## Dependencies
- riscv-gnu-toolchain newlib compiled for RV32I
