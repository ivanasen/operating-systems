#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "invalid args");
        return 1;
    }

    char *cmd1 = argv[1];
    char *cmd2 = argv[2];

    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    if (!fork()) {
        if (close(fd[0]) == -1) {
            perror("close");
            return 1;
        }

        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            return 1;
        }

        execlp(cmd1, cmd1, 0);
        perror("execlp");
        return 1;
    }

    if (close(fd[1]) == -1) {
        perror("close");
        return 1;
    }

    if (dup2(fd[0], STDIN_FILENO) == -1) {
        perror("dup2");
        return 1;
    }

    execlp(cmd2, cmd2, 0);
    perror("execlp");
    return 1;
}