#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFSIZE 10

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "invalid args\n");
		return 1;
	}

	char *f1 = argv[1];
	char *f2 = argv[2];

	int fd1 = open(f1, O_RDONLY);
	int fd2 = open(f2, O_WRONLY | O_CREAT, 0666);

	int stdout_fd = fileno(stdout);
	int stdin_fd = fileno(stdin);

	fflush(stdout);
	close(stdout_fd);

	close(stdin_fd);

	dup2(fd1, stdin_fd);
	dup2(fd2, stdout_fd);

	char buff[BUFFSIZE];
	int count = read(0, buff, BUFFSIZE);
	write(1, buff, count);

	return 0;
}
