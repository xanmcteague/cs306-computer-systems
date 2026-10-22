# CSCI 306 Lab04 - Makefile
# -g  : emit debug symbols so gdb can show source lines (Exercise 4.2)
# -O0 : no optimization, so gdb/valgrind line numbers match the source

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g -O0

PROGS   = list_equal_test str_list_test
OBJS    = str_node.o str_list.o

all: $(PROGS)

list_equal_test: list_equal_test.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

str_list_test: str_list_test.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# object files depend on the headers that declare their interfaces
str_node.o:        str_node.c str_node.h
str_list.o:        str_list.c str_list.h str_node.h
list_equal_test.o: list_equal_test.c str_list.h str_node.h
str_list_test.o:   str_list_test.c str_list.h str_node.h

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Exercise 4.3: check the list implementation for leaks.
# Only str_list_test is checked, which is what exercise_4_3.md specifies.
# Do NOT valgrind list_equal_test -- that file is given by the lab and never
# calls list_destroy, so it leaks 28 blocks by design. That is the test
# program's doing, not a bug in str_list.c / str_node.c.
valgrind: str_list_test
	valgrind --leak-check=full --show-leak-kinds=all ./str_list_test

clean:
	rm -f $(PROGS) *.o

.PHONY: all valgrind clean
