// list_primes.c

#include <stdio.h>
#include <stdlib.h>

int is_prime(int n);  // prototype only

int main(int argc, char* argv[])
{
    int max_num = 80;
    if (argc > 1)
        max_num = atoi(argv[1]);

    for (int i = 2; i <= max_num; i++)
        printf("%7d %7s prime.\n", i, (is_prime(i) == 1) ? "is ": "isn't ");

    return EXIT_SUCCESS;
}
