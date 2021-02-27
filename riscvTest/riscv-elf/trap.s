.section .text
.global _trap
.global clear_mip

clear_mip:
    li t0, 1
    sll a0, t0, a0
    csrrc zero,mip, a0
    ret

_trap:
        addi    sp, sp, -64    #save all temporary register on stack
        sw      ra, 60(sp)
        sw      t0, 56(sp)
        sw      t1, 52(sp)
        sw      t2, 48(sp)
        sw      a0, 44(sp)
        sw      a1, 40(sp)
        sw      a2, 36(sp)
        sw      a3, 32(sp)
        sw      a4, 28(sp)
        sw      a5, 24(sp)
        sw      a6, 20(sp)
        sw      a7, 16(sp)
        sw      t3, 12(sp)
        sw      t4, 8(sp)
        sw      t5, 4(sp)

        la    ra, _trap_exit            # return point for handlers
        csrrc  t0, mcause, zero
        mv a0,t0
        bltz t0, exceptionHandler       # interrupt causes are less than zero
        slli t0, t0, 1                  # shift off high bit
        srli t0, t0, 1
        li t1, 3                        # check this is an m_sofware interrupt
        beq t0, t1, softTrapHandler
        li t1, 7                        # check this is an m_timer interrupt
        beq t0, t1, timerHandler
        li t1, 11                        # check this is an m_ext interrupt
        beq t0, t1, externalHandler
        j exceptionHandler

_trap_exit:
        lw      ra, 60(sp)   # load temporary registers back from stack
        lw      t0, 56(sp)
        lw      t1, 52(sp)
        lw      t2, 48(sp)
        lw      a0, 44(sp)
        lw      a1, 40(sp)
        lw      a2, 36(sp)
        lw      a3, 32(sp)
        lw      a4, 28(sp)
        lw      a5, 24(sp)
        lw      a6, 20(sp)
        lw      a7, 16(sp)
        lw      t3, 12(sp)
        lw      t4, 8(sp)
        lw      t5, 4(sp)
        addi    sp, sp, 64  # stackpointer should be the same as before the trap
        mret

.weak exceptionHandler
exceptionHandler:
.weak timerHandler
timerHandler:
.weak softTrapHandler
softTrapHandler:
.weak externalHandler
externalHandler:
loop:           # Hard_Fault
        NOP
        J loop
