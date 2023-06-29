


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include "trim.h"

#define MAX_SW_BLOCKS 10
#define MAX_PARAMETERS 3

typedef struct {
    pid_t pid;
    time_t lastRestartTime;
    char name[20];
    int restartCount;
    char parameters[MAX_PARAMETERS][20];
    char reason[30];
} SwBlock;

SwBlock blocks[MAX_SW_BLOCKS];
int swBlockCount;

void runSwBlock(SwBlock *block) {
    printf("%s 초기화 중...\n", block->name);
    pid_t pid = fork();

    if (pid < 0) {
        printf("%s 초기화 오류\n", block->name);
        exit(1);
    } else if (pid == 0) {
        printf("%s 실행 중..\n", block->name);

        sleep(3);
        exit(0);
    } else {
        // 부모 프로세스
        block->pid = pid;
    }
}

void printLog(FILE *log, char name[30], int restartCount, char restartTime[30], char reason[30]) {

    fprintf(log, "----------------------------------------\n\n");
    fprintf(log, "블록 이름: %s\n", name);
    fprintf(log, "재 초기화 횟수: %d\n", restartCount);
    fprintf(log, "최종 재 초기화 시간: %s\n", restartTime);
    fprintf(log, "사유: %s\n\n", reason);
    fprintf(log, "----------------------------------------\n\n");

    printf("\n----------------------------------------\n\n");
    printf("블록 이름: %s\n", name);
    printf("재 초기화 횟수: %d\n", restartCount);
    printf("최종 재 초기화 시간: %s\n", restartTime);
    printf("사유: %s\n\n", reason);
    printf("----------------------------------------\n");
}

void signalHandler(int signum) {
    int status;
    pid_t pid;

    // WNOHANG : 만약 기다리는 프로세스가 종료되지 않아, 프로세스 회수가 불가능한
    // 상황이라면 차단되지 않고 반환값으로 0을 받음
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        SwBlock *block = NULL;
        for (int i = 0; i < swBlockCount; i++) {
            if (blocks[i].pid == pid) {
                block = &blocks[i];
                break;
            }
        }

        if (block) {
            block->restartCount++;
            block->lastRestartTime = time(NULL);
            strcpy(block->reason, strsignal(signum));

            FILE *log = fopen("log.txt", "a");
            if (log == NULL) {
                printf("로그 파일 열기 실패");
                exit(1);
            }

            printLog(log, block->name, block->restartCount, ctime(&block->lastRestartTime), block->reason);
            fclose(log);

            // 재기동
            runSwBlock(block);
        } else {
            printf("자식 프로세스 %d 종료됨.\n", pid);
        }
    }
}

void initSigaction() {
    struct sigaction sa;
    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);

    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if (sigaction(SIGCHLD, &sa, 0) == -1) {
        printf("sigaction");
        exit(1);
    }
}

int readSwBlocks(FILE *file) {
    char buf[256];
    int index = 0;

    while (index < MAX_SW_BLOCKS && fgets(buf, sizeof(buf), file)) {
        char *token = strtok(buf, ";");
        trim_str(token);
        strcpy(blocks[index].name, token);

        for (int paramIndex = 0; paramIndex < MAX_PARAMETERS; paramIndex++) {
            token = strtok(NULL, ";");
            if (token) {
                trim_str(token);
                strcpy(blocks[index].parameters[paramIndex], token);
            }
        }

        index++;
    }

    return index;
}

int main() {
    srand(time(NULL));
    FILE *logFile = fopen("log.txt", "w");
    FILE *fileList = fopen("FileList.txt", "r");

    if (logFile == NULL) {
        printf("로그 파일 열기 실패!");
        exit(1);
    }

    if (fileList == NULL) {
        printf("S/W 블록 열기 실패");
    }

    swBlockCount = readSwBlocks(fileList);
    fclose(logFile);
    fclose(fileList);

    initSigaction();
    for (int i = 0; i < swBlockCount; i++) {
        runSwBlock(&blocks[i]);
    }

    while (1) {
        sleep(1);
    }
}