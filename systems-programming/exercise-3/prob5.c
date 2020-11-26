// Да се състави програма на Си, която получава два параметъра,
// първият от които е име на съществуващ текстов файл,
// в който дължината на редовете не надвишава 60.
// Програмата извежда на стандартния изход онези от редове от текстовия файл,
// чийто последен символ е $. Създава файл с име втория параметър и в него
// записва - всеки път на нов ред – първата по ред последователност, състояща се
// само от цифри, от всеки от останалите редове от първия файл. Извежда броя на
// редовете от новосформирания файл.

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXLEN 61

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid arguments");
        return 1;
    }

    char *readFile = argv[1];
    char *writeFile = argv[2];

    int readFd = open(readFile, O_RDONLY);
    if (readFd <= 0) {
        fprintf(stderr, "Error opening first file\n");
        return 1;
    }

    int writeFd = open(writeFile, O_WRONLY | O_CREAT, 0666);
    if (writeFd <= 0) {
        fprintf(stderr, "Error opening second file\n");
        return 1;
    }

    char line[MAXLEN];
    memset(line, 0, MAXLEN);

    char c;
    int readCount = 0;
    int column = 0;

    int state = 0;

    char nums[MAXLEN];
    memset(nums, 0, MAXLEN);
    int numsLen = 0;

    while ((readCount = read(readFd, &c, 1)) > 0) {
        if (c == '\n') {
            if (column == 0) {
                continue;
            }
            
            if (line[column - 1] == '$') {
                write(1, line, column);
                puts("");
            } else {
                nums[numsLen++] = '\n';
                write(writeFd, nums, numsLen);
            }

            memset(line, 0, MAXLEN);
            c = 0;
            memset(nums, 0, MAXLEN);
            numsLen = 0;
            column = 0;
            state = 0;
        } else {
            line[column++] = c;

            switch (state) {
                case 0:
                    if (c >= '0' && c <= '9') {
                        state = 1;
                        nums[numsLen++] = c;
                    }
                    break;
                case 1:
                    if (c >= '0' && c <= '9') {
                        nums[numsLen++] = c;
                    } else {
                        state = 2;
                    }
                    break;
                case 2:
                    break;
            }
        }
    }

    if (readCount < 0) {
        fprintf(stderr, "Error reading from first file\n");
        return 1;
    }

    if (close(readFd) < 0) {
        fprintf(stderr, "Error closing first file\n");
        return 1;
    }

    if (close(writeFd) < 0) {
        fprintf(stderr, "Erro closing second file\n");
        return 1;
    }

    return 0;
}
