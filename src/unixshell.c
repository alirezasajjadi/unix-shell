#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAXCOM 1000
#define MAXLIST 100

#define clear() printf("\033[H\033[J")

void init_shell()
{
    clear();
    printf("\n\n\n\n******************"
           "************************");
    printf("\n\n\n\t****WELCOME TO MY UNIX SHELL****");
    printf("\n\n\n\n*******************"
           "***********************");
    char *username = getenv("USER");
    printf("\n\n\nUSER is: @%s", username);
    printf("\n");
    sleep(1);
    clear();
}

int printdir()
{
    char cdir[1024];
    if (getcwd(cdir, sizeof(cdir)) != NULL)
    {
        printf("\nDir", cdir);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }
    return 0;
}

int get_input(char *inp)
{
    char *buffer;
    buffer = readline("\n>>");
    printf("\n>>"); //
    if (strlen(buffer) != 0)
    {
        // add_history(buffer);
        int i;
        for (i = 0; i < strlen(buffer) && buffer[i]; i++)
        {
            inp[i] = buffer[i];
        }
        inp[i] = '\0';
    }
    return 0;
}

void handeler(char *inp)
{
    char(*args)[MAXLIST / 2 + 1];
    char *token = strtok(inp, " ");
    int i = 0;
    while (token != NULL)
    {
        strcpy(args[i], token);
        // args[i] = token;
        //  printf("\n%s token",token);
        //  printf("\n%s arg %d", args[i],i);

        token = strtok(NULL, " ");
        // if(strlen(token)==0)
        // i--;
        i++;
    }
}

void execArgs(char **parsed)
{

    pid_t pid = fork();

    if (pid == -1)
    {
        printf("\nFailed forking child..");
        return;
    }
    else if (pid == 0)
    {
        if (execvp(parsed[0], parsed) < 0)
        {
            printf("\nCould not execute command..");
        }
        else
        {
            commandsHandler
        }
        exit(0);
    }
    else
    {
        // waiting for child to terminate
        wait(NULL);
        return;
    }
}

void helpMenu()
{
    puts("\n---->This is shell help<----"
         "\n ->List of Commands supported:<-"
         "\n>1. pwd"
         "\n>2. cd"
         "\n>3. ls"
         "\n>4. pfp"
         "\n>5. mxstr"
         "\n>6. delspace"
         "\n>7. shuncmt"
         "\n>8. numLine"
         "\n>9. firstTen"
         "\n>10. pipe");
    return;
}

int commandsHandler(char **inp)
{
    int numCmd = 8;
    int i;
    int switchArg = 0;
    char *cmdList[numCmd];
    char *username;
    cmdList[0] = "cd";
    cmdList[1] = "pfp";
    cmdList[2] = "mxstr";
    cmdList[3] = "delspace";
    cmdList[4] = "shuncmt";
    cmdList[5] = "numLine";
    cmdList[6] = "firstTen";
    cmdList[7] = "pipe";
    for (i = 0; i < numCmd; i++)
    {
        if (strcmp(inp[0], cmdList[i]) == 0)
        {
            switcArg = i + 1;
            break;
        }
    }
    // Forking a child
    pid_t pid = fork();

    if (pid == -1)
    {
        printf("\nFailed forking child..");
        return;
    }
    else if (pid == 0)
    {
        switch (switchArg){
        case 1:
            chdir(inp[1]);
            break;
        case 2:
        printf("%s", inp[1]);
            printFirstPart(inp[1]);
            break;
        default:
            break;
        }
        exit(0);
    }
    else{
        // waiting for child to terminate
        wait(NULL);
    }
}

void readFile()
{
    FILE *ptr;
    char ch;
    ptr = fopen("test.txt", "r");
    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }
}

void printFirstPart(char **inp){

}

int main()
{
    char inpstr[MAXCOM];

    while (1)
    {
        printdir();

        get_input(inpstr);
        handeler(inpstr);

        break;
    }
    return 0;
}