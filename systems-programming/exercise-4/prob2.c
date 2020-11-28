#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	// Second way: coment this
	fflush(stdout);
	close(fileno(stdout));

	int fd = open("f1", O_WRONLY | O_CREAT, 0666);
	if (fd < 0) {
		perror("error opening f1");
		return 1;
	}

	// Second way: uncomment this
	// fflush(stdout);
	// close(fileno(stdout))
	// int fd_new = dup(fd);
	// if (fd_new < 0) {
	// 	perror("error duplicating fd_new");
	// }
	//
	// close(fd);

	for (int i = 0; i < 10; i++) {
		printf("EXAMPLE\n");
	}

	return 0;
}
