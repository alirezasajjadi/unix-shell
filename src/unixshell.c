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