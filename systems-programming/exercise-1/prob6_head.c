// Да се напише програма на C, която реализира командата head -10l файл

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define BUFFSIZE 100
#define ARGC 2
#define MAX_LINES 10

void writeToFile(int readCount, char buffer[BUFFSIZE], int fd) {
    int writeCount = 0;

    while(writeCount < readCount) {
        int writeCountCurr = write(fd, buffer + writeCount, readCount - writeCount);

        if (writeCountCurr < 0 && errno == EINTR) {
            continue;
        } else if (writeCountCurr < 0) {
            puts("Error writing to file");
            exit(1);
        }

        writeCount += writeCountCurr;
    }
}

int main(int argc, char *argv[]) {
    if (argc != ARGC) {
        puts("Invalid arguments");
        return 1;
    }

    int maxLines = MAX_LINES;
    char *file = argv[1];
    
    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        puts("Error opening file");
        return 1;
    }

    char buffer[BUFFSIZE];
    int newLineCount = 0;

    while (1) {
        int readCount = read(fd, buffer, BUFFSIZE);
        if (readCount < 0) {
            puts("Error reading file");
            return 1;
        } else if (readCount == 0) {
            break;
        }

        int maxWriteCount = readCount;
        for (int i = 0; i < readCount; i++) {
            if (buffer[i] == '\n') {
                newLineCount++;
            }

            if (newLineCount >= maxLines) {
                maxWriteCount = i;
                break;
            }
        }

        writeToFile(maxWriteCount, buffer, 1);
    }

    close(fd);
    return 0;
}

