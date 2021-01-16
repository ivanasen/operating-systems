#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define DEFAULT_PROMPT "> "
#define BUFFER_LENGTH 1000
#define SHELL_ERROR 1
#define SHELL_OK 0
#define SHELL_EXIT 2

typedef int (*handler_t)(char*);

int builtInCommandHandler(char* cmd) {}

int execFileCommandHandler(char* file) {}

int execPathCommandHandler(char* cmd) {}

struct Shell {
    char* prompt;
    char* buffer;
    int bufferSize;
    int in;
    int out;

    char shouldShowPrompt;
};

struct Shell newShell(char* prompt, char* buffer, int bufferSize, int in,
                      int out) {
    struct Shell s = {prompt, buffer, bufferSize, in, out, 1};
    return s;
}

int execute(struct Shell* s) {
    if (s->shouldShowPrompt) {
        write(s->out, s->prompt, strlen(s->prompt));
    }

    int readCount = read(s->in, s->buffer, s->bufferSize);

    if (readCount == 0) {
        s->shouldShowPrompt = 0;
        return SHELL_OK;
    }

    if (readCount < 0) {
        perror("read");
        return SHELL_ERROR;
    }

    s->buffer[readCount - 1] = '\0';
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return SHELL_ERROR;
    } else if (pid == 0) {
        execlp(s->buffer, s->buffer, 0);
    }

    int status;
    wait(&status);
    if (!WIFEXITED(status) || status) {
        write(s->out, "*", 1);
    }
    s->shouldShowPrompt = 1;
    return SHELL_OK;
}

int start(struct Shell* s) {
    int status;
    while (1) {
        if ((status = execute(s)) != SHELL_OK) {
            return status;
        }
    }
}

int ignoreExit(int status) { return status == SHELL_EXIT ? SHELL_OK : status; }

int main() {
    char buffer[BUFFER_LENGTH];
    struct Shell shell = newShell(DEFAULT_PROMPT, buffer, BUFFER_LENGTH,
                                  STDIN_FILENO, STDOUT_FILENO);
    int status = start(&shell);
    status = ignoreExit(status);
    return status;
}
