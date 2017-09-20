//
// Created by ulimartinez on 9/12/17.
//

#include "mytoc.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include "util.h"

//function prototypes
short streq(char *, char const *);

char getDelimiter(char *optarg);

char* getPath(char **envp);

short checkComm(char *path);

int main(int argc, char **argv, char **envp){
    int c;
    char delim = ' ';//default delimiter is a space
    while((c = getopt(argc, argv, "d:")) != -1){
        switch(c) {
            case 'd'://if commandline option d is found get the delimiter
                delim = getDelimiter(optarg);
                break;
            default:
                break;
        }
    }
    while(1){//inf loop to keep on reading strings to tokenize
        write(1, "$", 2);
        char *str = getStdIn();//get input from user
        if(streq(str, "exit"))//check for exit string
            return 0;
        char **tokens = mytoc(str, delim);
        if(tokens){
            //check if command exists
            if(checkComm(tokens[0]))
                printf("Command %s exists\n", tokens[0]);
            else{
                char *path = getPath(envp);
                char **bins = mytoc(path, ':');
                int found = 0;
                for(int i = 0; bins[i] != (char *)0; i++){
                    char *comm = strcat(strcat(bins[i], "/"), tokens[0]);
                    if(checkComm(comm)) {
                        printf("Command %s exists\n", comm);
                        found = 1;
                        break;
                    }
                }
                if(!found)
                    printf("%s: command not found\n", tokens[0]);
            }
        }
    }
}

short checkComm(char *path){
    struct stat sb;
    return(((stat(path, &sb) == 0) && (sb.st_mode & S_IXOTH))?(short)1:(short)0);
}
char getDelimiter(char *optarg) {
    return *optarg;
}
/*
 * check if the input string is "exit"
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

char* getPath(char **envp){
    for(int i = 0; envp[i] != (char *)0; i++){
        char **toks = mytoc(envp[i], '=');
        if(streq(toks[0], "PATH"));
        return toks[1];
    }
    return NULL;
}
