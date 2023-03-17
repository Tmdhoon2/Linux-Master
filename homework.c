#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(void){
	
	FILE *file;
	
	char temp[1024] = "ddong ddong ddong";

	int fd = open("temp0.txt", O_RDWR);

	close(fd); 
}
