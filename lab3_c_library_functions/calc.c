// calc.c
// CSCI 306 Lab 03: Using Library Functions in C
// xander mcteague
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isvalid(char *str) {
    if (strcmp(str, "add") == 0 || strcmp(str, "sub") == 0 ||
            strcmp(str, "mult") == 0 || strcmp(str, "div") == 0 || strcmp(str, "len") == 0) {
        //printf("%s is a valid command\n", str);
        return true;
    } else {
        printf("%s is an invalid command\n", str);
        return false;
    }
}

int main(int argc, char *argv[]) {
    // validate arguments
    if (argc < 2) {
        printf("No arguments passed\n");
        return EXIT_FAILURE;
    } else if (argc < 3) {
        printf("Incorrect number of arguments\n");
        return EXIT_FAILURE;
    } else if (!isvalid(argv[1])) { // check first arg is command
        return EXIT_FAILURE;
    }

    for (int i = 2; i < argc; i++) {
        char *endptr;
        strtol(argv[i], &endptr, 10);

        if (endptr != argv[i] && *endptr == '\0') {
        //    printf("%s is an integer\n", argv[i]);
            continue;
        } else {
            //printf("%s is not an integer\n", argv[i]);
            continue;
        }
    }

    if (strcmp(argv[1], "len") == 0) {
        int length = 0;
        for (int i = 2; i < argc; i++) {
            char *endpt;
            strtol(argv[i], &endpt, 10);

            if (endpt != argv[i] && *endpt == '\0') {
                return EXIT_FAILURE;
            }
            length += strlen(argv[i]);
        }
        
        printf("%d\n", length);
    }
    else {
        for (int x = 2; x<argc; x++) {
            char *endpt;
            strtol(argv[x], &endpt, 10);
            if (!(endpt != argv[x] && *endpt == '\0')) {
                printf("Invalid operands\n");
                return EXIT_FAILURE;
            }
        }
    
    if (argc < 4) {
        printf("Incorrect number of arguments\n");
        return EXIT_FAILURE;
    }
                    

    int num1, num2;
    num1 = atoi(argv[2]);
    num2 = atoi(argv[3]);

    if (strcmp(argv[1], "add") == 0) {
        int num3 = num1 + num2;
        printf("%d\n", num3);
    } else if (strcmp(argv[1], "sub") == 0) {
        int num3 = num1 - num2;
        printf("%d\n", num3);
    } else if (strcmp(argv[1], "mult") == 0) {
        int num3 = num1 * num2;
        printf("%d\n", num3);
    } else {
        if (num2 == 0) {
            printf("Division by zero\n");
            return EXIT_FAILURE;
        } else {
            int num3 = num1 / num2;
            printf("%d\n", num3);
        }
    }
    }

    return EXIT_SUCCESS;
}

