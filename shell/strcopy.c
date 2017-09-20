#include "strcopy.h"
#include <stdlib.h>
/*
 * function to copy a substring starting at start and having len characters in length
 * */
char* substrCopy(char *start, int len){
    int i;
    char *copy = (char *)malloc(len+1);
    for(i = 0; i < len; i++){
        *(copy + i) = *(start + i);
    }
    *(copy + i) = 0;
    return copy;
}