// Да се напише програма на C, която получава като параметър в командния ред
// на команда (изпълним файл) и списък с параметри за нея. Поражда процес дете
// и сменя образа му с командата. В родителя изчаква наследника да приключи
// и извежда номера му и кода на завършване.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const int ERR = 1;

void parent() {
    int res;
    int pid = wait(&res);
    printf("res: %d, pid: %d\n", res, pid);
}

void child(char** argv) {
    if (execvp(argv[0], argv) == -1) {
        printf("Error running command: %s", argv[0]);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Invalid arguments!\n");
        return ERR;
    }

    char** cmdArgv = argv + 1;

    int pid = fork();
    if (pid == -1) {
        perror("Couldn't fork!");
        exit(ERR);
    } else if (pid > 0) {
        parent();
    } else {
        child(cmdArgv);
    }

    return 0;
}