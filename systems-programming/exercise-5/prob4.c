// Да се напише програма на С, която получава като параметър команда
// с опции и аргуманти. При успешното ѝ изпълнение, извежда на
// стандартния изход кода на завършане.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc == 1) {
        fprintf(stderr, "invalid args\n");
        exit(1);
    }

    if (fork()) {
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("%d\n", WEXITSTATUS(status));
        }
    } else {
        execvp(argv[1], argv + 1);
    }
}