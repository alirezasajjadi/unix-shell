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

void init_shell();
int printdir();
int get_input(char *inp);
void parseSpace(char *str, char **parsed);
// void handeler(char *inp);
void execArgs(char **parsed);
void helpMenu();
int commandsHandler(char **inp);
void loop_run(char *inpstr, char **args);
void printFirstPart(char *fileName);
FILE* readFile(char* fileName);

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
        printf("\nDir: %s", cdir);
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
    buffer = readline("\n>>> ");
    // printf("\n>>> ");
    // gets(buffer);
    if (strlen(buffer) != 0)
    {
        // add_history(buffer);
        strcpy(inp, buffer);
        return 0;
    }
    else
    {
        return 1;
    }
}

void parseSpace(char *str, char **parsed)
{
    int i;

    for (i = 0; i < MAXLIST; i++)
    {
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}

// void handeler(char *inp)
// {
//     char *args[MAXLIST / 2 + 1];
//     char *token = strtok(inp, " ");
//     int i = 0;
//     while (token != NULL)
//     {
//         strcpy(args[i], token);
//         // args[i] = token;
//         //  printf("\n%s token",token);
//          printf("\n%s arg %d", args[i],i);

//         token = strtok(NULL, " ");
//         if(strlen(token)==0)
//             i--;
//         i++;
//     }
//     int x= 0;
//     printf("\nx = %d", x);

//     // x = commandsHandler(args);
//     printf("\nx = %d", x);
// }

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

int commandsHandler(char **args)
{
    int numCmd = 9;
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
    cmdList[8] = "help";
    for (i = 0; i < numCmd; i++)
    {
        if (strcmp(args[0], cmdList[i]) == 0)
        {
            switchArg = i + 1;
            break;
        }
    }

    switch (switchArg)
    {
    case 1:
        chdir(args[1]);
        return 1;
    case 2:
        printFirstPart(args[1]);
        return 1;
    case 9:
        helpMenu();
        return 1;
    default:
        break;
    }

    return 0;
}

FILE* readFile(char *fileName)
{
    FILE *ptr;
    char ch;
    ptr = fopen(fileName, "r");
    if (ptr == NULL)
    {
        printf("file can't be opened \n");
    }
    else
        return ptr;
}

void printFirstPart(char *fileName)
{
    char line[100];
    FILE *file = readFile(fileName);

    while (fgets(line, 100, file) != NULL)
    {
        printf("\n %s",strtok(line," "));
    }

    fclose(file);
}

void maxFrequent(char *fileName){
    int count,maxCount=0,i=0,j,k;
    char words[1000][1000], word[20]; // to remember
    char line[100];
    FILE *file = readFile(fileName);
    while(fgets(line,100,file)!=NULL){
            for(k=0; line[k]!='\0'; k++){
            //Here, i represents row and j represents column of two-dimensional array words 
            if(line[k] != ' ' && line[k] != '\n' && line[k] != ',' && line[k] != '.' ){
                words[i][j++] = tolower(line[k]);
            }
            else{
                words[i][j] = '\0';
                //Increment row count to store new word
                i++;
                //Set column count to 0
                j = 0;
            }
        }
    }
        int length = i;
    
    //Determine the most repeated word in a file
    for(i = 0; i < length; i++){
        count = 1;
        //Count each word in the file and store it in variable count
        for(j = i+1; j < length; j++){
            if(strcmp(words[i], words[j]) == 0 && (strcmp(words[i]," ") != 0)){
                count++;
            } 
        }
        //If maxCount is less than count then store value of count in maxCount 
        //and corresponding word to variable word
        if(count > maxCount){
            maxCount = count;
            strcpy(word, words[i]);
        }
    }
    printf("/nResult= %s",word);
    
}

void loop_run(char *inpstr, char **args)
{
    while (1)
    {
        printdir();
        if (get_input(inpstr))
            continue;
        // get_input(inpstr);
        parseSpace(inpstr, args);
        commandsHandler(args);
    }
}

int main()
{
    char inpstr[MAXCOM];
    char *args[MAXLIST / 2 + 1];
    init_shell();
    loop_run(inpstr, args);
    return 0;
}