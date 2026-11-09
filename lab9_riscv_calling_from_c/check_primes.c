// check_primes.c

#include <stdio.h>
#include <stdlib.h>

void check_primes(int a, int b, int *r);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s left count\n", argv[0]);
    printf("Where left is the starting int (left > 0), count is how many.\n");
    exit(EXIT_FAILURE);
  }

  int left = atoi(argv[1]);
  int right = left + atoi(argv[2]);
  int count = right - left + 1; // how many
  int *results = (int *)malloc(count * sizeof(int));

  printf("left = %d, right = %d\n", left, right);

  check_primes(left, right, results);

  for (int i = left; i < right; i++)
    printf("%7d %7s prime.\n", i, (results[i - left] == 1) ? "is " : "isn't ");

  return EXIT_SUCCESS;
}
