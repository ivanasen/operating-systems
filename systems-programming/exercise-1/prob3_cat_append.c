// Да се напише програма на C, която реализира командата cat >>файл

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define BUFFSIZE 100

int ARGC = 2;

int main(int argc, char *argv[]) {
    if (argc != ARGC) {
        puts("Invalid arguments");
        return 1;
    }

    char *file = argv[1];

    int fd = open(file, O_WRONLY | O_CREAT | O_APPEND);
    if (fd == -1) {
        puts("Error reading file");
        return 1;
    }

    char *buffer[BUFFSIZE];
    int readCount;
    while ((readCount = read(0, buffer, BUFFSIZE)) > 0) {
        int writeCount = 0;

        while(writeCount < readCount) {
            int writeCountCurr = write(fd, buffer + writeCount, readCount - writeCount);
            if (writeCountCurr < 0 && errno == EINTR) {
                continue;
            } else if (writeCountCurr < 0) {
                puts("Error writing to file");
                return 1;
            }

            writeCount += writeCountCurr;
        }
    }

    close(fd);

    return 0;
}
