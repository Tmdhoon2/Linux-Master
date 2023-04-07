#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void file1(char *);

int main(int argc, char **argv){
	if(argc!=2) exit(0);

	file1(argv[1]);
}

void file1(char *filename){
	int fd = open(filename, O_RDWR|O_CREAT, 0644);
	char a[1024] = "01234567890123";
	write(fd, a, 10);
	close(fd);

	fd = open(filename, O_RDWR, 0644);
	char b[1024] = {};
	read(fd, b, 4);
	close(fd);
	printf("%s\n", b);
}


