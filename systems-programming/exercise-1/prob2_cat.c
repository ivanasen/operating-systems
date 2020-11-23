// Да се напише програма на C, която реализира командата cat (без параметри)

#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define BUFFSIZE 3

int main() {
    char buffer[BUFFSIZE];

    while(1) {
        int readCount = read(0, buffer, BUFFSIZE);
        if (readCount < 0) {
            puts("Error reading from stdin");
            return 1;
        }

        int writeCount = 0;
        while(writeCount < readCount) {
            int writeCountCurr = write(1, buffer + writeCount, readCount - writeCount);
            if (writeCountCurr < 0 && errno == EINTR) {
                continue;
            } else if (writeCountCurr < 0) {
                puts("Error writing to file");
                return 1;
            }
            writeCount += writeCountCurr;
        }
    }

    return 0;
}
