#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#define MAXCOM 1000 
#define MAXLIST 100 

int get_input(char *inp){
    char *buffer;
    buffer = readline("\n>>");
    printf("\n>>"); //
    if(strlen(buffer) != 0){
        // add_history(buffer);
        int i;
        for (i = 0; i < strlen(buffer) && buffer[i]; i++) {
             inp[i] = buffer[i];
        }
        inp[i] = '\0';
    }
    return 0;
}


int main(){
    char inpstr[MAXCOM];

    while (1)
    {
        get_input(inpstr);
        break;
    }
    return 0;
}