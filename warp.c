#include "headers.h"

char tamp1[4096];

char *warp(char *previous, char *path, char **tokens, int i, int j)
{
    strcpy(tamp1, previous);
    int k = j + 1;
    if (k == i)
    {
        getcwd(tamp1, sizeof(tamp1));
        chdir(path);
        char cwd[4096];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
        return tamp1;
    }
    while (k < i)
    {
        if (strcmp(tokens[k], ";") == 0)
        {
            break;
        }
        if (access(tokens[k], F_OK) == -1 && tokens[k][0] != '~' && strcmp(tokens[k], "-") != 0)
        {
            printf("No such file or directory\n");
            break;
        }
        if (tokens[k][0] == '~' && tokens[k][1] == '/')
        {
            int l = 2;
            char temp[4096];
            int m = 0;
            while (tokens[k][l] != '\0')
            {
                temp[m++] = tokens[k][l++];
            }
            temp[m] = '\0';
            getcwd(tamp1, sizeof(tamp1));
            chdir(path);
            if (strcmp(temp, "") == 0)
            {
                chdir(path);
                char cwd[4096];
                getcwd(cwd, sizeof(cwd));
                printf("%s\n", cwd);
                break;
            }
            else
            {
                chdir(temp);
                char cwd[4096];
                getcwd(cwd, sizeof(cwd));
                printf("%s\n", cwd);
                break;
            }
        }
        if (strcmp(tokens[k], "~") == 0)
        {
            getcwd(tamp1, sizeof(tamp1));
            chdir(path);
            char cwd[4096];
            getcwd(cwd, sizeof(cwd));
            printf("%s\n", cwd);
            break;
        }
        if (strcmp(tokens[k], "-") == 0)
        {
            char temp[4096];
            getcwd(temp, sizeof(temp));
            // printf("%s\n", temp);
            // printf("%s\n", tamp1);
            chdir(tamp1);
            printf("%s\n", tamp1);
            strcpy(tamp1, temp);
            break;
        }
        getcwd(tamp1, sizeof(tamp1));
        chdir(tokens[k++]);
        char cwd[4096];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
    }
    return tamp1;
}