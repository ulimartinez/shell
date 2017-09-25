//
// Created by ulimartinez on 9/12/17.
//
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include "mytoc.h"
#include "util.h"

//function prototypes

char* getPath(char **envp);

short checkComm(char *path);

char* getPropmpt();

int main(int argc, char **argv, char **envp){
    int pid;
    int waitVal, waitStatus;
    while(1){//inf loop to keep on prompting
        char *command = NULL;
        char *prompt = getPropmpt();
        write(STDOUT_FILENO, prompt, strlen(prompt));
        char *str = getStdIn();//get input from user
        if(streq(str, "exit"))//check for exit string
            return 0;
        char **tokens = mytoc(str, SPACE_DELIM);//tokenize the input from the prompt
        if(tokens){
            int found = 0;
            //check if command exists
            if(checkComm(tokens[0])) {
                printf("Command %s exists\n", tokens[0]);
                command = tokens[0];//command contains the full path to an executable
                found = 1;
            }
            else{
                char *path = getPath(envp);
                char **bins = mytoc(path, COLON_DELIM);//tokenize the $PATH env variable, each token is a directory with binary files
                for(int i = 0; bins[i] != (char *)0; i++){//look for the command in all the path directories
                    char *comm = strcat(strcat(bins[i], "/"), tokens[0]);
                    if(checkComm(comm)) {//once found store the full path
                        found = 1;
                        command = comm;
                        break;
                    }
                }
            }
            if(!found)
                printf("%s: command not found\n", tokens[0]);
            else{//if the command was found create a child process to run the command
                pid = fork();
                if(pid == 0){
                    execve(command, tokens, envp);
                }
                else{
                    waitVal = waitpid(pid, &waitStatus, 0);//wait until child terminates
                    if(waitVal == pid && waitStatus != 0){//if the terminated child notify the exit code
                        printf("Program terminated with exit code %d\n", waitStatus);
                    }
                }
            }
        }
    }
}
/*
 * uses stat to check that a file exists and also if the file is an executable file
 */
short checkComm(char *path){
    struct stat sb;
    return(((stat(path, &sb) == 0) && (sb.st_mode & S_IXOTH))?(short)1:(short)0);
}
/*
 * Gets the path variable from the environment variables
 */
char* getPath(char **envp){
    for(int i = 0; envp[i] != (char *)0; i++){
        char **toks = mytoc(envp[i], EQ_DELIM);
        if(streq(toks[0], "PATH"))
            return toks[1];
    }
    return NULL;
}
char* getPropmpt(){
    char *buf = (char *)malloc(MAX_CHARS);
    char *ptr = getcwd(buf, MAX_CHARS);
    char *prompt = strcat(ptr, "$");
    free(buf);
    return prompt;
}
