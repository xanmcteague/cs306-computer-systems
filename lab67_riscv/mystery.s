.data
msg:   .asciz "Result: "
        .align 2
val:   .word 10

        .text
main:
        la t0, val
        lw t0, 0(t0)
        add t1, zero, zero
        add t2, zero, zero

loop:   bge t2, t0, done
        addi t2, t2, 1
        add t1, t1, t2
        j loop

done:   la a0, msg
        addi a7, zero, 4
        ecall

        add a0, t1, zero
        addi a7, zero, 1
        ecall

        addi a7, zero, 10
        ecall