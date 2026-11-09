# add_second.s

            .text
            .globl add_second

# void add_second(struct tm *the_time)
# Parameter: the_time (pointer to struct tm) in a0
#   0(a0) = tm_sec  (4-byte int)
#   4(a0) = tm_min  (4-byte int)
#   8(a0) = tm_hour (4-byte int)
add_second:
            lw   t0, 0(a0)          # t0 = tm_sec
            lw   t1, 4(a0)          # t1 = tm_min
            lw   t2, 8(a0)          # t2 = tm_hour
            li   t3, 60             # rollover limit

            addi t0, t0, 1          # tm_sec++
            blt  t0, t3, store      # if seconds < 60, no carry, done

            li   t0, 0              # if seconds >= 60, seconds = 0
            addi t1, t1, 1          # increment minutes +1
            blt  t1, t3, store      # if minutes < 60, done

            li   t1, 0              # if minutes >= 60, minutes = 0
            addi t2, t2, 1          # increment hours +1

store:
            sw   t0, 0(a0)          # write back tm_sec
            sw   t1, 4(a0)          # write back tm_min
            sw   t2, 8(a0)          # write back tm_hour
            jr   ra
