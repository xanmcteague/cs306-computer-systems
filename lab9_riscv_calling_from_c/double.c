// double.c

#include <stdio.h>
#include <stdlib.h>

// This prototype is necessary for the compiler;
// the actual code will be supplied in assembly language.
int double_value(int n);

int main(int argc, char* argv[])
{
    int max_num = 80;

    if (argc > 1)
        max_num = atoi(argv[1]);

    printf("Doubling the values from 1 to %d:\n", max_num);
    for (int i = 1; i <= max_num; i++)
    {
        int n = double_value(i);
        printf("%7d", n);
        if (i % 10 == 0)
            printf("\n");
    }

    return EXIT_SUCCESS;
}
