#include "headers.h"

void pinfo(int argc, char **argv)
{
    int pid;
    if (argc > 2)
    {
        printf("pinfo: too many arguments\n");
        return;
    }

    // (argc) ? pid=getpid():pid=atoi(argv[1]);

    if (argc == 1)
        pid = getpid();
    else
        pid = atoi(argv[1]);

    if (pid == 0)
    {
        printf("Invalid PID\n");
        return;
    }

    FILE *fptr;
    char path[MAX], row[MAX];
    int row_num = 0;
    char pgrpid[50], tgid[50];
    char status[3] = ""; //'+' for a foreground process
    char memory[50] = "";
    sprintf(path, "/proc/%d/stat", pid);

    if ((fptr = fopen(path, "r")) != NULL)
    {
        if (fgets(row, sizeof(row), fptr) == NULL)
        {
            printf("bash: can't access %s such file or directory\n", path);
            return;
        }
    }

    char* token=strtok(row," ");
    while(token!=NULL && row_num<23)
    {
        row_num++;
        if(row_num==3)
        strcpy(status,token);
        else if(row_num==5)
        strcpy(pgrpid,token);
        else if(row_num==8)
        strcpy(tgid,token);
        else if(row_num==23)
        strcpy(memory,token);
        token=strtok(NULL," ");
    }

    if(strcmp(pgrpid,tgid)==0)
    strcat(status,"+");
    
    char linker[MAX];
    char ex_path[MAX];
    sprintf(linker, "/proc/%d/exe", pid);
    int len = readlink(linker, ex_path,MAX);

    printf("pid -- %d\n", pid);
    printf("Process Status -- {%s}\n", status);
    printf("memory -- %s {Virtual Memory}\n", memory);

    if (len == -1)
    {
        printf("Error in opening %s\n", linker);
        return;
    }
    ex_path[len]='\0';    
    printf("Executable Path -- %s\n", ex_path);
    return;
}