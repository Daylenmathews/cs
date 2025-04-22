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
    fprintf(stderr, "Usage: ./mycat [-f <file>] [-h]\n");
}

int main (int argc, char * argv[]) {
    FILE *input = stdin;
    char *filename = NULL;
    char buffer[READ_BUFFER_SIZE];
    int opt;

    // process command-line options using getopt
    while ((opt = getopt(argc, argv, "f:h")) != -1) {
        switch (opt) {
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

    //if file name provided, try to open
    if (filename) {
        input = fopen(filename, "r");
        if (!input) {
            perror("fopen");
            return 1;
        }
    }

    //read and print each line from input
    while (fgets(buffer, sizeof(buffer), input)) {
        fputs(buffer, stdout);
    }

    //close file if opened 
    if (input != stdin) {
        fclose(input);
    }

    return 0;
}
