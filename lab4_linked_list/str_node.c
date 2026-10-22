// str_node.c
// CSCI 306 Lab04 - Linked Lists
//

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "str_node.h"

// Allocate a node plus its own private copy of the string.
// Returns NULL if the arguments are bad or either allocation fails.
struct str_node_t *str_node_create(char *str, int length) {
    if (str == NULL || length <= 0) {
        return NULL;
    }

    struct str_node_t *node = malloc(sizeof(struct str_node_t));
    if (node == NULL) {
        return NULL;
    }

    node->data = malloc(length);
    if (node->data == NULL) {
        // don't leak the node we just allocated
        free(node);
        return NULL;
    }

    // copy at most length-1 chars, then terminate by hand so that the
    // buffer is always a valid C string even if str was longer
    strncpy(node->data, str, length - 1);
    node->data[length - 1] = '\0';

    node->length = length;
    node->next = NULL;   // critical: a fresh node is not linked to anything

    return node;
}

// Free a node and the string buffer it owns.
void str_node_free(struct str_node_t *node) {
    if (node == NULL) {
        return;
    }
    free(node->data);   // free the payload first...
    free(node);         // ...then the node itself
}

// Two nodes are equal if their payloads have the same length and contents.
bool str_node_eq(const struct str_node_t *node1, const struct str_node_t *node2) {
    if (node1 == node2) {
        return true;    // same pointer (covers NULL == NULL)
    }
    if (node1 == NULL || node2 == NULL) {
        return false;   // exactly one is NULL
    }
    if (node1->length != node2->length) {
        return false;
    }
    return strcmp(node1->data, node2->data) == 0;
}

// Deep-copy src  into dest, replacing dest
// dest->next untouched
void str_node_copy(struct str_node_t *dest, const struct str_node_t *src) {
    if (dest == NULL || src == NULL) {
        return;
    }

    // allocate the new buffer BEFORE freeing the old one, so failed
    // malloc leaves dest untouched instead of holding a dangling pointer
    char *buffer = malloc(src->length);
    if (buffer == NULL) {
        return;
    }
    memcpy(buffer, src->data, src->length);

    free(dest->data);
    dest->data = buffer;
    dest->length = src->length;
}
