// Да се напише програма на C, която получава като параметри в командния ред 2
// команди (без параметри). Програмата реализира конструкцията: команда1 &&
// команда2

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const int ERR = 1;

pid_t forkAndExec(char* cmd) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Couldn't fork!");
        exit(ERR);
    } else if (pid > 0) {
        return pid;
    } else {
        if (execlp(cmd, cmd, NULL) == -1) {
            printf("Error running command: %s", cmd);
            exit(ERR);
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Invalid arguments!\n");
        return ERR;
    }

    char* cmd1 = argv[1];
    char* cmd2 = argv[2];

    int pid1 = forkAndExec(cmd1);

    int status;
    waitpid(pid1, &status, 0);
    if (status == 0) {
        forkAndExec(cmd2);
    }

    return 0;
}