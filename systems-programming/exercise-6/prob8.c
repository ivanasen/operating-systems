// Да се напише програма на C, която получава като параметри от команден ред две
// команди (без параметри). Изпълнява първата. Ако тя е завършила успешно
// изпълнява втората. Ако не, завършва с код -1.
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define HELLO_1 "hello1\n"
#define HELLO_2 "hello2\n"
#define HELLO_3 "hello3\n"
#define HELLO_4 "hello4\n"

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "invalid args\n");
        exit(1);
    }

    char* cmd1 = argv[1];
    char* cmd2 = argv[2];

    if (!fork()) {
        execlp(cmd1, cmd1, 0);
    }

    int status;
    wait(&status);

    if (!status) {
        execlp(cmd2, cmd2, 0);
    } else {
        exit(-1);
    }
}