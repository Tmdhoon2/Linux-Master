#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	char *envlist[] = {"APPLE=0", "BANANA=1", (char *)0 };

	execle("ex08-13", "ex08-13", (char *)0
}
