.section .text
.global switchContext
.global firstContext
.global halt

halt:
    JALR zero, 0(zero)



switchContext:
        addi    sp, sp, -128  #save all temporary register on stack
        sw      ra, 4(sp)
        sw      t0, 8(sp)
        sw      t1, 12(sp)
        sw      t2, 16(sp)
        sw      a0, 20(sp)
        sw      a1, 24(sp)
        sw      sp, 0(a0)

        lw      sp, 0(a1)
        lw      ra, 4(sp)   #get  some temporary register from stack
        lw      t0, 8(sp)
        lw      t1, 12(sp)
        lw      t2, 16(sp)
        lw      a0, 20(sp)
        lw      a1, 24(sp)
        lw      t3, 0(sp)
        addi    sp, sp, 128  #leave space for all registers
        ret


firstContext:
        lw      sp, 0(a0)
        lw      ra, 4(sp)
        lw      t0, 8(sp)
        lw      t1, 12(sp)
        lw      t2, 16(sp)
        lw      a0, 20(sp)
        lw      a1, 24(sp)
        lw      t3, 0(sp)
        addi    sp, sp, 128 #leave space for all registers
        JALR     zero, 0(t3)
