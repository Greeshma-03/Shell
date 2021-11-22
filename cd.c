#include "headers.h"

char prev[MAX] = "", add[MAX];

void cd( int argc,char** argv)
{
    strcpy(add, "");
        
    if (argc > 2)
    {
        printf("bash: cd: too many arguments\n");
        return;
    }

    else if (argc == 1)
    {
        int check=chdir(home);
        if(check!=0)
        printf("bash: cd: %s: No such file or directory\n",home);
        return;
    }

    if (argv[1][0] == '~')
    {
        strcpy(add, home);
        strcat(add,&argv[1][1]);
    }
    else if (strcmp(argv[1], "--") == 0)
        strcpy(add, "..");
    else if (strcmp(argv[1], "-") == 0)
    {
        strcpy(add, prev);
        printf("%s\n", add);
    }
    else if (strcmp(argv[1], ".") == 0)
        strcpy(add, ".");
    else
        strcpy(add, argv[1]);

    getcwd(prev, sizeof(prev));

    int check = chdir(add);
    if (check != 0)
        printf("bash: cd: %s: No such file or directory\n", argv[1]);
}