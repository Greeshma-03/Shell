#include "headers.h"

void handler(int sent)
{
  int status;
  int pid = waitpid(-1, &status, WNOHANG); //-1 any child process
  Delete_Node(pid);

  if (pid > 0)
  {
    NodePtr ptr = Get_Node_pid(pid);
    if (ptr == NULL)
    {
      printf("Internal error!!");
      return;
    }
    if (WIFEXITED(status))
      printf("%s with pid %d exited normally\n", ptr->name, ptr->pid);
    else
      printf("%s with pid %d exited abnormally\n", ptr->name, ptr->pid);
  }
  return;
}


void handler_c(int sent)
{
  if (fg_child != -1)
    kill(fg_child, SIGINT);
  printf("\n");
  user_prompt();
  fflush(stdout);
  return;
}


void handler_z(int sent)
{   
  user_prompt();
  printf("\n");
  fflush(stdout);
  return;
}
