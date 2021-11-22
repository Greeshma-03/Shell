#include "headers.h"

void replay(int argc, char **argv)
{
    if (argc <= 6)
    {
        printf("replay: less number of arguments\n");
        return;
    }

    if (strcmp(argv[0], "replay") || strcmp(argv[1], "-command") || strcmp(argv[argc - 4], "-interval") || strcmp(argv[argc - 2], "-period"))
    {
        printf("replay: incorrect arguments\n");
        return;
    }

    int interval = atoi(argv[argc - 3]);
    int period = atoi(argv[argc - 1]);
    char *command = (char *)malloc(sizeof(char) * MAX);

    for (int i = 0; i < period / interval; i++)
    {
        strcpy(command, "");
        for (int i = 2; i < argc - 4; i++)
        {
            strcat(command, argv[i]);
            strcat(command, " ");
        }
        sleep(interval);
        if (!execute_command(command))
        {
            printf("replay: invalid command entered\n");
            return;
        }
    }
    free(command);

    sleep(period % interval);

    return;
}