#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 256

void printcwd(){
	char buffer[BUF_SIZE];

	if(getcwd(buffer, BUF_SIZE) == NULL){
		printf("path not exist");
	}

	printf("%s\n", buffer);
}

int main(){
	printcwd();
	chdir("/usewfr/include");
	printcwd();
	chdir("..");
	printcwd();
}

