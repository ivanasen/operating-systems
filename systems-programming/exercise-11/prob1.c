#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    if (!fork()) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);

        execlp("who", "who", 0);
        perror("execlp");
        return 1;
    }

    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);

    execlp("wc", "wc", "-l", 0);
    perror("execlp");
    return 1;
}