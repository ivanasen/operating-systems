// Да се напише програма на C, която получава като параметри  име на файл и
// команда с опции и аргуманти. Да се изпълни команда, която отпечатва редовете
// от файл, съдържащи символния низ int. Да се изпълни подадената команда с
// опции и аргументи като се отпечата кода й на завършване.

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

const int ERR = -1;

pid_t forkAndExec(char** argv) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Couldn't fork!");
        exit(ERR);
    } else if (pid > 0) {
        return pid;
    } else {
        if (execvp(argv[0], argv) == -1) {
            printf("Error running command: %s", argv[0]);
            exit(ERR);
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Invalid arguments.\n");
        return ERR;
    }

    char* file = argv[1];
    char** cmdArgv = argv + 2;
    char* fileArgv[4] = {"grep", "int", file};
    forkAndExec(fileArgv);
    forkAndExec(cmdArgv);
    return 0;
}
