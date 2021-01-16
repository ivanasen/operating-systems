// Да се пуснат един след друг два системни примитива fork(),
// като за всеки генериран процес се отпечатва pid-а на
// процеса/getpid()/ и pid-a на родителския ппроцес/getppid()/.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define CHILDREN_COUNT 2

void child() {
    pid_t pid = getpid();
    pid_t ppid = getppid();
    printf("pid: %d, ppid: %d\n", pid, ppid);
    exit(0);
}

int main(int argc, char** argv) {
    for (int i = 0; i < CHILDREN_COUNT; i++) {
        if (!fork()) {
            child();
        }
    }

    // wait for children to finish
    while (wait(NULL) > 0);
}