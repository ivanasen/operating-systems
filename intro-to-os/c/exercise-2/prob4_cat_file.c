// Да се напише програма на C, която реализира командата cat [файл] [...]

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

    char *file = argv[1];
    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        write(STDERR, "Error opening file\n", 19);
        return ERR;
    }

    char *buffer[BUFF_SIZE];
    int count;
    while ((count = read(fd, buffer, BUFF_SIZE)) > 0) {
        write(STDOUT, buffer, count);
    }

    close(fd);

    return 0;
}
