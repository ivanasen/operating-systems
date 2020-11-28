#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void print10(char *str) {
	for (int i = 0; i < 10; i++) {
		puts(str);
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) { fprintf(stderr, "invalid args\n"); return 1; }

	char *filename = argv[1];
	int fd = open(filename, O_WRONLY | O_CREAT, 0666);

	print10("EXAMPLE");

	int stdout_fd = fileno(stdout);
	int stdout_copy = dup(stdout_fd);
	fflush(stdout);
	close(stdout_fd);

	int fd_copy = dup(fd);
	close(fd);

	for (int i = 1; i <= 10; i++) {
		printf("%d ", i);
	}
	puts("");

	close(fd_copy);

	dup(stdout_copy);
	close(stdout_copy);

	print10("HELLO");

	return 0;
}
