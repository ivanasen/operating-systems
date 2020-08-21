// Записва се във файл 25 байта. Чете от него по 10 байта и отпечатва какво
// връща read.

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const char *OUTPUT_NAME = "readWrite.out";
const int ERROR = 1;
const int READ_SIZE = 10;

void readFile(int fileDescriptor) {
    int BUFFER_SIZE = READ_SIZE + 1;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    int charCount = 0;

    while ((charCount = read(fileDescriptor, buffer, READ_SIZE)) > 0) {
        buffer[charCount] = '\0';
        printf("Read %d characters: %s\n", charCount, buffer);
    }
}

int main() {
    char *msg = "123456789ABCDEFGHIJKLMNOP";

    int outputFile = open(OUTPUT_NAME, O_RDWR | O_CREAT, 0666);
    int writeCount = write(outputFile, msg, strlen(msg));

    if (writeCount == -1) {
        perror("Failed to write to output file");
        return ERROR;
    }

    lseek(outputFile, 0, SEEK_SET);
    readFile(outputFile);

    return 0;
}
