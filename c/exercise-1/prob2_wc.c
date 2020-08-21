// Да се напише програма на C, която реализира командата wc файл

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const int ARGS_COUNT = 2;
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
    int fileDescriptor = open(fileName, O_RDONLY);

    if (fileDescriptor == -1) {
        perror("Failed to open file");
        return ERROR;
    }

    int byteCount = getFileSize(fileName);

    if (byteCount == -1) {
        perror("Error reading file size!");
        return ERROR;
    }

    char *buffer = (char *)malloc(byteCount);
    read(fileDescriptor, buffer, byteCount);

    int newLineCount = countNewLines(buffer, byteCount);
    int wordCount = countWords(buffer, byteCount);

    printf("%d %d %d %s\n", newLineCount, wordCount, byteCount, fileName);
}

int main(int argc, char **argv) {
    if (argc != ARGS_COUNT) {
        puts("Invalid arguments!");
        return ERROR;
    }

    return wc(argv[1]);
}
