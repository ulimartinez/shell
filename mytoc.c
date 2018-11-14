#include "mytoc.h"
#include "util.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


char ** mytoc(char *str, char delim){
    if(!*str)//return null when there is no string
        return NULL;
    int numToc = 1;
    char *pStr = str;
    if(*pStr == delim)//when the string starts with a delimiter, there is one less token
        numToc = 0;
    for(; *pStr; pStr++){//count all the tokens
        if(*pStr == delim){
            while(*(pStr + 1) == delim)//ignore consecutive delimiters
                pStr++;
            numToc++;
        }
    }
    if(*(pStr-1) == delim)//if the string ends with the delimiter then there is one less token
        numToc--;
    char **tokens = malloc(sizeof(char*) * (numToc+1));//allocate the memory for the tokens pointers
    int numChars = 0;
    char *tokStart = str;
    while(*(tokStart) == delim){//skip any delimiters at the beginning
        tokStart++;
    }
    int curTokInd = 0;
    for(pStr = tokStart; *pStr; pStr++){
        if(*pStr != delim){
            numChars++;
        }
        else{
            while(*(pStr+1) == delim){//skip consecutive delimiters
                pStr++;
            }
            char *cstr = substrCopy(tokStart, numChars);//get the pointer to the copy of the token
            *(tokens + curTokInd) = cstr;
            numChars = 0;
            curTokInd++;
            tokStart = pStr+1;
        }
    }
    if(*(pStr-1) != delim)
        *(tokens + curTokInd++) = substrCopy(tokStart, numChars);//store the last token if there is one
    *(tokens + curTokInd) = (char *)0;//null terminate tokens vector
    return tokens;
}
int veclen(char **vec){
    size_t i = 0;
    for(char **pvec = vec; *pvec != (char *)0; pvec++)
        i++;
    return i;
}
void removeLast(char **vec){
    int len = veclen(vec);
    free(*(vec + len));
    free(*(vec + len-1));
    *(vec+len-1) = malloc(1);
    *(vec+len-1) = 0;
}