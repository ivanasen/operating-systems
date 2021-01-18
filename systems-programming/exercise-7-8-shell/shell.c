#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define DEFAULT_PROMPT "> "
#define CMD_DELIMITER " "
#define BUFFER_LENGTH 1000
#define MAX_TOKEN_COUNT 500
#define SHELL_ERROR 1
#define SHELL_OK 0
#define SHELL_EXIT 2

struct Shell {
    char* prompt;
    char* buffer;
    int bufferSize;
    int in;
    int out;

    char shouldShowPrompt;
    char* tokens[MAX_TOKEN_COUNT + 1];
};

struct Shell newShell(char* prompt, char* buffer, int bufferSize, int in,
                      int out) {
    struct Shell s = {prompt, buffer, bufferSize, in, out, 1};
    return s;
}

int parseTokens(struct Shell* s) {
    int currentToken = 0;
    char* ptr = strtok(s->buffer, CMD_DELIMITER);

    while (ptr != NULL && currentToken < MAX_TOKEN_COUNT) {
        s->tokens[currentToken] = ptr;
        currentToken++;
        ptr = strtok(NULL, CMD_DELIMITER);
    }

    if (ptr != NULL && currentToken == MAX_TOKEN_COUNT) {
        return SHELL_ERROR;
    }

    s->tokens[currentToken] = NULL;
    return SHELL_OK;
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

    // remove the new line
    s->buffer[readCount - 1] = '\0';

    int err;
    if ((err = parseTokens(s)) != SHELL_OK) {
        return err;
    }

    int i = 0;
    while (s->tokens[i] != NULL) {
        printf("%s\n", s->tokens[i++]);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return SHELL_ERROR;
    } else if (pid == 0) {
        execvp(s->tokens[0], s->tokens);
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
