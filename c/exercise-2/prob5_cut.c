// Да се напише програма на C, която реализира командата cut -cm-n файл
// (m и n да се четат от входа)

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int BUFF_SIZE = 100;
const int STDIN = 0;
const int STDOUT = 1;
const int STDERR = 2;
const int ERR = 1;
const int ARGC = 2;

int main(int argc, char *argv[]) {
    if (argc != ARGC) {
        write(STDERR, "Invalid arguments\n", 18);
        return ERR;
    }

    char *file = argv[1];
    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        write(STDERR, "Error reading file\n", 19);
        return ERR;
    }

    char input[BUFF_SIZE];
    memset(input, 0, BUFF_SIZE);
    read(STDIN, input, BUFF_SIZE);
    int m = atoi(input);
    if (input != "0" && m == 0) {
        write(STDERR, "Invalid value for m\n", 20);
        return ERR;
    }
    memset(input, '\0', BUFF_SIZE);
    read(STDIN, input, BUFF_SIZE);
    int n = atoi(input);
    if (input != "0" && n == 0) {
        write(STDERR, "Invalid value for n\n", 20);
        return ERR;
    }

    char buffer[1];
    int column = 1;
    while (read(fd, buffer, 1) > 0) {
        if (column >= m && column <= n) {
            write(STDOUT, buffer, 1);

            if (buffer[0] == '\n') {
                column = 0;
            }
        } else if (buffer[0] == '\n') {
            write(STDOUT, buffer, 1);
            column = 0;
        }

        column++;
    }

    write(STDOUT, "\n", 1);

    close(fd);
    return 0;
}
