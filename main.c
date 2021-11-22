#include "headers.h"

char home[MAX] = ""; //home to store the path from root to the directory where shell resides
int job_num = 0;//intially no jobs
int fg_child=-1;
char fg_name[MAX]="";

int main()
{
    char *buffer = NULL;
    int count = 0;

    size_t buffer_size = 0;
    getcwd(home, sizeof(home)); //getting the current working directory which is our home for shell

    signal(SIGINT, handler_c);
    signal(SIGTSTP, handler_z);
    signal(SIGCHLD, handler);      //parent recieves a signal and processed by the handler function

    fclose(fopen("process", "w")); //file for storing the running background processes
    Create_List();

    while (1)
    {
        user_prompt(); //set up the user_prompt
        //handling cntrl-D
        if(getline(&buffer, &buffer_size, stdin)==EOF)
        {
          printf("\n");
          return 0;
        }
        if (strcmp("\n", buffer) != 0)
            add_history(buffer);
        int num_commands = commands_num(buffer); //getting the total number of commands
        char **command = get_commands(buffer);   //seperating the ; seperated commands and storing

        for (int i = 0; i < num_commands; i++)
        {
            int original1 = dup(1), original2 = dup(0);
            if (!execute_command(command[i])) //checking if the command is implemented or not
                printf("%s: command not found\n", command[i]);
            free(command[i]);
            dup2(original1, STDOUT_FILENO);
            close(original1);
            dup2(original2, STDIN_FILENO);
            close(original2);
        }
        free(command);
    }
    free(buffer);

    return 0;
}