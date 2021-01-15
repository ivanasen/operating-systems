// Да се напише програма на С, която получава като параметри имена на два файла.
// В зад 6 пренасочва изхода на процеса дете във втория файл
// (ако не съществува, го създава, в противен случай добавя в него)

// Not really much point in redirecting stdout since the children
// don't write to it. Going to just redirect stdout to the file from the
// first argument and write "Hello" to it.
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
    int fd = open(fileName, O_CREAT | O_WRONLY | O_APPEND, 0666);

    if (fd < 0) {
        perror("can't open file");
        exit(1);
    }

    for (int i = 0; i < PROCESS_COUNT; i++) {
        if (fork()) {
            wait(NULL);
        } else {
            dup2(fd, STDOUT_FILENO);
            close(fd);

            printf(MSG);
            exit(0);
        }
    }

    close(fd);
}