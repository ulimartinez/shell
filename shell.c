//
// Created by ulimartinez on 9/12/17.
//

#include "mytoc.h"
#include <unistd.h>
#include "util.h"

//function prototypes
short exit(char *);

char getDelimiter(char *optarg);

int main(int argc, char **argv){
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
        if(exit(str))//check for exit string
            return 0;
        char **tokens = mytoc(str, delim);
        if(tokens){
            //do the forking and stuff here
            int pc = fork();
            if(pc < 0){
                //error
            }
            else if(pc == 0)
                wait();
        }
    }
}

char getDelimiter(char *optarg) {
    return *optarg;
}
/*
 * check if the input string is "exit"
 */
short exit(char *str){
    char *exit = "exit";
    short ind = 0;
    while(str[ind]==exit[ind]) {
        if(str[ind]=='\0'||exit[ind]=='\0')
            break;
        ind++;
    }
    if(str[ind]=='\0' && exit[ind]=='\0')
        return 1;
    else
        return 0;
}
