// Да се напише програма на C, която реализира командата 
// tee [файл1 файл2 ..... файлN ]

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define BUFFSIZE 100

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
    int filesCount = argc;
    char **files = argv + 1;

    int *fds = (int*) malloc(argc * sizeof(int));
    fds[0] = 0; // Add stdin
    for (int i = 1; i < filesCount; i++) {
        fds[i] = open(files[i - 1], O_WRONLY | O_CREAT, 0666);

        if (fds[i] < 0) {
            printf("Error opening file %s\n", files[i]);
            exit(1);
        }
    }

    char buffer[BUFFSIZE];

    while (1) {
        int readCount = read(0, buffer, BUFFSIZE);
        if (readCount < 0) {
            puts("Error reading from stdin");
            exit(1);
        }

        for (int i = 0; i < filesCount; i++) {
            writeToFile(readCount, buffer, fds[i]);
        }
    }

    return 0;
}
