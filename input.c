#include "headers.h"

bool execute_command(char *command_given) //command array has space seperated commands stored
{
    
    char* command=redirection(command_given);
    if (piped_command(command) == 1)
        return pipe_call(command);
    
    char *token;
    token = strtok(command, " \t");
    char **flag;
    flag = malloc(20 * (sizeof(char *))); //allocating memory for the pointers that store each command line argument
    int num_flags = 0;

    while (token != NULL)
    {
        if (num_flags >= 20)
        {
            printf("bash: too many command line arguments\n");
            return false;
        }
        flag[num_flags] = (char *)malloc(sizeof(char) * MAX);
        strcpy(flag[num_flags], token); //copying each argument into array
        num_flags++;
        token = strtok(NULL, " ");
    }

    flag[num_flags] = NULL;

    if (num_flags == 0)
        return true;
    else if (strcmp(flag[0], "exit") == 0)
        exit(0);
    else if (strcmp(flag[0], "cd") == 0)
        cd(num_flags, flag);
    else if (strcmp(flag[0], "pwd") == 0)
        pwd();
    else if (strcmp(flag[0], "echo") == 0)
        echo(num_flags, flag);
    else if (strcmp(flag[0], "ls") == 0)
        ls(num_flags, flag);
    else if (strcmp(flag[0], "repeat") == 0)
        repeat(num_flags, flag);
    else if (strcmp(flag[0], "history") == 0)
        history(num_flags, flag);
    else if (strcmp(flag[0], "pinfo") == 0)
        pinfo(num_flags, flag);
    else if (strcmp(flag[0], "jobs") == 0)
        jobs(num_flags, flag);
    else if (strcmp(flag[0], "sig") == 0)
        job_kill(num_flags, flag);
    else if (strcmp(flag[0], "fg") == 0)
        fg(num_flags, flag);
    else if (strcmp(flag[0], "bg") == 0)
        bg(num_flags, flag); 
    else if (strcmp(flag[0], "replay") == 0)
        replay(num_flags, flag);            
    else if (strcmp(flag[0], "") == 0)
        return false;
    else
        child_parent(num_flags, flag); //rest of the commands implemented using execvp()

    free(token);
    for (int i = 0; i < num_flags; i++)
        free(flag[i]);
    free(flag);
    

    return true;
}

char **get_commands(char *buffer) //returns a double pointer that points to an array of commands
{
    int num = 1;
    for (ll i = 0; i < strlen(buffer); i++)
    {
        if (buffer[i] == ';')
            num++;
        else if (buffer[i] == '\t' || buffer[i] == '\n')
            buffer[i] = ' ';
    }

    char **command = malloc(num * sizeof(char *));
    char *token;
    token = strtok(buffer, ";");
    int i = 0;

    while (token != NULL)
    {
        command[i] = (char *)malloc(sizeof(char) * 1024);
        strcpy(command[i], token);
        i++;
        token = strtok(NULL, ";");
    }

    free(token);
    return command;
}

int commands_num(char *buffer) //counting the number of commands sepreated by ; given
{
    int num = 1;
    for (ll i = 0; i < strlen(buffer); i++)
        if (buffer[i] == ';')
            num++;
    return num;
}
