// Да се напише програма на С, която получава като параметър команда
// (без параметри) и при успешното ѝ изпълнение, извежда на стандартния
// изход името на командата.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Invalid args!\n");
        exit(1);
    }

    char *cmd = argv[1];

    if (fork()) {
        int status;
        wait(&status);
        if (!status) {
            printf("%s\n", cmd);
        }
    } else {
        execlp(cmd, cmd, 0);
    }
}