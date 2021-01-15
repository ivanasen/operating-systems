// Да се напише програма на С, която получава като параметър име на файл.
// Създава процес син, който записва стринга Hello във файла
// (ако не съществува, го създава, в противен случай го занулява),
// след което процеса родител прочита записаното във файла съдържание
// и го извежда на стандартния изход, добавяйки по един интервал между
// всеки два символа.
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MSG "Helloo\n"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "invalid args\n");
        exit(1);
    }

    char* fileName = argv[1];
    int fd = open(fileName, O_CREAT | O_RDWR | O_TRUNC, 0666);

    if (fd < 0) {
        perror("can't open file");
        exit(1);
    }

    if (!fork()) {
        size_t msgLength = strlen(MSG);
        if (write(fd, MSG, msgLength) != msgLength) {
            fprintf(stderr, "error writing to file\n");
            exit(1);
        }
        exit(0);
    }

    int status;
    wait(&status);

    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        fprintf(stderr, "child errored\n");
        exit(1);
    }

    lseek(fd, 0, SEEK_SET);

    size_t readCount;
    char c[2];
    while ((readCount = read(fd, c, 2)) > 0) {
        write(STDOUT_FILENO, c, readCount);
        if (readCount == 2) {
            write(STDOUT_FILENO, " ", 1);
        }
    }
}