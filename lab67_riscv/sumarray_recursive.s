# sumarray_recursive
# using recursive sum_array function with base_case exit in RISC-V

.data
array: .word 1, 2, 3, 18, 46, 42, 20, 26, 8, 9, 10
length: .word 11

.text
main: 
    la a0, array # load address of array into a0
    addi a1, zero, 0 # set i = 0
    la a2, length # load length to a2
    lw a2, 0(a2) # load value
    jal ra, sum_array

    addi a7, zero, 1
    ecall # print int

    addi a7, zero, 10
    ecall #exit 

sum_array:
    bge a1, a2, base_case # base if statement

    addi sp, sp, -8
    sw ra, 4(sp)
    sw s0, 0(sp)

    slli s0, a1, 2
    add s0, s0, a0
    lw s0, 0(s0)

    addi a1, a1, 1
    jal ra, sum_array
    add a0, a0, s0

    lw s0, 0(sp)
    lw ra, 4(sp)
    addi sp, sp, 8
    jr ra

base_case: 
    add a0, zero, zero
    jr ra