#include "headers.h"

typedef struct node Node;
typedef Node* NodePtr;

struct node{
pid_t pid;
char* name;
int job;
struct node* next;
};

struct node* head;

// int job_num=0; //total number of jobs 

NodePtr Get_Node_pid(pid_t pid);
NodePtr Get_Node_job(int job);
void Create_List();
void Delete_Node(pid_t pid);
void Insert_Node(char* name,pid_t pid);
NodePtr Create_Node(char* name,pid_t pid);
void Print_List();

