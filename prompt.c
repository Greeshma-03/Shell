#include "headers.h"

char path[MAX] = "", add[MAX] = "";
void user_prompt()
{
   char user_name[100], system_name[100];
   int root = 0;//printing from root or home is decided

   gethostname(system_name, sizeof(system_name)); 
   getlogin_r(user_name, sizeof(user_name));

   getcwd(path, sizeof(path));
   path[sizeof(path) / sizeof(char)] = '\0';

   if (strlen(home) > strlen(path))
      root = 1;

   else
   {
      for (ll i = 0; i < strlen(home); i++)
      {
         if (home[i] != path[i])
         {
            root = 1;
            break;
         }
      }
      if (strcmp(home, path) == 0)
         root = 0;
      else if (path[strlen(home)] != '/')
         root = 1;
   }

   if (root == 0)
   {
      add[0] = '~';
      ll i;
      for (i = 1; i < strlen(path) - strlen(home) + 1; i++)
         add[i] = path[i + strlen(home) - 1];
      add[i] = '\0';
   }
   else
      strcpy(add, path);

   printf("\x1b[32m<%s@%s\x1b[0m:\x1b[34m%s> \x1b[0m", user_name, system_name, add);
   strcpy(add, "");
   return;
}
