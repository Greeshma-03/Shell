#ifndef __COMMANDS_H
#define __COMMANDS_H
#include "headers.h"

//function prototypes from all .c files

//bg.c
void bg(int argc,char** argv);


//cd.c
void cd(int argc,char** argv);


//echo.c
void echo(int argc,char** argv);


//fg.c
void fg(int argc,char** argv);


//fgbg.c
void child_parent(int argc, char **argv);


//history.c
void add_history(char *command);
void history(int argc, char **argv);


//input.c
bool execute_command(char* command);
char** get_commands(char * buffer);
int commands_num(char * buffer);


//jobs.c
void jobs(int argc,char** argv);


//kill.c
void job_kill(int argc,char** argv);


//ls.c
void ls(int argc,char** argv);
void ls_l_a(char dir[]);
void ls_each_file(char str[], char file_name[]);


//pinfo.c
void pinfo(int argc, char **argv);


//piping.c
int piped_command(char command[]);
void pipe_execution(int in, int out, char *command);
bool pipe_call(char command[]);


//prompt.c
void user_prompt();


//pwd.c
void pwd();


//redirection.c
char* redirection(char* command);


//repeat.c
void repeat(int argc,char** argv);


//replay.c
void replay(int argc,char** argv);


//signal.c
void handler(int sent);
void handler_z(int sent);
void handler_c(int sent);


#endif