// Да се напише програма на С, която получава като параметър
// име на файл. Отваря подадения файл за писане (ако не съществува,
// го създава, в противен случай го занулява), създава 2 процеса и
// двата процеса пишат символния низ Hello във файла.
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROCESS_COUNT 2
#define MSG "Hello\n"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "invalid args\n");
        exit(1);
    }

    char* fileName = argv[1];
    int fd = open(fileName, O_CREAT | O_WRONLY | O_TRUNC, 0666);

    if (fd < 0) {
        perror("can't open file");
        exit(1);
    }

    for (int i = 0; i < PROCESS_COUNT; i++) {
        if (fork()) {
            wait(NULL);
        } else {
            write(fd, MSG, strlen(MSG));
            close(fd);
            exit(0);
        }
    }

    close(fd);
}