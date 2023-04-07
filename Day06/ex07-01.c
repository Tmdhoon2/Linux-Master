#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	pid_t pld;
	int i = 0;

	i++;

	printf("before calling fork(%d)\n", i);

	pld = fork();

	if(pld == 0){
		printf("child process(%d)\n", ++i);
	}

	else if(pld > 0){
		printf("parent process(%d)\n", --i);
	}

	else printf("fall to fork\n");

	return 0;
}

