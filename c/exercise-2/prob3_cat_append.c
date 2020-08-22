// Да се напише програма на C, която реализира командата cat >>файл

#include <fcntl.h>
#include <unistd.h>

const int BUFF_SIZE = 100;
const int STDIN = 0;
const int STDOUT = 1;
const int STDERR = 2;
const int ERR = 1;

int ARGC = 2;

int main(int argc, char *argv[]) {
    if (argc != ARGC) {
        write(STDERR, "Invalid arguments\n", 19);
        return ERR;
    }

    // get the file name without ">>"
    char *file = &argv[1][2];

    int fd = open(file, O_WRONLY | O_CREAT | O_APPEND);
    if (fd == -1) {
        write(STDERR, "Error opening file\n", 19);
        return ERR;
    }

    char *buffer[BUFF_SIZE];
    int count;
    while ((count = read(STDIN, buffer, BUFF_SIZE)) > 0) {
        int size = write(fd, buffer, count);
        if (size == -1) {
            write(STDERR, "Error writing to file\n", 19);
        }
    }

    close(fd);

    return 0;
}
