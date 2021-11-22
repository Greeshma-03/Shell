#include "headers.h"

char rows[20][MAX] = {""};
char data[20][MAX] = {""};

void history(int argc, char **argv)
{
    int max;

    if (argc == 1)
        max = 10;
    else if (argc == 2)
        max = atoi(argv[1]);
    else if (argc > 2)
    {
        printf("bash: history: too many arguments\n");
        return;
    }

    for (int i = max - 1; i >= 0; i--)
    {
        if (i > 19)
            continue;
        if (strcmp(data[i], "") == 0)
            return;
        printf("%s", data[i]);
    }
    return;
}

void add_history(char *command)
{
    char path[MAX] = "";
    strcat(path, home);
    strcat(path, "/history");
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Error in opening file\n");
        return;
    }

    strcpy(data[0], command);

    int num_lines = 1;
    while (fgets(rows[num_lines - 1], MAX, fp))
    {
        if (strcmp(rows[0], command) == 0)
            return;
        if (num_lines >= 20)
            break;
        strcpy(data[num_lines], rows[num_lines - 1]);
        num_lines++;
    }
    fclose(fp);

    fclose(fopen(path, "w"));
    fp = fopen(path, "a");

    if (fp == NULL)
    {
        printf("Error in opening file\n");
        return;
    }

    for (int i = 0; i < num_lines; i++)
        fputs(data[i], fp);
    fclose(fp);
}