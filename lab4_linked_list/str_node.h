#ifndef STR_NODE_H
#define STR_NODE_H

#include <stdbool.h>

struct str_node_t {
  char *data;              // Pointer to dynamically allocated string buffer
  int length;              // Number of characters (including '\0')
  struct str_node_t *next; // Pointer to next node in list
};

// Function prototypes
struct str_node_t *str_node_create(char *str, int length);
void str_node_free(struct str_node_t *node);

bool str_node_eq(const struct str_node_t *node1, const struct str_node_t *node2);
void str_node_copy(struct str_node_t *dest, const struct str_node_t *src);

#endif
