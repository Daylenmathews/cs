/* 
 * Author: Luke Hindman, Daylen Mathews
 * Date: Fri 13 Nov 2020 12:21:37 PM PST
 * Description: Starter code for stream processing lab
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#define INITIAL_CAPACITY 16
#define READ_BUFFER_SIZE 1024
#define MAX_FILEPATH_SIZE 4096

// print usage
void print_usage() {
    fprintf(stderr, "Usage: ./mysort [-f <file>] [-r] [-h]\n");
}

//compare function for ascending sort
int compareAsc(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

// compare function for descending sort
int compareDesc(const void *a, const void *b) {
    return strcmp(*(char **)b, *(char **)a);
}

int main (int argc, char * argv[]) {
    FILE *input = stdin;
    char *filename = NULL;
    bool reverse = false;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int opt;

    // parse arguments
    while ((opt = getopt(argc, argv, "f:rh")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'r':
                reverse = true;
                break;
            case 'h':
                print_usage();
                return 0;
            default:
                print_usage();
                return 1;
        }
    }

    // open file
    if (filename) {
        input = fopen(filename, "r");
        if (!input) {
            perror("fopen");
            return 1;
        }
    }

    size_t capacity = INITIAL_CAPACITY, count = 0;
    char **lines = malloc(capacity * sizeof(char *));
    if (!lines) {
        perror("malloc");
        return 1;
    }

    //read and store all lines
    while ((read = getline(&line, &len, input)) != -1) {
        if (count == capacity) {
            capacity *= 2;
            lines = realloc(lines, capacity * sizeof(char *));
            if (!lines) {
                perror("realloc");
                return 1;
            }
        }
        lines[count++] = strdup(line);
    }
    free(line);

    //sort lines
    qsort(lines, count, sizeof(char *), reverse ? compareDesc : compareAsc);

    //print lines
    for (size_t i = 0; i < count; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }
    free(lines);

    if (input != stdin) {
        fclose(input);
    }


    return 0;
}
