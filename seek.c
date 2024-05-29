#include "headers.h"

char path2[4096];

int c;

void search(const char *current_dir, const char *target, int flag, int flag1, int flag2)
{
    DIR *dir;
    struct dirent *entry;
    if (!(dir = opendir(current_dir)))
    {
        return;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            {
                continue;
            }
            // printf("%s\n", entry->d_name);
            // printf("%d\n", strncmp(entry->d_name, target, strlen(target)));
            // printf("%s\n", target);
            // printf("\n");
            if (strncmp(entry->d_name, target, strlen(target)) == 0)
            {
                c++;
                if (flag == 1)
                {
                    // printf("%s/%s\n", current_dir, target);
                }
                else if (flag2 == 1)
                {
                    // printf("%s/%s\n", current_dir, target);
                    // c++;
                    // chdir(current_dir);
                }
                else if (flag == 0 && flag1 == 0)
                {
                    // printf("%s/%s\n", current_dir, target);
                }
            }
            char path1[4096];
            snprintf(path1, sizeof(path1), "%s/%s", current_dir, entry->d_name);
            search(path1, target, flag, flag1, flag2);
        }
        else
        {
            if (strncmp(entry->d_name, target, strlen(target)) == 0)
            {
                c++;
                if (flag == 1 && flag1 == 0)
                {
                    continue;
                }
                else if (flag2 == 1)
                {
                    // printf("%s/%s\n", current_dir, target);
                    // chdir(current_dir);
                }
                else
                {
                    // printf("%s/%s\n", current_dir, target);
                }
            }
        }
    }
    closedir(dir);
}

void search_and_print_path(const char *current_dir, const char *target, int flag, int flag1, int flag2, char *path)
{
    DIR *dir;
    struct dirent *entry;
    if (!(dir = opendir(current_dir)))
    {
        return;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        // printf("%s\n", entry->d_name);
        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            {
                continue;
            }
            if (strncmp(entry->d_name, target, strlen(target)) == 0)
            {
                if (c > 1 && flag2 == 1)
                {
                    return;
                }
                if (flag == 1)
                {
                    char cwd[4096];
                    strcpy(cwd, current_dir);
                    // printf("curr--%s\n",cwd);
                    if (strstr(cwd, path) != NULL)
                    {
                        char temp[4096];
                        strcpy(temp, ".");
                        strcat(temp, cwd + strlen(path));
                        strcpy(cwd, temp);
                    }
                    printf("\033[1;34m");
                    printf("%s/%s\n", cwd, entry->d_name);
                    printf("\033[0m");
                }
                else if (flag2 == 1)
                {
                    char cwd[4096];
                    // getcwd(cwd, sizeof(cwd));
                    strcpy(cwd, current_dir);
                    // printf("curr--%s\n",cwd);
                    if (strstr(cwd, path) != NULL)
                    {
                        char temp[4096];
                        strcpy(temp, ".");
                        strcat(temp, cwd + strlen(path));
                        strcpy(cwd, temp);
                    }
                    printf("\033[1;34m");
                    printf("%s/%s\n", cwd, entry->d_name);
                    printf("\033[0m");
                    // char path[4096];
                    snprintf(path2, sizeof(path2), "%s/%s", current_dir, entry->d_name);
                    // chdir(path);
                }
                else if (flag == 0 && flag1 == 0)
                {
                    char cwd[4096];
                    strcpy(cwd, current_dir);
                    if (strstr(cwd, path) != NULL)
                    {
                        char temp[4096];
                        strcpy(temp, ".");
                        strcat(temp, cwd + strlen(path));
                        strcpy(cwd, temp);
                    }
                    printf("\033[1;34m");
                    printf("%s/%s\n", cwd, entry->d_name);
                    printf("\033[0m");
                    // printf("%s/%s\n", current_dir, target);
                }
            }
            char path1[4096];
            snprintf(path1, sizeof(path1), "%s/%s", current_dir, entry->d_name);
            search_and_print_path(path1, target, flag, flag1, flag2, path);
        }
        else
        {
            if (strncmp(entry->d_name, target, strlen(target)) == 0)
            {
                if (c > 1 && flag2 == 1)
                {
                    return;
                }
                if (flag == 1 && flag1 == 0)
                {
                    continue;
                }
                else if (flag2 == 1)
                {
                    if (c > 1)
                    {
                        return;
                    }
                    char cwd[4096];
                    strcpy(cwd, current_dir);
                    // printf("curr--%s\n",cwd);
                    if (strstr(cwd, path) != NULL)
                    {
                        char temp[4096];
                        strcpy(temp, ".");
                        strcat(temp, cwd + strlen(path));
                        strcpy(cwd, temp);
                    }
                    printf("\033[1;32m");
                    printf("%s/%s\n", cwd, entry->d_name);
                    printf("\033[0m");
                    char file[4096];
                    snprintf(file, sizeof(file), "%s/%s", current_dir, entry->d_name);
                    // print content of the file
                    FILE *fptr;
                    char ch;
                    fptr = fopen(file, "r");
                    // if it has not read permission then it will print error
                    if(fptr==NULL)
                    {
                        printf("Missing permissions for task!");
                        exit(1);
                    }
                    ch = fgetc(fptr);
                    while (ch != EOF)
                    {
                        printf("%c", ch);
                        ch = fgetc(fptr);
                    }
                    fclose(fptr);
                }
                else
                {
                    char cwd[4096];
                    strcpy(cwd, current_dir);
                    // printf("curr--%s\n",cwd);
                    if (strstr(cwd, path) != NULL)
                    {
                        char temp[4096];
                        strcpy(temp, ".");
                        strcat(temp, cwd + strlen(path));
                        strcpy(cwd, temp);
                    }
                    printf("\033[1;32m");
                    printf("%s/%s\n", cwd, entry->d_name);
                    printf("\033[0m");
                }
            }
        }
    }
    closedir(dir);
}

void seek(char *command, char *current_dir, int last_command, int k, char **tokens, char *path, char *previous)
{
    c = 0;
    int flag = 0;
    int flag1 = 0;
    int flag2 = 0;
    int mis = 0;
    // printf("%d\n", k);
    char name[4096];
    char change[4096];
    // char rm[4096];
    // rm[0] = '.';
    // rm[1] = '/';
    // rm[2] = '\0';
    int flag23 = 0;
    if (tokens[k - 1][0] == '.')
    {
        // char we[4096];
        // strcpy(we, tokens[k - 1] + 2);
        strcpy(change, path);
        flag23 = 1;
        // strcat(change, tokens[k - 1] + 1);
        strcat(change, tokens[k - 1] + 1);
    }
    else if (tokens[k - 1][0] == '~')
    {
        // printf("a\n");
        flag23 = 1;
        strcpy(change, path_text);
        // printf("%s\n",change);
    }
    else if (tokens[k - 1][0] == '-')
    {
        flag23 = 1;
        strcpy(change, previous);
    }
    else
    {
        strcpy(change, path);
        // strcat(change, tokens[k - 1]);
    }
    if (k == 2)
    {
        mis = 1;
        strcpy(name, tokens[1]);
    }
    else if (k == 3)
    {
        strcpy(name, tokens[2]);
        if (strcmp(tokens[1], "-d") == 0)
        {
            flag = 1;
        }
        if (strcmp(tokens[1], "-f") == 0)
        {
            flag1 = 1;
        }
        if (strcmp(tokens[1], "-e") == 0)
        {
            flag2 = 1;
        }
    }
    else
    {
        strcpy(name, tokens[3]);
        // printf("%s\n",name);
        // printf("%s\n",tokens[1]);
        // printf("%s\n",tokens[2]);
        if ((strcmp(tokens[1], "-d") == 0) || (strcmp(tokens[2], "-d") == 0))
        {
            flag = 1;
        }
        if ((strcmp(tokens[1], "-f") == 0) || (strcmp(tokens[2], "-f") == 0))
        {
            flag1 = 1;
        }
        if ((strcmp(tokens[1], "-e") == 0) || (strcmp(tokens[2], "-e") == 0))
        {
            flag2 = 1;
        }
    }
    char dir[4096];
    getcwd(dir, sizeof(dir));
    char current_dir1[4096];
    strcpy(current_dir1, change);
    // printf("path---%s\n", path);
    // chdir(change);
    if (flag23 == 1)
    {
        strcpy(name, tokens[k - 2]);
    }
    // printf("%s\n", current_dir1);
    if (access(current_dir1, F_OK) == -1)
    {
        printf("INVALID PATH\n");
        return;
    }
    if (flag1 == 1 && flag == 1)
    {
        printf("INVALID FLAG\n");
        return;
    }
    // printf("00%s00\n", name);
    search(current_dir1, name, flag, flag1, flag2);
    // printf("%d\n", c);
    search_and_print_path(current_dir1, name, flag, flag1, flag2, current_dir1);
    // printf("%d\n", c);
    // printf("%s\n", path2);
    // strstr(path2, path);
    if (c <= 1 && flag2 == 1)
    {
        chdir(path2);
    }
    if (c == 0)
    {
        printf("No such file or directory\n");
    }
    // chdir(current_dir1);
    //  search_and_print_path(name,current_dir);
}