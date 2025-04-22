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
#include <ctype.h>

#define READ_BUFFER_SIZE 1024
#define MAX_FILEPATH_SIZE 4096

// Print usage info
void print_usage() {
    fprintf(stderr, "Usage: ./mywc [-f <file>] [-c] [-w] [-l] [-h]\n");
}

int main (int argc, char * argv[]) {
    FILE *input = stdin;
    char *filename = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int opt;
    bool countChars = false, countWords = false, countLines = false;

    // parsing options
    while ((opt = getopt(argc, argv, "f:cwlh")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'c':
                countChars = true;
                break;
            case 'w':
                countWords = true;
                break;
            case 'l':
                countLines = true;
                break;
            case 'h':
                print_usage();
                return 0;
            default:
                print_usage();
                return 1;
        }
    }

    if (!countChars && !countWords && !countLines) {
        countChars = countWords = countLines = true;
    }

    //open file if needed
    if (filename) {
        input = fopen(filename, "r");
        if (!input) {
            perror("fopen");
            return 1;
        }
    }

    size_t chars = 0, words = 0, lines = 0;

    //read and count stats
    while ((read = getline(&line, &len, input)) != -1) {
        chars += read;
        lines++;
        bool inWord = false;
        for (int i = 0; i < read; i++) {
            if (isspace(line[i])) {
                inWord = false;
            } else if (!inWord) {
                inWord = true;
                words++;
            }
        }
    }

    if (countLines) printf("%lu ", lines);
    if (countWords) printf("%lu ", words);
    if (countChars) printf("%lu", chars);
    printf("\n");

    free(line);
    if (input != stdin) {
        fclose(input);
    }

    return 0;
}
