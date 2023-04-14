#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	
	pid_t pid1, pid2;
	int status;

	int x, y = 0;
	scanf("%d %d", &x, &y);
	
	int p, c;

	pid1 = pid2 = -1;

	if((pid1 = fork()) > 0){
		wait(&status);
		for(int i = 1; i<=y; i++){
			x *= x;		
		}
		
		p = x;
		
		
	}else if(pid == 0){
		for(int i = x; i<=y; i++){
			
		}
	}

	
	
	exit(1);
	
	return 0;
}
