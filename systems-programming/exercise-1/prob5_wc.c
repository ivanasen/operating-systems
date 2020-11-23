// Да се напише програма на C, която реализира командата 
// wc [-cwl ] [файл1 файл2 ....файлN ]

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const int ARGC = 2;
const int ERROR = 1;

long int getFileSize(const char *fileName) {
    struct stat st;

    if (stat(fileName, &st) != 0) {
        return -1;
    }

    return st.st_size;
}

int countNewLines(const char *buffer, int size) {
    if (size == 0) {
        return 0;
    }

    int count = 1;
    for (int i = 0; i < size; i++) {
        if (buffer[i] == '\n') {
            count++;
        }
    }

    return count;
}

int countWords(const char *buffer, int size) {
    int count = 0;
    bool readingWord = false;

    for (int i = 0; i < size; i++) {
        char c = buffer[i];

        if (readingWord) {
            if (c == ' ' || c == '\n' || c == '\t') {
                readingWord = false;
                count++;
            }
        } else {
            if (c != ' ' && c != '\n' && c != '\t') {
                readingWord = true;
            }
        }
    }

    // If file doesn't end with some kind of whitespace
    if (readingWord) {
        count++;
    }

    return count;
}

int wc(const char *fileName) {
    int fd = open(fileName, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        return ERROR;
    }

    int fileSize = getFileSize(fileName);
    if (fileSize == -1) {
        perror("Error reading file size!");
        return ERROR;
    }

    char *buffer = (char *)malloc(fileSize);
    read(fd, buffer, fileSize);

    int newLineCount = countNewLines(buffer, fileSize);
    int wordCount = countWords(buffer, fileSize);

    printf("%d %d %d %s\n", newLineCount, wordCount, fileSize, fileName);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != ARGC) {
        puts("Invalid arguments!");
        return ERROR;
    }

    return wc(argv[1]);
}
