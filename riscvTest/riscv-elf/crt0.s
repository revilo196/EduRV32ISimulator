.section .init, "ax"
.global _start


_start:
    .cfi_startproc
    .cfi_undefined ra
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
    la sp, __stack_top      
    add s0, sp, zero      
    jal ra, _trap_setup 
    mv  ra,zero
    jal zero, main
    .cfi_endproc

_trap_setup:
    .cfi_startproc
    .option push
    .option norelax
    la t0, _trap
    .option pop
    csrrw   zero, mtvec, t0 # setup machine trap vector
    ret
    .cfi_endproc
    .end


