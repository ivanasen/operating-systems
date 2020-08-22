// Да се напише програма на C, която изпълнява последователно подадените ѝ
// като параметри команди, като реализира следната функционалност постъпково:
// 1. main cmd1 ... cmdN Изпълнява всяка от командите в отделен дъщерен процес.
// 2. запазва се броя на изпълнените команди, които са дали грешка и броя на
// завършилите успешно.

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const int ERR = -1;

pid_t forkAndExec(char* cmd) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Couldn't fork!");
        exit(ERR);
    } else if (pid > 0) {
        return pid;
    } else {
        if (execlp(cmd, cmd, NULL) == -1) {
            printf("Error running command: %s\n", cmd);
            exit(ERR);
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Invalid arguments.\n");
        return ERR;
    }

    char** cmds = argv + 1;
    int cmdCount = argc - 1;

    // Problem statement doesn't say to start all processes in parallel but
    // we're gonna do it anyway.
    pid_t* pids = (pid_t*)malloc(cmdCount * sizeof(pid_t));

    for (int i = 0; i < cmdCount; i++) {
        char* cmd = cmds[i];
        pid_t pid = forkAndExec(cmd);
        pids[i] = pid;
    }

    // Wait for the processes
    int failed = 0;
    for (int i = 0; i < cmdCount; i++) {
        int stat;
        waitpid(pids[i], &stat, 0);
        if (stat != 0) {
            failed++;
        }
    }

    printf("Successful commands: %d\n", cmdCount - failed);
    printf("Failed commands: %d\n", failed);

    return 0;
}
