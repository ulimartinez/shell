#include "mytoc.h"
#include "strcopy.h"
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
    char **tokens = (char **)malloc(sizeof(char*) * (numToc+1));//allocate the memory for the tokens pointers
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
    *(tokens + curTokInd++) = substrCopy(tokStart, numChars);//store the last token
    *(tokens + curTokInd) = (char *)0;//null terminate tokens vector
    return tokens;
}
void printTokens(char ** tokens, char delim){
    for(char **ptokens = tokens; *ptokens; ptokens++){
        if(*(*ptokens) != delim)
            write(1, *ptokens, (size_t)strlen(*ptokens));
        free(*ptokens);
        write(1, "\n", 1);
    }
    free(tokens);
}