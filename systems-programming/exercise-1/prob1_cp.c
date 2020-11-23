// Да се напише програма на C, която реализира командата cp файл1 файл2

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define ARGS_COUNT 3
#define BUFFER_SIZE 100

int main(int argc, char **argv) {
    if (argc != ARGS_COUNT) {
        puts("Invalid arguments");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    char *src = argv[1];
    char *dst = argv[2];

    int srcDescriptor = open(src, O_RDONLY);
    if (srcDescriptor == -1) {
        puts("Failed to open source file");
        return 1;
    }

    int dstDescriptor = open(dst, O_WRONLY | O_CREAT, 0666);
    if (dstDescriptor == -1) {
        puts("Failed to open destination file");
        return 1;
    }

    while(1) {
        int readCount = read(srcDescriptor, buffer, BUFFER_SIZE);
        if (readCount < 0) {
            puts("Error reading from file");
            return 1;
        } else if (readCount == 0) {
            break;
        }

        int writeCount = 0;
        while(writeCount < readCount) {
            int writeCountCurr = write(dstDescriptor, buffer + writeCount, readCount - writeCount);
            if (writeCountCurr < 0 && errno == EINTR) {
                continue;
            } else if (writeCountCurr < 0) {
                puts("Error writing to file");
                return 1;
            }
            writeCount += writeCountCurr;
        }
    }

    close(srcDescriptor);
    close(dstDescriptor);
    return 0;
}
