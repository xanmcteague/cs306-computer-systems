# sumarray.s - Array Traversal and Pointer Arithmetic
#
# Task: Compute the sum of an integer array terminated by sentinel value 0.
# Store the total sum in register s0 and the element count in register s1.
# Print formatted output "Sum: 238, Count: 13"

        .data
array:  .word 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 0   # sentinel 0

msg_sum:   .asciz "Sum: "
msg_cnt:   .asciz ", Count: "

        .text
main:
        la t0, array            # t0 = pointer to current array element
        addi s0, zero, 0        # s0 = sum = 0
        addi s1, zero, 0        # s1 = count = 0

loop:
        # TODO: Load current array word from address in t0 into a temporary register (e.g. t1)
        lw t1, 0(t0)
        # TODO: If value == 0 (sentinel), branch to done
        beq t1, zero, done
        # TODO: Add value to s0 (sum)
        add s0, s0, t1
        # TODO: Increment s1 (count) by 1
        addi s1, s1, 1
        # TODO: Increment t0 by 4 bytes to point to next array element
        addi t0, t0, 4
        # TODO: Jump back to top of loop
        j loop

done:
        # Step 1: Print "Sum: " string
        la a0, msg_sum
        addi a7, zero, 4
        ecall

        # Step 2: Print sum stored in s0
        add a0, s0, zero
        addi a7, zero, 1
        ecall

        # Step 3: Print ", Count: " string
        la a0, msg_cnt
        addi a7, zero, 4
        ecall

        # Step 4: Print count stored in s1
        add a0, s1, zero
        addi a7, zero, 1
        ecall

        # Step 5: Exit program
        addi a7, zero, 10
        ecall