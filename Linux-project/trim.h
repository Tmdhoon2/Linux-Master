//
// Created by 정승훈 on 2023/06/16.
//

#ifndef C_TRIM_H
#define C_TRIM_H

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *rtrim(const char *s){
    while(isspace(*s) || !isprint(*s)) ++s;
    return strdup(s);
}

char *ltrim(const char *s){
    char *r = strdup(s);
    if(r != NULL){
        char *fr = r + strlen(s) - 1;
        while((isspace(*fr) || !isprint(*fr) || *fr == 0) && fr >= r) --fr;
        *++fr = 0;
    }
    return r;
}

char *trim(const char *s){
    char *r = rtrim(s);
    char *f = ltrim(r);
    free(r);
    return f;
}

#endif
