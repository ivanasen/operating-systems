// Да се напише програма на C, която реализира командата cut -cm-n файл
// (m и n да се четат от входа)

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFSIZE = 100;
const int ARGC = 4;

int main(int argc, char *argv[]) {
    if (argc != ARGC) {
        puts("Invalid arguments");
        return 1;
    }

    char *mStr = argv[1];
    int m = atoi(mStr);

    char *nStr = argv[2];
    int n = atoi(nStr);

    char *file = argv[3];
    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        puts("Error reading file");
        return 1;
    }

    char buffer;
    int column = 1;
    while (read(fd, &buffer, 1) > 0) {
        if (column >= m && column <= n) {
            write(1, &buffer, 1);
        }
        
        if (buffer == '\n') {
            if (column < m || column > n) {
                write(1, &buffer, 1);
            }
            column = 0;
        }

        column++;
    }

    close(fd);
    return 0;
}
