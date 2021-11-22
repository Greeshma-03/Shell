#include "headers.h"

void bg(int argc,char** argv)
{
    if(argc>2)
    {
        printf("bg: too many arguments\n");
        return;
    }
    else if(argc!=2)
    {
        printf("bg: less arguments\n");
        return;
    }
    
    int job=atoi(argv[1]);
    NodePtr temp=Get_Node_job(job);
    if(temp==NULL)
    {
        printf("Error: job not found\n");
        return;
    }
    pid_t pid=temp->pid;
    if (pid <= 0) //sigcont signal resumes the process where it stopped
    {
        perror("Invalid command");
        return;
    }
    
    if (kill(pid, SIGCONT) < 0)
    {
        perror("Can't send signal");
    }

}