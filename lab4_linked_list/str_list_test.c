// str_list_test.c
// CSCI 306 Lab04 - exercises the list API so Valgrind can check it (Exercise 4.3).
//
// NOTE (Claude): reconstructed -- the Exercise 4.1 version of this file was not
// in the directory. It builds ONE list of 100 items, which reproduces the
// "201 allocs, 201 frees" heap usage shown in exercise_4_3.md:
//   100 nodes + 100 string buffers = 200, plus 1 buffer glibc allocates
//   internally on the first printf.
// If you still have your own str_list_test.c from 4.1, use that one instead.

#include <stdio.h>
#include <stdlib.h>

#include "str_list.h"

#define NUM_ITEMS 100
#define ITEM_LEN  7      // "item NN" is up to 6 chars + '\0'

int main(void) {
    char item[16];
    struct list_t the_list;

    list_init(&the_list);

    // build the list -- 2 heap allocations per append (node + payload buffer)
    for (int i = 0; i < NUM_ITEMS; i++) {
        snprintf(item, sizeof(item), "item %d", i);
        list_append(&the_list, item, ITEM_LEN);
    }

    printf("length: %zu\n", list_length(the_list));

    // membership: a hit and a miss (neither allocates)
    printf("contains \"item 0\": %d\n", list_contains(the_list, "item 0", ITEM_LEN));
    printf("contains \"nope\":   %d\n", list_contains(the_list, "nope", 5));

    // hand every byte back to the heap
    list_destroy(&the_list);

    // list_destroy must also reset the struct, not just free the nodes
    printf("after destroy, length: %zu\n", list_length(the_list));

    return EXIT_SUCCESS;
}
