#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(){
	int fdin, fdout;
	ssize_t nread;
	char buffer[1024] = "My name is Seunghoon Jung";
	
	fdin = open("temp1.txt", O_RDONLY);
	fdout = open("temp2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	while((nread = read(fdin, buffer, 1024)) > 0) {
		if(write(fdout, buffer, nread) < nread){
			close(fdin);
			close(fdout);	
		
		}
	}

	close(fdin);
	close(fdout);
		
}
