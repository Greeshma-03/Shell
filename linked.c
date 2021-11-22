#include "headers.h"

NodePtr Create_Node(char *name, pid_t pid)
{
    NodePtr ptr = (NodePtr)malloc(sizeof(Node));
    ptr->name = (char *)malloc(sizeof(char) * MAX);
    strcpy(ptr->name, name);
    ptr->pid = pid;
    ptr->next = NULL;
    ptr->job=0;
    return ptr;
}

void Print_List()
{
    NodePtr temp=head->next;
    int i=0;
    while(temp!=NULL)
    {
      printf("pid is %d for node %d\n",temp->pid,++i);
      temp=temp->next;
    }
    return;
}

void Insert_Node(char *name, pid_t pid)
{
    NodePtr ptr = Create_Node(name, pid);
    NodePtr temp = head,temp2;
    while (temp->next != NULL && strcmp(name,temp->next->name)>=0)
    {
        temp = temp->next;
    }
    temp2=temp->next;
    temp->next = ptr;
    ptr->next=temp2;
    ptr->job=job_num;
    return;
}

void Delete_Node(pid_t pid)
{
    NodePtr temp1 = head,temp2=head->next;
    
    while(temp2!=NULL)
    {
        if(temp2->pid==pid)
        break;
        temp1=temp2;
        temp2=temp2->next;
    }

    if(temp2==NULL)
    {
        return;
    }

    temp1->next=temp2->next;
    temp2=NULL;
    free(temp2);

    return;
}

void Create_List()
{
    head = Create_Node("", 0); //intialising head
    return;
}

NodePtr Get_Node_pid(pid_t pid)
{
    NodePtr temp = head->next;
    while (temp!= NULL)
    {
        if (temp->pid == pid)
            break;
        temp = temp->next;
    }
    return temp;
}

NodePtr Get_Node_job(int job)
{
    NodePtr temp = head->next;
    while (temp!= NULL)
    {
        if (temp->job == job)
            break;
        temp = temp->next;
    }
    return temp;
}