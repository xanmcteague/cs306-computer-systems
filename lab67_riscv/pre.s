# Lab 06: Program Structure and System Calls (Assembly Practice)
#
# Task: Load an integer constant stored in data memory, add 10 to it,
# and print the message "My number is " followed by the updated integer.

        .data
msg:    .asciz "My number is "
        .align 2
val:    .word 32                # integer stored in memory

        .text
main:
        # Step 1: Print string "My number is " using system call 4
        la a0, msg              # load address
        addi a7, zero, 4        # syscall 4 = print_string
        ecall 

        # Step 2: Load val from memory, add 10, and print integer using system call 1
        # TODO: Load value of val into a register, add 10, place result in a0,
        # set system call code a7 = 1 (print_int), and execute ecall.
        
        li a1, val # load address of 'val' to a1
        lw a1, 0(a1)
        addi a0, a1, 10 # adding 10 and storing in a0
        addi a7, zero, 1 # set the system call code = 1 in register a7
        ecall # execute print

        # Step 3: Exit program cleanly using system call 10
        addi a7, zero, 10       # syscall 10 = exit
        ecall