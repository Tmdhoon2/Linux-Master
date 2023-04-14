#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	pid_t pid1, pid2;
	int status;

	pid1 = pid2 = -1;

	pid1 = fork();
	if(pid1 > 0){
		pid2 = fork();
	}
	if(pid1 > 0 && pid2 > 0){
		waitpid(pid2, &status, 0);
		printf("parent: child2 - exit(%d)\n", status);
		waitpid(pid1, &status, 0);
		printf("parent: child1 - exit(%d)\n", status);
	}
	else if(pid1 == 0 && pid2 == 0){
		sleep(1);
		exit(1);
	}
	else if(pid1 > 0 && pid2 == 0){
		sleep(2);
		exit(2);
	}
	else {
		printf("fall to fork\n");
	}

	return 0;
}
