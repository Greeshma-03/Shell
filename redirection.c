#include "headers.h"

char *redirection(char *command)
{
    if (!(strstr(command, "<") || strstr(command, ">") || strstr(command, ">>")))
        return command;
    
    char *token;
    token = strtok(command, " ");
    char flag[20][MAX] = {"\0"};
    int num_flags = 0;
    while (token != NULL)
    {
        if (num_flags >= 20)
        {
            printf("bash: too many command line arguments\n");
            return " ";
        }
        strcpy(flag[num_flags], token); //copying each argument into array
        num_flags++;
        token = strtok(NULL, " ");
    }

    int left = -1, right = num_flags, num_lefts = 0, num_rights = 0, append = 0, pipe = num_flags,pipe_last=-1;

    //left indicates the last input redirection
    //right indicates the last ouput redirection
    //num_lefts=number of input redirections
    //num_rigths-number of output redirections
    //append=0/1 accordingly append or rewrite it on overall
    //pipe locations are used to check the order of redirection
    //pipe=store the first pipen position
    //pipe_last=store the last pipe position

    for (int i = 0; i < num_flags; i++)
    {
        if (strcmp(flag[i], "<") == 0)
        {
            left = i;
            num_lefts++;
        }
        else if (strcmp(flag[i], ">") == 0)
        {
            num_rights++;
            right = i;
        }
        else if (strcmp(flag[i], ">>") == 0)
        {
            num_rights++;
            right = i;
            append = 1;
        }
        else if (strcmp(flag[i], "|") == 0)
        {
            if (pipe == num_flags) //We will store only first pipe
                pipe = i;
            pipe_last=i;
        }
    }
 
    if (num_lefts > 1 || num_rights > 1) //assumption of atmost single input or output redirection
    {
        printf("Too many redirections\n");
        return "";
    }
    

    if(!(left<pipe && pipe_last<right && left<right))
    //assumption of order of redirection as input followed by pipe and then output redirection
    {
        printf("%s: wrong order of redirection\n",flag[0]);
        return "";
    }

    int last = (right < pipe) ? right : pipe;
    //the input file we need to redirect stdin

    if (left>0)//handling cases like cat < a1.txt a2.txt as cat < a2.txt
    {
        for (int i = left; i < last - 1; i++)
            strcpy(flag[i], " ");
    }

    if (right < num_flags - 1)//redirection to output file
    {
        int fd;
        if (append)
            fd = open(flag[right + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd = open(flag[right + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (fd < 0) 
            printf("Error in opening file\n");
        
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("Unable to duplicate file descriptor.");
            return "";
        }
        close(fd);
    }

    else if(right==num_flags-1 || left==0)
    //handling cases where < or > are present at corners then that case is not valid
    return "";
        
    char *final_cmd = malloc(sizeof(char) * MAX);
    strcpy(final_cmd, "");

    for (int i = 0; i < right; i++)//we just need till we reach output redirection as we already did dup2 as part of output redirection
    {
        strcat(final_cmd, flag[i]);
        strcat(final_cmd, " ");
    }

    free(token);
    return final_cmd;
}