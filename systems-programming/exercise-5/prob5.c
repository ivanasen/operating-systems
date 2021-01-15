// Да се напише програма на С, която получава като параметри
// три команди (без параметри), изпълнява ги последователно,
// като изчаква края на всяка и извежда на стандартния изход номера на
// завършилия процес, както и неговия код на завършване
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// gonna do it fo N commands
int main(int argc, char** argv) {
    if (argc == 1) {
        fprintf(stderr, "invalid args\n");
        exit(1);
    }

    char** cmds = argv + 1;
    int cmdCount = argc - 1;
    int status;
    pid_t pid;

    for (int i = 0; i < cmdCount; i++) {
        if (fork()) {
            pid = wait(&status);
            if (WIFEXITED(status)) {
                printf("pid: %d, status: %d\n", pid, WEXITSTATUS(status));
            } else {
                printf("pid: %d, didn't exit normally\n", pid);
            }
        } else {
            execlp(cmds[i], cmds[i], 0);
        }
    }
}