#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 512

int main(){
    char msg[SIZE];
    int fileDes[2];

    pid_t pid;

    if(pipe(fileDes) == -1){
        printf("fail to call pipe()\n");
        exit(1);
    }

    if((pid = fork()) == -1){
        printf("fail to call fork()\n");
        exit(1);
    }else if(pid>0){
        strcpy(msg, "apple is red.\n");
        write(fileDes[1], msg, SIZE);
        printf("[parent] %s\n", msg);
    }else{
        sleep(1);
        read(fileDes[0], msg, SIZE);
        printf("[child] %s\n", msg);
    }
}
