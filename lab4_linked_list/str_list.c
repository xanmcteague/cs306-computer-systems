// str_list.c
// CSCI 306 Lab04 - Linked Lists
// linked list stucture file and function definitions

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "str_node.h"
#include "str_list.h"


// list_init method
void list_init(struct list_t *the_list) {
    // set head and tail pointers to null, length to zero
    the_list->head = NULL;
    the_list->tail = NULL;
    the_list->count = 0;
}

// memory deallocation
void list_destroy(struct list_t *the_list) {
    // set the current node to be the head pointer
    struct str_node_t *current;
    current = the_list->head;
    
    struct str_node_t *temp;
    // while the current node (not the node's data) is not null
    while (current != NULL) {
        // create a node pointer temp
        //struct str_node_t *temp;
        // and point it to cur.next
        temp = current->next;
        // hand the node back to str_node_free, which owns node teardown:
        // it frees the payload buffer AND the node itself. Keeping the two
        // free() calls here would mean str_node.c and str_list.c both had to
        // be updated if struct str_node_t ever gained another heap field.
        str_node_free(current);
        // set current to temp and repeat
        current = temp;
    }
    // reset list 
    the_list->head = NULL;
    the_list->tail = NULL;
    the_list->count = 0;
}

// append items
void list_append(struct list_t *the_list, char *item, int length) {
    // step 1: call str_node_create to allocate new node
    struct str_node_t *new_node;
    new_node = str_node_create(item, length);
    // step 2: handle allocation failure
    if (new_node == NULL) {
        return;
    }
    // handle empty vs non-empty list cases
    if (the_list->head == NULL) {
        // if empty set head and tail to new_node
        the_list->head = new_node;
        the_list->tail = new_node;
    } else {
        // else set tail->next to new_node
        the_list->tail->next = new_node;
    }

    // update tail pointer
    the_list->tail = new_node;

    the_list->count += 1;
}

// query length of linked list (num nodes)
size_t list_length(struct list_t the_list) {
    // return length
    return the_list.count;
}

// membership query: is item in the linked list?
bool list_contains(struct list_t the_list, char *item, int length) {
    // init current node to head
    struct str_node_t *current;
    current = the_list.head;
    // traverse while cur is not null
    while (current != NULL) {
        // compare item and current node's data, length == length
        if (strcmp(item, current->data) == 0 && length == current->length) {
            return true;
        }
        // else continue searching list advance to next
        else {
            current = current->next;
        }
    }
    // return false if not found
    return false;
}

// format print the list
void list_print(struct list_t the_list) {
    printf("[");
    struct str_node_t *current;
    current = the_list.head;
    // Iterate through nodes and print. Traverse the chain itself rather than
    // counting to the_list.count: if the two ever disagree, counting walks off
    // the end of the list and dereferences NULL. The chain is the truth.
    while (current != NULL) {
        printf("%s", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

// Check if two lists are equal by traversing the lists and
// comparing their elements
//
// bug fix for exercise 4.2: the original loop condition was `while (n1 != NULL)`,
// which only tracked when list1 ran out. That produced two separate failures:
//
// The repair has two parts:
//   1. Stop as soon as either list ends, so neither pointer is dereferenced
//      after it goes NULL.
//   2. After the loop, both pointers have to land on NULL together.
//      If only one is NULL, lists are not equal
bool list_equal(struct list_t list1, struct list_t list2){
    struct str_node_t *n1 = list1.head;
    struct str_node_t *n2 = list2.head;
    while (n1 != NULL && n2 != NULL){   
        if (strcmp(n1->data, n2->data) != 0){
            return false;       // data mismatch, not equal
        }
        n1 = n1->next;       
        n2 = n2->next;          
    }
    // Equal only if the two lists ran out at the same time. If exactly one
    // pointer is non-NULL, that list is longer and the lists differ.
    return (n1 == NULL && n2 == NULL);
}
