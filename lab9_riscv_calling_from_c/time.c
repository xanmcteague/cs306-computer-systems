// time.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void add_second(struct tm *the_time);   // implement this in add_second.s

int main(void)
{
    time_t seconds = time(NULL);
    struct tm *current_time = localtime(&seconds);

    printf("It is now: %s\n", asctime(current_time));

    for (int i = 0; i < 2345; i++) {
        add_second(current_time);
    }

    printf("+2345 seconds: %s\n", asctime(current_time));
    // then print: "+2345 seconds: %s\n"

    return EXIT_SUCCESS;
}
