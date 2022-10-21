#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_SIZE 128

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "First agrument: PID\n");
		return 0;
	}
	if (argc < 2) {
		fprintf(stderr, "Not enough agruments!\n");
		return 0;
	}
	if (argc > 2) {
		fprintf(stderr, "Too many agruments!\n");
		return 0;
	}
	char *c;
	errno = 0;
	long PID = strtol(argv[1], &c, 10);
	if (*c != '\0' || errno != 0) {
		fprintf(stderr, "Provided PID must be number!\n");
		return 0;
	}
	if (PID < 0) {
		fprintf(stderr, "PID must be positive!\n");
		return 0;
	}
	char inbuf[4096];
	char outbuf[4096];
	int fd = open("/proc/Lab2/struct_info", O_RDWR);
	sprintf(inbuf, "%s", argv[1]);
	write(fd, inbuf, 17);
	lseek(fd, 0, SEEK_SET);
	read(fd, outbuf, 4096);
	puts(outbuf);
	return 0;
}