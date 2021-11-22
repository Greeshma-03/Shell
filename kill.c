#include "headers.h"

void job_kill(int argc,char** argv)
{
    if(argc!=3)
    {
        printf("sig: Incorrect number of arguments\n");
        return;
    }

    int job=atoi(argv[1]),signal=atoi(argv[2]);

    NodePtr temp=Get_Node_job(job);
    if(temp==NULL)
    {
        printf("Error: job not found\n");
        return;
    }
    pid_t pid=temp->pid;
    if(pid<=0 || kill(pid,signal)<0)
    {
      perror("Invalid command");
       return;
    }
}