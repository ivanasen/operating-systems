// Да се напише програма на C, която създава файл abc в текущата директория и го
// отваря за писане. Създава 2 процеса, които пишат в него hello.

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

const int ERR = -1;
const char* MSG = "hello";

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

void forkAndWriteToFile(int fd) {
    int pid = fork();
    if (pid == -1) {
        perror("Couldn't fork!");
        exit(ERR);
    } else if (pid > 0) {
        return;
    }

    int ok = write(fd, MSG, strlen(MSG));
    if (ok == -1) {
        fprintf(stderr, "Error writing to file!\n");
        exit(ERR);
    }
    exit(0);
}

int main() {
    const char* file = "abc";

    int fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);

    forkAndWriteToFile(fd);
    forkAndWriteToFile(fd);

    close(fd);

    return 0;
}
