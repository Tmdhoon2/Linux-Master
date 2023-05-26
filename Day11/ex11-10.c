#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MSGSIZE 16

int child(int []);

void onerror(char *msg) {
    printf("%s", msg);
    exit(1);
}

int main() {
    int p1[2], p2[2];
    char msg[MSGSIZE];
    int i;
    pid_t pid1, pid2;
    fd_set initset, newset;

    pid1 = pid2 = 0;

    if (pipe(p1) == -1) {
        onerror("fail to call pipe() #1\n");
    }
    if (pipe(p2) == -1) {
        onerror("fail to call pipe() #2\n");
    }

    if ((pid1 = fork()) == -1) {
        onerror("fail to call fork() #1\n");
    }
    if (pid1 > 0) {
        if ((pid2 = fork()) == -1) {
            onerror("fail to fork() #2\n");
        }
    }

    if (pid1 > 0 && pid2 > 0) {
        printf("parent: %d\n", getpid());
        close(p1[1]);
        close(p1[2]);

        FD_ZERO(&initset);
        FD_SET(p1[0], &initset);
        FD_SET(p2[0], &initset);

        newset = initset;
        while (select(p2[0] + 1, &newset, NULL, NULL, NULL) > 0) {
            if (FD_ISSET(p1[0], &newset)) {
                if (read(p1[0], msg, MSGSIZE) > 0) {
                    printf("[parent] %s from child1\n", msg);
                }
            }
            if (FD_ISSET(p2[0], &newset)) {
                if (read(p2[0], msg, MSGSIZE) > 0) {
                    printf("[parent] %s from child2\n", msg);
                }
            }
            newset = initset;
        }
    } else if (pid1 == 0 && pid2 == 0) {
        printf("child1: %d\n", getppid());
        close(p1[0]);
        close(p2[0]);
        close(p2[1]);

        for (i = 0; i < 3; i++) {
            sleep((i+1) % 4);
            printf("child1: send message %d\n", i);
            write(p1[1], "i 'm child1", MSGSIZE);
        }

        printf("child1: bye!\n");
        exit(0);
    } else if(pid1 > 0 && pid2 == 0){
        printf("child2: %d\n", getpid());
        close(p1[0]);
        close(p1[1]);
        close(p2[0]);

        for(i = 0; i < 3; i++){
            sleep((i+3) % 4);
            printf("child2: send message %d\n", i);
            write(p2[1], "i 'm child2", MSGSIZE);
        }
        printf("child2: bye!\n");
        exit(0);
    }
}
