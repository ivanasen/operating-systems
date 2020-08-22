// Да се напише програма на C, която реализира командата cat (без параметри)

#include <unistd.h>

const int BUFF_SIZE = 100;
const int STDIN = 0;
const int STDOUT = 1;

int main() {
    char *buffer[BUFF_SIZE];
    int count;
    while ((count = read(STDIN, buffer, BUFF_SIZE)) > 0) {
        write(STDOUT, buffer, count);
    }
    return 0;
}
