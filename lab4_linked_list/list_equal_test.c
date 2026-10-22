#include <stdio.h>
#include <stdlib.h>
#include "str_list.h"

int main(void) {
  char item[10];
  struct list_t my_list;      // a list of items 0-4
  struct list_t shorter_list; // shorter than my_list
  struct list_t diff_list;    // same length, different values

  list_init(&my_list);
  list_init(&shorter_list);
  list_init(&diff_list);

  for (int i = 0; i < 5; i++) {
    snprintf(item, 7, "item %d", i);
    list_append(&my_list, item, 7);
    if (i < 4){
        list_append(&shorter_list, item, 7);
    }
    if (i==2){
        list_append(&diff_list, "i'm different", 14);  
    }else{
        list_append(&diff_list, item, 7);  
    }
  }

  // tests
  printf("Test 1: %d\n", list_equal(my_list, my_list)); // same list
  printf("Test 2: %d\n",
         list_equal(my_list, shorter_list)); // list, shorter list
  printf("Test 3: %d\n",
         list_equal(shorter_list, my_list)); // shorter list, list
  printf("Test 4: %d\n",
         list_equal(my_list, diff_list)); // different lists, same length

  return EXIT_SUCCESS;
}
