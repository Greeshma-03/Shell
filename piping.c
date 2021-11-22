#include "headers.h"

int last = 0;
int piped_command(char command[]) //checking if there is a pipe seperated by spaces in the untokenized command
{
    int l = strlen(command);
    for (int i = 0; i < l; i++)
    {
        if (command[i] == '|')
        {
            if (i > 0 && command[i - 1] == ' ' && i < l - 1 && command[i + 1] == ' ')
                return 1;
        }
    }
    return 0;
}

void pipe_execution(int in, int out, char *command)
{   
    int pid = fork();
    if (pid == 0)//child
    {
        if (in != 0)//redirecting input
        {
            dup2(in, 0);
            close(in);
        }

        if (out != 1 && last == 0)//redirecting output
        {
            dup2(out, 1);
            close(out);
        }
        
        //tokenizing piped_command wrt space
        char *token;
        token = strtok(command, " ");
        char *flag[20];
        int num_flags = 0;

        while (token != NULL)
        {
            if (num_flags >= 20)
            {
                printf("bash: too many command line arguments\n");
                return;
            }
            flag[num_flags] = (char *)malloc(sizeof(char) * MAX);
            strcpy(flag[num_flags],token); //copying each argument into array
            num_flags++;
            token = strtok(NULL, " ");
        }

        flag[num_flags] = NULL;

        if (strcmp(flag[0], "pinfo") == 0)
            pinfo(num_flags, flag);
        else if (strcmp(flag[0], "jobs") == 0)
            jobs(num_flags, flag);
        else
            execvp(flag[0], flag); //if execvp() fails then next lines of code will be execeuted
        perror("");
        for (int i = 0; i < num_flags; i++)
            free(flag[i]);
        exit(0);
    }

    else //parent
    {
        int status;
        waitpid(pid, &status, 0);
        return;
    }
}

bool pipe_call(char command[])
{
    //tokenizing pipes and storing pipe seperated commands in piped_commands
    last = 0;
    char piped_commands[20][MAX];   
    char *token;
    token = strtok(command, "|");
    int i = 0;

    while (token != NULL)
    {    
        strcpy(piped_commands[i], token);
        i++;
        token = strtok(NULL, "|");
    }
    
    int flides[2], in = 0;

    //executing each piped command with i/o redirection
    for (int j = 0; j < i; j++)
    {
        if (j == i - 1)
            last = 1;

        if (pipe(flides) < 0)
        {
            perror("Error in creating pipe");
            return false;
        }
        pipe_execution(in, flides[1], piped_commands[j]);//sending the file descriptors for input and output of files
        in = flides[0];
        close(flides[1]);
    }

    free(token);
    return true;
}

