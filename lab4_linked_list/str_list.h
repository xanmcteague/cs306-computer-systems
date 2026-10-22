#ifndef STR_LIST_H
#define STR_LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "str_node.h"

struct list_t
{
    struct str_node_t *head;   // Pointer to the first node in the list
    struct str_node_t *tail;   // Pointer to the last node (enables O(1) appends)
    size_t count;              // Number of elements currently in the list
};

void list_init(struct list_t *the_list);                            // Initialize list fields
void list_destroy(struct list_t *the_list);                         // Deallocate list memory
void list_append(struct list_t *the_list, char *item, int length);  // Append item to tail
size_t list_length(struct list_t the_list);                         // Return list element count
void list_print(struct list_t the_list);                            // Print formatted list contents
bool list_contains(struct list_t the_list, char *item, int length); // Return true if item is in list, false otherwise
bool list_equal(struct list_t list1, struct list_t list2);          // Return true if both lists hold the same values

#endif
