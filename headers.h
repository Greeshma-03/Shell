#ifndef __HEADERS_H
#define __HEADERS_H

//MACRO declarations
#define MAX 1024
#define ll long long int

//libraries 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include<fcntl.h>

//header files
#include "commands.h"
#include "linked.h"

//extern declarations
extern char home[MAX];
extern struct node* head;
extern int job_num;
extern int fg_child;
char fg_name[MAX];

#endif