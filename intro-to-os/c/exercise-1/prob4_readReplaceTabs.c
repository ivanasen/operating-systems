// Чете последователност от символи от стандартния вход.
// Записва ги във файл, чието име е подадено като първи параметър.
// Замества символите за табулация с '>>>' и резултата извежда на стандартния
// изход за грешки

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const int ARGS_COUNT = 2;
const int BUFFER_SIZE = 100;
const int STDIN = 0;
const int STDERR = 2;
const int OK = 0;
const int ERROR = 1;

// If all characters are tabs and is of max size
const int OUT_SIZE = BUFFER_SIZE * 3;

int writeToOutput(const char* fileName, char* inputBuffer, int inputSize) {
    int output = open(fileName, O_WRONLY | O_CREAT, 0666);
    if (write(output, inputBuffer, inputSize) != inputSize) {
        return ERROR;
    }
    return OK;
}

void addSwapChars(char* s, int sSize, int* pos) {
    int end = (*pos + 3) < sSize ? *pos + 3 : sSize;
    while (*pos < end) {
        s[(*pos)++] = '>';
    }
}

int swapTabs(const char* src, int srcSize, char* dst, int dstSize) {
    int srcI = 0;
    int dstI = 0;

    while (srcI < srcSize && dstI < dstSize) {
        char c = src[srcI++];

        if (c == '\t') {
            addSwapChars(dst, dstSize, &dstI);
        } else {
            dst[dstI++] = c;
        }
    }

    return dstI;
}

int main(int argc, char** argv) {
    if (argc != ARGS_COUNT) {
        perror("Invalid arguements");
        return ERROR;
    }

    char* outputName = argv[1];

    char inputBuffer[BUFFER_SIZE];
    int readCount = read(STDIN, inputBuffer, BUFFER_SIZE);

    if (readCount == -1) {
        perror("Error reading from stdin");
        return ERROR;
    }

    int writeResult = writeToOutput(outputName, inputBuffer, readCount);
    if (writeResult != OK) {
        perror("Error writing to output file");
        return ERROR;
    }

    char swapped[OUT_SIZE];
    int swappedSize = swapTabs(inputBuffer, readCount, swapped, OUT_SIZE);

    write(STDERR, swapped, swappedSize);

    return 0;
}