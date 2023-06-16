//
// Created by 정승훈 on 2023/06/16.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "trim.h"

typedef struct swInfo {
    char swArgv[4][256];
} SwInfo;

void saveSwBlockInfo(const char *filename, struct swInfo *swInfo) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("파일 열기 실패");
    }

    int swNumber = 0;
    char line[256];

    // 파일에서 한 번에 256개의 문자열을 가지고 옴
    // 파일의 끝에
    while (fgets(line, sizeof(line), fp) != NULL) {
        int n = 0;
        char *token = strtok(line, ";");
        while (token != NULL && n < 4) {
            strcpy(swInfo[swNumber].swArgv[n], trim(token));
            n++;
            // 이전에 strtok 에서 ; 로 분리하고 남은 문자열을 계속 처리하기 위해
            // NULL 을 전달
            token = strtok(NULL, ";");
        }
        swNumber++;
    }
    fclose(fp);
}

struct swInfo *initializeSwBlock(SwInfo *swInfo){
    swInfo = malloc(sizeof(struct swInfo) * 10);
    if(swInfo == NULL){
        printf("메모리 할당 실패");
    }

    saveSwBlockInfo("SwInfo.txt", swInfo);

    return swInfo;
}

int main(){
    SwInfo *swInfo = NULL;
    swInfo = initializeSwBlock(swInfo);
}
