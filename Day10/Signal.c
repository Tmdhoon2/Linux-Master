#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void handler(int signum);
int flag = 5;

int main(){
    struct sigaction act;
    sigset_t set;

    sigfillset(&(act.sa_mask));
    act.sa_handler = handler;

    sigaction(SIGCHLD, &act, NULL);

    pid_t pid = fork();
    if(pid == 0){
        sleep(2);
        //kill(getpid(), 9);
        exit(10);
    }else{
        for(int t = 0; t<5; t++){
            sleep(1);
        }
    }
}

void handler(int signum){
    int pid;
    int status;
    while((pid=waitpid(-1, &status, WNOHANG)) > 0){
        printf("SIGCHLD, %d %d\n", pid, signum);
        if(WIFEXITED(status)){
            printf("exit %d\n", WEXITSTATUS(status));
        }
        if(WIFEXITED(status)){
            printf("signal %d\n", WTERMSIG(status));
        }
    }
}
