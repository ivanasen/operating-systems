// Създавате файл aa със съдържание английската азбука.
// Отваряте файла само за четене.
// Четете от него с цикъл for и променлива меняща се  5 до 1 в буфер с размер 16 байта.
// Отпечатвате с printf прочетеното в буфера на всяка итерация.

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int fd = open("aa", O_WRONLY | O_CREAT, 0666);
    if (fd < 0) {
        puts("Error opening 'aa'file");
        exit(1);
    }

    int count = write(fd, "abcdefghijklmnopqrstuvwxyz", 26);
    if (count < 0) {
        puts("Error writing to 'aa' file");
        exit(1);
    }

    close(fd);

    fd = open("aa", O_RDONLY);
    char buff[16];

    for (int i = 5; i >= 1; i--) {
        int count = read(fd, buff, 16);
        if (count < 0) {
            puts("Error reading from file");
            exit(1);
        }

        printf("Read %d bytes\n", count);
        printf("%s\n", buff);
    }

    return 0;
}
