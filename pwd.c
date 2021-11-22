#include "headers.h"

char dir[MAX]="";

void pwd()
{
    if(getcwd(dir, MAX)!=NULL)
    printf("%s\n",dir);
    else 
    printf("Error in getting the path of current directory\n");

    strcpy(dir,"");
}
