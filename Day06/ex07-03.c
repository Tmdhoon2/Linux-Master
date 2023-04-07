#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	printf("before \n");
	execl("/bin/ls", "ls", "-1", (char *)0);
	printf("after \n");
}
