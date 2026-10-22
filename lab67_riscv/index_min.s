.data
list:	.word 3, 6, 7, 0, 1, 9, 8, 5, 2, 4
length: .word 10

.text
main:   addi s2, zero, 0x7F     # these registers should still have
        addi s3, zero, 0x77     # these values after the function call

        la a0, list             # a0 = address of list
        la a1, length           
        lw a1, 0(a1)            # a1 = length of list
        addi a2, zero, 5
        jal ra, index_min       # call index_min(list, length)

        addi a7, zero, 1
        ecall                   # print return value

        addi a7, zero, 10
        ecall                   # exit

index_min: addi sp, sp, -16      # make room to save 2 registers
        sw s0, 12(sp)            # save s0 on the stack
        sw s1, 8(sp)            # save s1 on the stack
        sw s2, 4(sp)
        sw s3, 0(sp)

        add s0, zero, a2      # s0 = min_index = 0
        addi s1, a2, 1        # s1 = i = 1
        add s2, a0, zero        # t2 = address of list[min_index]
        slli t0, s0, 2
        add s2, a0, t0
        addi s3, a0, 4          # t3 = address of list[i] (i == 1)
        slli t0, s1, 2
        add s3, a0, t0

loop:   bge s1, a1, return      # if i >= length, go to ret
        lw t0, 0(s2)            # t0 = list[min_index]
        lw t1, 0(s3)            # t1 = list[i]
        blt t1, t0, new_min     # if list[i] < list[min_index], go to new_min
        j skip
new_min: add s0, zero, s1       # min_index = i
        add s2, zero, s3        # adress of list[min_index] = address of list[i]
skip:   addi s1, s1, 1          # i++
        addi s3, s3, 4          # advance address of list[i]
        j loop                  # return to the top of the loop

return: add a0, zero, s0        # return value = min_index
        lw s0, 12(sp)            # restore s0
        lw s1, 8(sp)            # restore s1
        lw s2, 4(sp)
        lw s3, 0(sp)
        addi sp, sp, 16          # pop the stack frame
        jr ra                   # return