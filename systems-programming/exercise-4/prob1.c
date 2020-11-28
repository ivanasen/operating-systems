#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "invalid args\n");
		return 1;
	}

	char *file = argv[1];

	int fd = open(file, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "error opening file\n");
		return 1;
	}

	int fdDup = dup(fd);
	if (fdDup < 0) {
		fprintf(stderr, "error duplicating fd\n");
		return 1;
	}

	char buff[3];
	int readSize = 3;

	int count = read(fd, buff, readSize);
	if (count < 0) {
		fprintf(stderr, "error reading from file\n");
		return 1;
	}
	write(1, buff, count);
	puts("");

	count = read(fdDup, buff, readSize);
	if (count < 0) {
		fprintf(stderr, "error reading from file\n");
		return 1;
	}
	write(1, buff, count);
	puts("");

	close(fd);

	count = read(fdDup, buff, readSize);
	if (count < 0) {
		fprintf(stderr, "error reading from file\n");
		return 1;
	}
	write(1, buff, count);
	puts("");

	return 0;
}
