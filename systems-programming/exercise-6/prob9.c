// Да се напише програма на C, която получава като командни параметри две
// команди (без параметри). Изпълнява ги едновременно и извежда на стандартния
// изход номера на процеса на първата завършила успешно. Ако нито една не
// завърши успешно извежда -1.
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define CDM_COUNT 2

int main(int argc, char** argv) {
    if (argc - 1 != CDM_COUNT) {
        fprintf(stderr, "invalid args\n");
        exit(1);
    }

    for (int i = 0; i < CDM_COUNT; i++) {
        pid_t pid;
        if (!(pid = fork())) {
            execlp(argv[i + 1], argv[i + 1], 0);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }

    pid_t pid;
    int status;
    while ((pid = wait(&status)) > 0) {
        if (!status) {
            printf("%d\n", pid);
            exit(0);
        }
    }

    exit(-1);
}