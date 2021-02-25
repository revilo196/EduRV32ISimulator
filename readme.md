
# EduRV32ISimulator

Educational RISC-V 32I simulator with focus not on performance but on 
understanding the architecture and hardware.

## Running:
- Loading/Run a rv32i elf executable (with some special compile options)
- SerialPort simulation simple char output
- all rv32i instructions

## In Progress:
- exceptions and interrupts
- CSR registers
- Hardware timer & interrupt
- better (graphical) device options

## Goal
My goal is to develop a good to understand and expandable simulation. That can run a simple embedded like OS. 
And maybe even dynamically load rv32i executables into this running and simulated hardware and OS.

## Dependencies
- riscv-gnu-toolchain (newlib arch=rv32i) (https://github.com/riscv/riscv-gnu-toolchain)
- libelf 
