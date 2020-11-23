// Да се напише програма на C, която реализира командата tee файл

#include <fcntl.h>
#include <unistd.h>

const int BUFF_SIZE = 100;
const int STDIN = 0;
const int STDOUT = 1;
const int STDERR = 2;
const int ERR = 1;
const int ARGC = 2;

int main(int argc, char *argv[]) {
    if (argc != ARGC) {
        write(STDERR, "Invalid arguments\n", 19);
        return ERR;
    }

    char *file = argv[1];
    int fd = open(file, O_WRONLY | O_CREAT);

    if (fd == -1) {
        write(STDERR, "Error opening file\n", 19);
        return ERR;
    }

    char *input[BUFF_SIZE];
    int size = read(STDIN, input, BUFF_SIZE);

    if (size == -1) {
        write(STDERR, "Error reading from stdin\n", 25);
        return ERR;
    }

    int stdSize = write(STDOUT, input, size);

    if (stdSize == -1) {
        write(STDERR, "Error writing to stdout\n", 25);
        return ERR;
    }

    int fdSize = write(fd, input, size);
    close(fd);

    if (fdSize == -1) {
        write(STDERR, "Error writing to file\n", 22);
        return ERR;
    }

    return 0;
}
