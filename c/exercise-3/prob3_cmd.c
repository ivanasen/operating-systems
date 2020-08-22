// Да се напише програма на C, която получава като параметър в командния ред
// една команда и при успешното й изпълнение извежда на стандартния изход името
// на командата.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const int ERR = -1;

void parent(const char* cmd) {
    int res;
    wait(&res);
    if (!res) {
        printf("%s\n", cmd);
    }
}

void child(const char* cmd) {
    if (execlp(cmd, cmd, NULL) == -1) {
        printf("Error running command: %s", cmd);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("Invalid arguments!\n");
        return ERR;
    }

    char* cmd = argv[1];

    int pid = fork();
    if (pid == -1) {
        perror("Couldn't fork!");
        exit(ERR);
    } else if (pid > 0) {
        parent(cmd);
    } else {
        child(cmd);
    }

    return 0;
}