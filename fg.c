#include "headers.h"

void fg(int argc, char **argv)
{
    if (argc > 2)
    {
        printf("fg: too many arguments\n");
        return;
    }
    else if (argc != 2)
    {
        printf("fg: less arguments\n");
        return;
    }

    int job = atoi(argv[1]);
    NodePtr temp = Get_Node_job(job);
    if (temp == NULL)
    {
        printf("Error: job not found\n");
        return;
    }
    pid_t pid = temp->pid;
    if (pid <= 0) 
    {
        perror("Invalid command");
        return;
    }
    signal(SIGTTIN, SIG_IGN); //ignoring the default behaviour
    signal(SIGTTOU, SIG_IGN); //else it would stop the process

    tcsetpgrp(STDIN_FILENO, pid); //changing the forground process group to child else terminal process don't work

    if (kill(pid, SIGCONT) < 0)//sigcont signal resumes the process where it stopped
    {
        perror("Can't send signal");
    }
    int status;
    waitpid(pid, &status, WUNTRACED);//WUNTRACED used 

    if (WIFSTOPPED(status))//cntrl-z
    {
        kill(pid, SIGSTOP);//send pause signal
    }
    else
    Delete_Node(pid);

    tcsetpgrp(STDIN_FILENO, getpgid(getpid())); //changing the forground process group to parent

    signal(SIGTTIN, SIG_DFL);//do the default action
    signal(SIGTTOU, SIG_DFL);//do the default action
}