#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void file1(char *);
void file2(char *);

int main(int argc, char **argv){
	if(argc!=3) exit(0);

	file1(argv[1]);
	file2(argv[2]);
}

void file1(char *filename){
	int fd = open(filename, O_RDWR, 0644);
	// int fd = open(filename, O_RDWR);
	// int fd = open(filename, O_RDONLY | O_CREAT);
	// int fd = open(filenmae, O_WRONLY | O_CREATE, 0644);
	// int fd = open(filename, O_WRONLY | 
	if(fd < 0){
		printf("%s(%d)\n", strerror(errno), errno);
	}
}

void file2(char *filename){
	int fd = open(filename, O_RDWR|O_CREAT, 0644);
	char a[1024] = "01234567890123";
	printf("%d\n", (int)write(fd, a, 10));
    printf("%s(%d)\n", strerror(errno), errno);
    close(fd);
}
