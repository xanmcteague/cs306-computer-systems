// head.c
// CSCI 306 Lab 03
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

// define global variables
#define MAX_LINES 100
#define MAX_LENGTH 255
#define DEFAULT_LINES 10

// helper read_file_lines
int read_file_lines(FILE *fd, char buffer[MAX_LINES][MAX_LENGTH + 1], int lines_expected) {
    int lines_read = 0;

    if (lines_expected > MAX_LINES) {
        lines_expected = MAX_LINES;
    }

    // read
    while (lines_read < lines_expected && 
            fgets(buffer[lines_read], MAX_LENGTH + 1, fd) != NULL) {
        lines_read++;
    }

    return lines_read;
}

// main entry
int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Usage: ./head <filename> [num_lines]\n");
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    int lines_expected = DEFAULT_LINES;

    // optional argv[2]
    if (argc == 3) {
        char *endptr = NULL;
        errno = 0;
        long value = strtol(argv[2], &endptr, 10);
    
        if (endptr == argv[2] || *endptr != '\0' || errno == ERANGE ||
                value <= 0 || value > INT_MAX) {
            printf("Invalid number of lines\n");
            exit(EXIT_FAILURE);
        }

        lines_expected = (int)value;
    }

    FILE *fd = fopen(filename, "r");
    if (fd == NULL) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_LINES][MAX_LENGTH + 1];
    int lines_read = read_file_lines(fd, buffer, lines_expected);

    for (int i = 0; i < lines_read; i++) {
        printf("%s", buffer[i]);
    }

    fclose(fd);
    return EXIT_SUCCESS;
}

