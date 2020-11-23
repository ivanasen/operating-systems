// При отпечатването на PID-a на процесите родител и дете,
// в детето със sleep  да се задържи достатъчно дълго,
// за да приключи своята работа процеса родител.

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int ERR = -1;

void parent() {
    printf("Doing work from parent...\n");
    sleep(10);
    printf("Done with work in parent\n");
}

void child() {
    pid_t parentPid = getppid();
    while (!kill(parentPid, 0)) {
        printf("Parent still working so sleeping...\n");
        sleep(3);
    }
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