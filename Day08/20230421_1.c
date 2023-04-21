#include <stdio.h>
#include <unistd.h>

#define num 2

int main() {
    pid_t pid[num];

    for(int i = 0; i<num; i++){
        if((pid[i] = fork()) == -1){
            printf("%d. error\n", i);
        }else if(pid[i] != 0){
            printf("%d. parent process\n", i);
        }else{
            printf("%d. child process\n", i);
        }
    }
    return 0;
}
