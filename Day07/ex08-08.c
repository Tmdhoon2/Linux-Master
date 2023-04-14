#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	time_t result = time(NULL);
	char buffer[1024] = {};
	strcpy(buffer, asctime(localtime(&result)));
	
	printf("%s", buffer);

	return 0;
}
