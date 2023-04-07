#include <unistd.h>
#include <stdio.h>

int main(){
	char *arg[] = {"ls", "-|", (char *)0};
	printf("before executing ls -|\n");
	execv("/bin/ls", arg);
	printf("after executing ls -|\n"); 
}
