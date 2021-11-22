#include "headers.h"

DIR *mydir;
char flags[4][4] = {"-a", "-l", "-al", "-la"}; //possible ls flags
int flag_a = 0, flag_l = 0;

int Is_File(char dir[]) //dir contains path to file w.r.t cwd/invalid thing
{
    for (int i = 0; i < 4; i++) //checking if it's a flag
        if (strcmp(dir, flags[i]) == 0)
            return 0;

    struct stat info = {0};
    stat(dir, &info); //stores the information about file

    if (!(S_ISDIR(info.st_mode) || S_ISREG(info.st_mode) || strcmp(dir, "~") == 0)) //checking if it's regular file or dir
    {
        printf("ls: cannot access '%s': No such file or directory\n", dir);
        return 0;
    }
    return 1;
}

void ls(int argc, char **argv)
{
    int num_flags = 0;
    //count the total number of flags given in command line,intialising flag_a,flag_l accordingly
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-al") == 0 || strcmp(argv[i], "-la") == 0)
        {
            flag_a = 1;
            flag_l = 1;
            num_flags++;
        }
        if (strcmp(argv[i], "-a") == 0)
        {
            flag_a = 1;
            num_flags++;
        }
        if (strcmp(argv[i], "-l") == 0)
        {
            flag_l = 1;
            num_flags++;
        }
    }

    for (int i = 1; i < argc; i++)
        if (Is_File(argv[i]) == 1) //checking if it's a valid regular_file/directory
        {
            if (argc > 2 + num_flags)
                printf("%s:\n", argv[i]);
            ls_l_a(argv[i]); //sending the file path w.r.t cwd
            printf("\n");
        }

    if (argc == num_flags + 1) //if no file/dir is passed then print for working directory
        ls_l_a(".");

    printf("\n");
    flag_a = 0, flag_l = 0; //Making the global variables again zero after each execution
}

void ls_l_a(char direc[])
{
    int hidden = 0;
    char dir[MAX] = "";
    strcpy(dir, direc);

    if (strcmp(dir, "~") == 0)
        strcpy(dir, home);

    struct stat hehe = {0};
    stat(dir, &hehe);

    if (S_ISREG(hehe.st_mode)) //checking if it's a regular file or not
        ls_each_file(dir, dir);

    else
    {
        //counting the total number of blocks
        int total = 0;
        if ((mydir = opendir(dir)) == NULL)
        {
            perror("Error in opening dir\n");
            return;
        }
        struct dirent *file; //for reading information of each of the file(reg/dir) from the directory

        while ((file = readdir(mydir)) != NULL)
        {
            struct stat more = {0};
            stat(file->d_name, &more);
            if ((file->d_name)[0] != '.' || flag_a)
                total += more.st_blocks;
        }

        if (flag_l)
            printf("total %d\n", total / 2);

        rewinddir(mydir);
        char path[MAX] = "";
        while ((file = readdir(mydir)) != NULL)
        {
            strcpy(path, "");
            if (strcmp(dir, home) != 0) //special case as path is not relative to current working directory
                strcpy(path, "./");

            strcat(path, dir);
            strcat(path, "/");
            strcat(path, file->d_name); //sending the path w.r.t to current directory
            ls_each_file(path, file->d_name);//sending path,file_name
        }
        closedir(mydir);
    }
}

void ls_each_file(char str[], char file_name[])
{
    struct stat my_stat = {0};
    stat(str, &my_stat);

    if (!(S_ISDIR(my_stat.st_mode) || S_ISREG(my_stat.st_mode)))
    {
        printf("ls: cannot access '%s': No such file or directory\n", file_name);
        return;
    }

    if (file_name[0] == '.' && flag_a == 0)
        return;
    if (flag_l)
    {
        (S_ISDIR(my_stat.st_mode)) ? printf("d") : printf("-");
        (my_stat.st_mode & S_IRUSR) ? printf("r") : printf("-");
        (my_stat.st_mode & S_IWUSR) ? printf("w") : printf("-");
        (my_stat.st_mode & S_IXUSR) ? printf("x") : printf("-");
        (my_stat.st_mode & S_IRGRP) ? printf("r") : printf("-");
        (my_stat.st_mode & S_IWGRP) ? printf("w") : printf("-");
        (my_stat.st_mode & S_IXGRP) ? printf("x") : printf("-");
        (my_stat.st_mode & S_IROTH) ? printf("r") : printf("-");
        (my_stat.st_mode & S_IWOTH) ? printf("w") : printf("-");
        (my_stat.st_mode & S_IXOTH) ? printf("x") : printf("-");
        printf(" %3ld  %s  %s  %6ld ", my_stat.st_nlink, getpwuid(my_stat.st_uid)->pw_name, getgrgid(my_stat.st_gid)->gr_name, my_stat.st_size);
        char *time = ctime(&my_stat.st_mtime);
        for (int i = 4; i < 16; i++)
            printf("%c", time[i]);
        printf("  %s\n", file_name);
    }
    else
        printf(" %s  ", file_name);
}