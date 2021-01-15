// Напишете програма на Си, която изпълнява команда извеждаща редовете,
// в които се среща символния низ int в подадения като параметър файл.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Invalid args!\n");
        exit(1);
    }

    execlp("grep", "grep", "int", argv[1], 0);
}