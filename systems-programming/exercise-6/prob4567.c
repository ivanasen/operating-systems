// 4. Да се напише програма на С, която получава като параметри две имена на
// файлове. Отваря първия файл за писане (ако не съществува, го създава, в
// противен случай го занулява), създава 2 процеса. Родителят пише hello1, а
// детето – hello2 във първия файл.
//
// 5. В зад 4 пренасочвате изхода на детето във втория файл.
// В общи действия на двата процеса се записват hello3 на стандартния изход и
// hello4 във втория файл:
//   ◦ с wait в родителя
//   ◦ без wait в родителя
//
// 6. В зад 5 в края на действията на детето възстановявате стандартния му
// изход.
//
// 7. В зад 6 – да се пробва с exit() – в единия или двата процеса; с или без
// wait()
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

    char* fileName1 = argv[1];
    char* fileName2 = argv[2];

    int fd1 = open(fileName1, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    int fd2 = open(fileName2, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    write(fd1, HELLO_1, strlen(HELLO_1));

    if (!fork()) {
        dup2(fd2, STDOUT_FILENO);

        write(fd1, HELLO_2, strlen(HELLO_2));

        printf("%s\n", HELLO_3);
        write(fd2, HELLO_4, strlen(HELLO_4));

        exit(0);
    }

    wait(NULL);

    printf("%s\n", HELLO_3);
    write(fd2, HELLO_4, strlen(HELLO_4));

    exit(0);
}