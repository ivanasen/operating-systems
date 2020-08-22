// При отпечатването на PID-a на процесите родител и дете,
// в детето с достатъчно дълъг цикъл без печат  да се задържи детето,
// за да приключи своята работа процеса родител.

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int ERR = -1;

void parent() {
    printf("Doing work from parent...\n");
    sleep(1);
    printf("Done with work in parent\n");
}

void child() {
    pid_t parentPid = getppid();
    // This is the preffered way to do it
    // while (!kill(parentPid, 0)) {
    // }
    // But this is what the problem statement wants
    for (unsigned long long i = 0; i < 1000000000; i++) {
    }
    printf("Done waiting for parent!");
}

int main() {
    int pid = fork();
    if (pid == -1) {
        perror("Couldn't fork!");
        exit(ERR);
    } else if (pid > 0) {
        parent();
    } else {
        child();
    }

    return 0;
}