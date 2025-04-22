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

#define READ_BUFFER_SIZE 1024
#define MAX_FILEPATH_SIZE 4096

// function to print usage instructions
void print_usage() {
    fprintf(stderr, "Usage: ./mygrep -s <filter> [-f <file>] [-h]\n");
}

int main (int argc, char * argv[]) {
    FILE *input = stdin;
    char *filename = NULL;
    char *filter = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int opt;

    // process command-line args
    while ((opt = getopt(argc, argv, "s:f:h")) != -1) {
        switch (opt) {
            case 's':
                filter = optarg;
                break;
            case 'f':
                filename = optarg;
                break;
            case 'h':
                print_usage();
                return 0;
            default:
                print_usage();
                return 1;
        }
    }

    // check if search term is missing
    if (!filter) {
        print_usage();
        return 1;
    }

    //open file if specified
    if (filename) {
        input = fopen(filename, "r");
        if (!input) {
            perror("fopen");
            return 1;
        }
    }

    //read lines and print matching ones
    while ((read = getline(&line, &len, input)) != -1) {
        if (strstr(line, filter)) {
            fputs(line, stdout);
        }
    }

    //cleanup
    free(line);
    if (input != stdin) {
        fclose(input);
    }

    return 0;
}
