#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	
	sigset_t set;
	int result;

	sigemptyset(&set);
	result = sigismember(&set, SIGALRM);
	printf("SIGALRM is %s a memeber\n", result ? "" : "not");
	sigaddest(&set, SIGALRM);
	result = sigismemeber(&set, SIGALRM);
	printf("SIGALRM is %s a memeber\n", result ? "" : "not");
		

}
