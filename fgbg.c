#include "headers.h"

void child_parent(int argc, char **argv)
{
    int back = 0;
    if (strcmp(argv[argc - 1], "&") == 0)
        back = 1;
    int shellpid = getpid();
    int fork_return = fork();

    if (fork_return == 0) //child process
    {
        setpgid(0, 0); //Creating a new process group

        if (back)
            argv[argc - 1] = NULL;
        execvp(argv[0], argv);
        perror("Error");
        exit(1);
    }

    else //parent process
    {
        int status;
        setpgid(fork_return, 0); //making the PGID same as child process

        if (!back) //foreground process
        {
            signal(SIGTTIN, SIG_IGN); //ignoring the default action
            signal(SIGTTOU, SIG_IGN); //else it would stop the process

            strcpy(fg_name, "");
            for (int i = 0; i < argc; i++)
            {
                strcat(fg_name, argv[i]);
                strcat(fg_name, " ");
            }
            tcsetpgrp(STDIN_FILENO, fork_return); //changing the foreground process group to child else terminal process don't work

            fg_child = fork_return;

            waitpid(fork_return, &status, WUNTRACED); //waiting for the change in state of child
            
            //background process exited coz of cntrl-Z
            if (WIFSTOPPED(status))
            {
                printf("\n");
                job_num++;
                Insert_Node(fg_name, fork_return);
                kill(fork_return,SIGSTOP);
            }
            
            fg_child = -1;

            tcsetpgrp(STDIN_FILENO, getpgid(getpid())); //changing the forground process group to parent
            
            //follow the default action asusual
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
        }

        else
        {
            char name[MAX] = "";
            for (int i = 0; i < argc - 1; i++)
            {
                strcat(name, argv[i]);
                strcat(name, " ");
            }
            job_num++;
            Insert_Node(name, fork_return);
            printf("%d\n", fork_return);

            setpgid(getpid(), 0);
            tcsetpgrp(STDIN_FILENO, getpgid(getpid())); //setting the parent back as terminal foreground process group with fd as input
        }
    }
    return;
}