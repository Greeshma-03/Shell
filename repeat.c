#include "headers.h"
char command[MAX];

void repeat(int argc, char **argv)
{
    for (int i = 0; i < strlen(argv[1]); i++)
        if (!('0' <= argv[1][i] && argv[1][i] <= '9'))
        {
            printf("Enter the correct number of times to repeat\n");
            return;
        }

    int repeat = atoi(argv[1]);

    for (int j = 0; j < repeat; j++)
    {
        strcpy(command, "");
        for (int i = 2; i < argc; i++)
        {
            strcat(command, argv[i]);
            strcat(command, " ");
        }
        if (!execute_command(command))
        {
            printf("%s: command not found\n", command);
            return;
        }
    }
    return;
}


