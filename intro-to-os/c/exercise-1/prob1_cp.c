// Да се напише програма на C, която реализира командата cp файл1 файл2

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const int ARGS_COUNT = 3;
const int ERROR = 1;
const int BUFFER_SIZE = 14;

int main(int argc, char **argv) {
    if (argc != ARGS_COUNT) {
        puts("Invalid arguments!");
        return ERROR;
    }

    char buffer[BUFFER_SIZE];

    char *src = argv[1];
    char *dst = argv[2];

    int srcDescriptor = open(src, O_RDONLY);
    int dstDescriptor = open(dst, O_WRONLY | O_CREAT, 0666);

    if (srcDescriptor == -1) {
        puts("Failed to open source file");
        return ERROR;
    }

    if (dstDescriptor == -1) {
        puts("Failed to open destination file");
        return ERROR;
    }

    while (read(srcDescriptor, buffer, BUFFER_SIZE)) {
        int writeCount = write(dstDescriptor, buffer, BUFFER_SIZE);
        if (writeCount == -1) {
            puts("Error writing to file");
        }
    }

    return 0;
}
