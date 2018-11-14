#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "util.h"

//helper functions
/*
 * gets the input string from standard input
 */
char* getStdIn(){
    char buf[MAX_CHARS];
    char *str;
    int i = read(0, buf, MAX_CHARS);
    str = malloc((size_t)i);
    char *pstr = str;
    for(int j = 0; j < i-1; j++){
        *(pstr++) = buf[j];
    }
    *pstr = 0;
    return str;
}
/*
 * gets the length of a null terminated string
 */
int strlength(char *str){
    int i = 0;
    for(char *pstr = str; *pstr; pstr++)
        i++;
    return i;
}

char * mystrcat(char *str, char *str2){
    int len1 = strlength(str);
    int len2 = strlength(str2);
    printf("len1 is %u and 2 is %u", len1, len2);
    char *cat = malloc((size_t)len1+len2+1);
    char *pcat = cat;
    for(int i = 0; i < len1; i++){
        *pcat = *(str+i);
        pcat++;
    }
    for(int i = 0; i < len2; i++){
        *pcat = *(str2+i);
        pcat++;
    }
    *pcat = 0;
    return cat;
}
/*
 * check if the str is equal to str2
 */
short streq(char *str, char const *str2){
    short ind = 0;
    while(str[ind]==str2[ind]) {
        if(str[ind]=='\0'||str2[ind]=='\0')
            break;
        ind++;
    }
    if(str[ind]=='\0' && str2[ind]=='\0')
        return 1;
    else
        return 0;
}
/*
 * function to copy a string, returns a new copy
 */
char* substrCopy(char *start, int len){
    int i;
    char *copy = malloc(len+1);
    for(i = 0; i < len; i++){
        *(copy + i) = *(start + i);
    }
    *(copy + i) = 0;
    return copy;
}