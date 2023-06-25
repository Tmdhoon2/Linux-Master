//
// Created by 정승훈 on 2023/06/16.
//

#ifndef C_TRIM_H
#define C_TRIM_H

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void trim_str(char *str) {
    // start 포인터를 str 의 시작위치로 설정
    char *start = str;
    // end 포인터를 str 문자열 길이 -1 ( == 마지막 위치 ) 로 설정
    char *end = str + (strlen(str) - 1);

    // start 가 공백인 경우 start 포인터 앞으로 이동 (== 앞쪽 공백 제거)
    while (isspace(*start)) start++;
    // end 가 공백인 경우 end 포인터 뒤로 이동 (== 뒤쪽 공백 제거)
    while (isspace(*end)) end--;

    // 문자열 앞으로 당김
    memmove(str, start, end - start + 1);
    // 문자열 끝 표시
    str[end - start + 1] = '\0';
}

#endif
