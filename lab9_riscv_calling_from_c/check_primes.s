# check_primes.s

                .text
                .globl check_primes

# is_prime function from previous exercise
is_prime:
            addi a2, zero, 2 # int i = 2
            addi a3, zero, 1 # yes = 1

loop:       beq a2, a0, ret
            beq a3, zero, ret
            rem t0, a0, a2 # a0 % a2 = n % i and place in t0
            beq t0, zero, not # if n % i == 0, jump to not
            addi a2, a2, 1 # increment i
            j loop
not:
            addi a3, a3, -1
            j loop
ret:
            mv a0, a3
            jr ra

# void check_primes(int a, int b, int *r)
# Parameters: a in a0, b in a1, r in a2
check_primes:
                # TODO: Save ra and any s-registers on the stack (using sd, 8 bytes each)
                # Loop from a (inclusive) to b (exclusive), call is_prime(i),
                # and store each 32-bit int result into r[i - a] (using sw, 4 bytes each).
                # Restore saved registers and ra (using ld) before returning.
                addi sp, sp, -16
                sw ra, 12(sp)
                sw s0, 8(sp)
                sw s1, 4(sp)
                sw s2, 2(sp) # saving registers and ra
                sw s3, 0(sp)
                la s0, a0
                lw s0, 0(a0) # s0 = a
                la s1, a0
                lw s1, 0(a0) # s1 = i
                la s2, a2 # load address/pointer of array into s2
                mv s3, a1 # s3 = b

check_loop:     bge s1, s3, done
                mv a0, s1
                jal ra, is_prime
                sub t0, s1, s0      # t0 = (i - a)
                slli t0, t0, 2      # compute offset *4
                add t0, s2, t0      # list + offset
                sw a0, 0(t0)        # save
                addi s1, s1, 1      # increment i++
                j check_loop

done:
                lw s3, 0(sp)
                lw s2, 2(sp)
                lw s1, 4(sp)
                lw s0, 8(sp)
                lw ra, 12(sp)
                addi sp, sp, 16
                jr ra
