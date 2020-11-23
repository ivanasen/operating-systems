// Да се напише програма на C, която получава като параметри от команден ред две
// команди (без параметри) и име на файл в текущата директория. Ако файлът не
// съществува, го създава. Програмата изпълнява командите последователно, по
// реда на подаването им. Ако първата команда завърши успешно, програмата добавя
// нейното име към съдържанието на файла, подаден като команден параметър. Ако
// командата завърши неуспешно, програмата уведомява потребителя чрез подходящо
// съобщение.

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const int ERR = -1;

pid_t forkAndExec(char* cmd) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Couldn't fork!");
        exit(ERR);
    } else if (pid > 0) {
        return pid;
    } else {
        if (execlp(cmd, cmd, NULL) == -1) {
            printf("Error running command: %s", cmd);
            exit(ERR);
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Invalid arguments.\n");
        return ERR;
    }

    char* cmd1 = argv[1];
    char* cmd2 = argv[2];
    char* file = argv[3];

    int fd = open(file, O_WRONLY | O_CREAT, 0666);
    if (fd == -1) {
        fprintf(stderr, "Error opening file.\n");
        exit(ERR);
    }

    int pid1 = forkAndExec(cmd1);
    forkAndExec(cmd2);

    int status;
    waitpid(pid1, &status, 0);

    if (status == 0) {
        write(fd, cmd1, strlen(cmd1));
    } else {
        fprintf(stderr, "Command 1 didn't complete successfully.\n");
    }

    return 0;
}
