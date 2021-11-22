# MY_SHELL

## Overview

My_Shell is a user-defined interactive shell written in C that works similar to the original shell and it can execeute many of the linux shell commands.The semicolon seperated commands,input output redirections,piping,signal handling are also supported.The shell can also create and manage new processes.Builtin commands like cd,ls,echo,pwd,history are implemented and it also supports running of background and foreground processes.


### Running the shell

* cd to the directory where the shell resides.
* run `make` command followed by `./a.out`
* To quit from the shell enter command `exit`.


### Features

#### Shell Commands
* Basic functionality of `cd` command is implemented and flags including ".","..","-","~" are also implemented.
* Command `echo` is implemented for simple commands without involving multi line strings and environmental variables.
* Command `pwd` that displays the path from root directory is also implemented.
* Command `ls` with two flags -a -l are implemented and cases of multiple flags possible with -a,-l and directories,regular files have are also supported.

* Command `repeat` is implemented which executes a given instruction the specified number of times.
* `history` command is also implemented that displays last 10 commands by default and can also display the given latest number of commands with maximum limit of 20.
* Command `jobs` is implemented similar to the original shell and the flags -s,-r are also supported.


#### User-Defined Commands

* Command `pinfo` is supported to print the information of process with given pid in command or takes the pid of the running shell process.
* Command `sig` that sends a given signal to the particular job given as input through command line arguments.
* Command `replay` is implemented which executes a particular command in fixed time interval for a certain period.


#### Signal Handling

* CTRL-C is handled that interrupts any running foreground job by sending signal SIGINT and no effect on the shell if there is no foreground process running.
* CTRL-D is handled that logs out the user from shell and without effecting original terminal.
* CTRL-Z is handled that pushes any currently running foreground job into the background, and change its state from running to stopped. This should have no effect on the shell if there is no foreground process running.
* The name and PID is printed when a background process is exited using a handler function for SIGCHLD.


### Code Files

* *bg.c:* A function is included that changes the state of a stopped background job to running if the given job number exists.

* *cd.c:* As the user changes the directories,functions are implemented for going to the appropraite paths.

* *commands.h:* This header file contains the function prototypes of all functions present in c files.

* *echo.c:* echo command is implemented by printing all the command line arguments after string echo and the empty,tab spaces when passed in command line are tokenized for simplicity of the echo command.

* *pwd.c:* Command pwd is implemented with inbuit cwd function in C.

* *fgbg.c:* For the other commands not implemented in the shell, they are executed by the child process execvp() by the method of forking.

* *fg.c:* A function is implemented that brings the running or stopped background job corresponding to ​job number​ to the foreground and changes its state to ​running and the shell throws an error if no job with the given job number exists.

* *Headers.h:* This header file contains all the required standard libraries for functions implemented and also has the declarations for extern variables.

* *history.c:* The last 20 commands entered by the user are stored in a file named "history" and each time a input is read it is added to the list using the functions implemented and the specified number of latest commands are displayed.

* *input.c:* Input tokenzing and executing functions are implemented here like getting list of commands seperated by ';' and tokenzing them with empty spaces and tabs and sending arguments to the functions that call corresponding commands.

* *jobs.c:* This conatins the implementation of jobs command that prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with their job number,process ID and their state, which can either be running​ or ​stopped​ and the flags implemented for the command are -r and -s.

* *kill.c*: This contains the command sig that sends the given signal to the mentioned job and it is implemented using system call kill.
* *linked.c:* This contains the linked list implementation for storing the pid,name and job of a background process and functions for inserting,deleting,finding node are implemented here.

* *Linked.h:* This contains the struct declaration for linked list and function prototypes of linked.c

* *ls.c:* The directories passed as command line arguments for ls are processed individually and each file in the directory is passed to respective functions that prints the long list information or just files depending on the flags passed.

* *main.c:* The main infinite loop for displaying the prompt to user is implemented and function calls to get and execution commands are present here.

* *pinfo.c:* Function to get the information of a process with given PID or running shell program is implemented by accessing some files and links present in root directory that contains the respective information of the process and executable path.

* *piping.c:* This includes a function that checks if the command involves piping and other function that redirects the output of the command on the left as input to the command on the right.The shell supports any numver of pipes.

* *prompt.c:* Prompt Box is implemented here which gets the user name and system name and displays them along with path relative to home or absolute path from root depending on the directory the user is in.

* *redirection.c:* This includes a function that checks if there is any input or output redirection and accordingly the output of command will be redirected to corresponding file and this supports <,>,>> symbols in command that specify redirection.

* *repeat.c:* A loop is written in the function that executes the given instruction specified number of times.

* *replay.c:* Replay command is implemented which executes a particular command in fixed time interval for a certain period.

* *signal.c:* Whenever a background process exits the signal sent to parent is processed by the signal handler function implemented by storing the information in "process" file.


### Assumptions

Violating any of the below assumptions can lead to Wrong output or exiting My_Shell...

-  The maximum number of command line arguments that can be given in the prompt are 20 with a maximum of total number of characters as 1024.

- Maximum number of semi colon seperated commands don't exceed 20.

-  The directory names or file names given by user should not exceed 1024 characters and the user name,system name of the system should not exceed 100 characters.

- Any path from root or home should be at most of 1024 characters.

- The symbols ​<, ​ >, ​ >>, ​ &​, ​|, ​ ; , ​ -​ would always correspond to their special meaning and would not appear otherwise, such as in inputs to echo etc.

- Kindly don't delete or alter the "history" file.# My_Shell
