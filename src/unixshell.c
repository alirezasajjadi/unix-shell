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
void printdir();
int get_input(char *inp);
void parseSpace(char *str, char **parsed);
// void handeler(char *inp);
void execArgs(char **parsed);
void helpMenu();
// int commandsHandler(char **inp);
void execArgs(char **args);
void loop_run(char *inpstr, char **args);
void changeDir(char *args);
void printFirstPart(char *fileName);
FILE *readFile(char *fileName);
void maxFrequent(char *fileName);
void delSpace(char *fileName);
void uncommented(char *fileName);
void numLine(char *file);
void firstTenLine(char *fileName);
void historyFile();

struct builtin
{
    char *name;
    void (*func)(char *fileName);
};

struct builtin builtin[] =
    {
        {"cd",changeDir},
        {"pfp", printFirstPart},
        {"mxfreq", maxFrequent},
        {"delspace", delSpace},
        {"shuncmt", uncommented},
        {"numline", numLine},
        {"firstten", firstTenLine},
};

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

void printdir()
{
    char cdir[1024];
    getcwd(cdir, sizeof(cdir));
    printf("\nDir: %s", cdir);
}

int get_input(char *inp)
{
    char *buffer;
    buffer = readline("\n>>>");
    // printf("\n>>> ");
    // gets(buffer);
    if (strstr(buffer, "exit()"))
    {
        // historyFile();
        exit(0);
    }
    if (strlen(buffer) != 0)
    {
        add_history(buffer);
        historyFile();
        strcpy(inp, buffer);
        return 0;
    }
    else
    {
        return 1;
    }
}

void historyFile()
{
    HISTORY_STATE *his = history_get_history_state();

    HIST_ENTRY **mylist = history_list();

    FILE *f = fopen("history.txt", "a");

    fprintf(f, "%s\n", mylist[his->length - 1]->line);

    fclose(f);
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

void execArgs(char **args)
{

    pid_t pid = fork();

    if (pid == -1)
    {
        printf("\nFailed forking child..");
        return;
    }
    else if (pid > 0)
    {
        // printf("\nparent wait");
        // waiting for child to terminate
        wait(NULL);
        return;
    }
    else if (pid == 0)
    {
        // printf("\nin child");

        // if (strcmp(args[0], "cd"))
        //     changeDir(args[1]);

        for (int i = 0; i < 7; i++)
        {
            if (strcmp(args[0], builtin[i].name) == 0)
            {
                builtin[i].func(args[1]);
                // printf("\nin child run builtin");
                exit(0);
                return;
            }
        }

        if (execvp(args[0], args) < 0)
        {
            fprintf(stderr, "\nCould not execute command..");
        }

        exit(0);
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
         "\n>5. mxfreq"
         "\n>6. delspace"
         "\n>7. shuncmt"
         "\n>8. numLine"
         "\n>9. firstTen"
         "\n>10. pipe");
    return;
}

void changeDir(char *args)
{
    if (args == NULL)
    {
        fprintf(stderr, "shell: cd: missing argument\n");
    }
    else
    {
        if (chdir(args) != 0)
        {
            perror("shell: cd");
        }
    }
}

FILE *readFile(char *fileName)
{
    FILE *ptr;
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
    char line[1000];
    FILE *file = readFile(fileName);
    char *token;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, " "))
        {
            token = strtok(line, " ");
            printf("%s\n", token);
        }
        else
            printf("%s", line);
    }

    fclose(file);
}

void maxFrequent(char *fileName)
{
    int count, maxCount = 0, i = 0, j, k;
    char words[1000][1000], word[100]; // to remember
    char line[1000];
    FILE *file = readFile(fileName);
    while (fgets(line, 1000, file) != NULL)
    {
        for (k = 0; line[k] != '\0'; k++)
        {
            // Here, i represents row and j represents column of two-dimensional array words
            if (line[k] != ' ' && line[k] != '\n' && line[k] != ',' && line[k] != '.')
            {
                words[i][j++] = tolower(line[k]);
            }
            else
            {
                words[i][j] = '\0';
                // Increment row count to store new word
                i++;
                // Set column count to 0
                j = 0;
            }
        }
    }
    int length = i;

    // Determine the most repeated word in a file
    for (i = 0; i < length; i++)
    {
        count = 1;
        // Count each word in the file and store it in variable count
        for (j = i + 1; j < length; j++)
        {
            if (strcmp(words[i], words[j]) == 0 && (strcmp(words[i], " ") != 0))
            {
                count++;
            }
        }
        // If maxCount is less than count then store value of count in maxCount
        // and corresponding word to variable word
        if (count > maxCount)
        {
            maxCount = count;
            strcpy(word, words[i]);
        }
    }
    printf("\nResult= %s", word);

    fclose(file);
}

void delSpace(char *fileName)
{
    char line[1000];
    FILE *file = readFile(fileName);

    while (fgets(line, 1000, file) != NULL)
    {
        char blank[1000];
        int j = 0;
        int sizeOfLine = sizeof(line) / sizeof(line[0]);
        // printf("size of line is : %d",sizeOfLine);
        for (int i = 0; i < sizeOfLine; i++)
        {
            if ((line[i] != ' ' && line[i] != '\t' && line[i] != '\n'))
            {
                blank[j] = line[i];
                j++;
            }
        }
        printf("\n%s", blank);
    }
    fclose(file);
}

void uncommented(char *fileName)
{
    char line[1000];
    FILE *file = readFile(fileName);
    char *token;
    while (fgets(line, 1000, file) != NULL)
    {
        // if(strstr(line, " ")){
        //     token = strtok(line, "#");
        //     printf("%s\n", token);
        // }
        // else
        //     printf("%s", line);
        char blank[1000];
        int j = 0, sizeOfLine = sizeof(line) / sizeof(line[0]);
        for (int i = 0; i < sizeOfLine; i++)
        {
            if (line[i] == '#')
                break;
            else
            {
                blank[j] = line[i];
                j++;
            }
        }
        printf("%s\n", blank);
    }
    fclose(file);
}

void numLine(char *fileName)
{
    FILE *file = readFile(fileName);
    int count = 0;
    char c;
    for (c = getc(file); c != EOF; c = getc(file))
        if (c == '\n')
            count = count + 1;
    fclose(file);
    printf("The file %s has %d lines\n ", fileName, count);
}

void firstTenLine(char *fileName)
{
    FILE *file = readFile(fileName);
    char line[1000];
    int numLine = 0;

    while (fgets(line, 1000, file) != NULL)
    {
        numLine++;
        if (numLine > 10)
        {
            break;
        }
        printf("%s", line);
    }
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
        // commandsHandler(args);
        execArgs(args);
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