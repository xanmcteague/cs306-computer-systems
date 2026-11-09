# is_prime.s

            .text
            .globl is_prime

# int is_prime(int n)
# Parameter: n in a0
# Return:    1 if n is prime, 0 otherwise (in a0)
is_prime:
            # TODO: Implement is_prime
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

