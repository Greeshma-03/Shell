#include "headers.h"

void jobs(int argc, char **argv)
{
    NodePtr temp = head->next;
    
    if (argc > 2)
    {
        printf("bash: Too many arguments\n");
        return;
    }
    
    while (temp != NULL)
    {
        int job = temp->job, pid = temp->pid, row_num = 0;
        char status[MAX], command[MAX], path[MAX], row[MAX];
        strcpy(command, temp->name);
        FILE *fptr;

        sprintf(path, "/proc/%d/stat", pid);
     
        if ((fptr = fopen(path, "r")) != NULL)
        {
            if (fgets(row, sizeof(row), fptr) == NULL)
            {
                printf("bash: can't access %s such file or directory\n", path);
                return;
            }
        }
        else
        return;
        
        char *token = strtok(row, " \t");
        while (token != NULL && row_num < 3)
        {
            row_num++;
            if (row_num == 3)
            {
                if (strcmp(token, "S") == 0 || strcmp(token, "R")==0|| strcmp(token, "D")==0)
                {
                    strcpy(status, "Running");
                }
                else
                    strcpy(status, "Stopped");
            }
            token = strtok(NULL, " \t");
        }
        
        if (argc == 1 || (strcmp(status, "Running") == 0 && strcmp(argv[1], "-r") == 0) || (strcmp(status, "Stopped") == 0 && strcmp(argv[1], "-s") == 0))
            printf("[%d] %s %s [%d] \n", job, status, command, pid);

        temp = temp->next;
    }
}