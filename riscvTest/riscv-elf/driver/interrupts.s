.section .text
.global enable_interrupt_status
.global enable_interrupt
.global disable_interrupt_status
.global disable_interrupt
.global clear_interrupts
.global soft_trap

enable_interrupt_status:
    li      t0, 8
    csrrs   zero, mstatus, t0 # set mstatus.MIE=1 (enable M mode interrupt)
    ret

enable_interrupt:
    li      t0, 1
    sll     t0, t0, a0
    csrrs   zero, mie, t0 # set mie
    ret

disable_interrupt_status:
    li      t0, 8
    csrrc   zero, mstatus, t0 # set mstatus.MIE=1 (disable M mode interrupt)
    ret

disable_interrupt:
    li      t0, 1
    sll     t0, t0, a0
    csrrc   zero, mie, t0 # set mie
    ret

clear_interrupts:
    mv t0, zero
    csrrw   zero, mip, t0 # set mip. zero clear all pending
    ret

soft_trap:
    li t0, 8
    csrrs   zero, mip, t0 # set mip.MSIE=1 set interrupts pending
    ret
    .end

