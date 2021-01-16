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
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "invalid args\n");
        exit(1);
    }

    char *cmd1 = argv[1];
    char *cmd2 = argv[2];
    char *fileName = argv[3];

    int fd = open(fileName, O_WRONLY | O_CREAT, 0666);

    pid_t pid;
    if (!(pid = fork())) {
        execlp(cmd1, cmd1, 0);
    } else if (pid < 0) {
        perror("fork");
        exit(1);
    }

    int status;
    wait(&status);

    if (!status) {
        write(fd, cmd1, strlen(cmd1));
    }

    if (!(pid = fork())) {
        execlp(cmd2, cmd2, 0);
    } else if (pid < 0) {
        perror("fork");
        exit(1);
    }

    wait(&status);

    if (!status) {
        printf("cmd2 \"%s\" executed successfully", cmd2);
    }
}