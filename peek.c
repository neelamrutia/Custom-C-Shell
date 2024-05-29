#include "headers.h"

int alphasort(const struct dirent **a, const struct dirent **b)
{
    return strcmp((*a)->d_name, (*b)->d_name);
}

void peek(char **tokens, int i, int j, char *previous, char *path)
{
    char path1[4096];
    if (i <= 2)
    {
        strcpy(path1, ".");
        // printf("1");
    }
    else if (i == 3 && ((strcmp(tokens[2], "-a") == 0) || (strcmp(tokens[2], "-l") == 0)))
    {
        strcpy(path1, ".");
    }
    else if (i == 3)
    {
        // printf("AAA\n");
        strcpy(path1, tokens[2]);
    }
    else
    {
        strcpy(path1, tokens[i - 1]);
    }
    if (access(path1, F_OK) == -1 && path1[0] != '~' && strcmp(path1, "-") != 0)
    {
        printf("No such file or directory\n");
        return;
    }
    if (tokens[j + 1] == NULL)
    {
        //DIR *d = opendir(".");
        struct dirent **namelist;
        int n = scandir(".", &namelist, NULL, alphasort);
        struct dirent *Data;
        // int long total_size = 0;
        // DIR *d = opendir(".");
        // while ((Data = readdir(d)) != NULL)
        // {
        //     if (Data->d_name[0] == '.')
        //     {
        //         continue;
        //     }
        //     struct stat fileStat;
        //     char entryPath[4096];
        //     snprintf(entryPath, sizeof(entryPath), "%s/%s", path, Data->d_name);
        //     if (stat(entryPath, &fileStat) == 0)
        //     {
        //         total_size += fileStat.st_blocks;
        //         // printf("%ld ", fileStat.st_blocks);
        //     }
        // }
        // printf("total %ld\n", total_size);
        for (int i = 0; i < n; i++)
        {
            if (namelist[i]->d_name[0] != '.')
            {
                struct stat fileStat;
                if (stat(namelist[i]->d_name, &fileStat) < 0)
                    return;
                if (S_ISDIR(fileStat.st_mode))
                {
                    printf("\033[1;34m");
                    printf("%s\n", namelist[i]->d_name);
                    printf("\033[0m");
                }
                else if (fileStat.st_mode & S_IXUSR)
                {
                    printf("\033[1;32m");
                    printf("%s\n", namelist[i]->d_name);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", namelist[i]->d_name);
                }
                free(namelist[i]);
            }
        }
        free(namelist);
        return;
    }
    int flag = 0;
    int flag1 = 0;
    int flag2 = 0;
    for (int k = j + 1; k < i; k++)
    {
        if (strcmp(tokens[k], "-l") == 0)
        {
            flag = 1;
        }
        if (strcmp(tokens[k], "-a") == 0)
        {
            flag1 = 1;
        }
        if (strcmp(tokens[k], "-la") == 0 || strcmp(tokens[k], "-al") == 0)
        {
            flag2 = 1;
        }
    }
    if (flag1 == 0 && flag2 == 0 && flag == 0 && i == 2)
    {
        strcpy(path1, tokens[1]);
    }
    // printf("path1111----  %s\n", path1);
    if (strcmp(path1, "~") == 0)
    {
        strcpy(path1, path);
    }
    else if (path1[0] == '~' && path1[1] == '/')
    {
        int l = 2;
        char temp[4096];
        int m = 0;
        while (path1[l] != '\0')
        {
            temp[m++] = path1[l++];
        }
        temp[m] = '\0';
        strcpy(path1, path);
        strcat(path1, "/");
        strcat(path1, temp);
    }
    else if (strcmp(path1, "-") == 0)
    {
        // printf("in function--%s\n", previous);
        strcpy(path1, previous);
    }
    else
    {
        strcpy(path1, tokens[i - 1]);
    }
    // printf("%s\n", path1);
    char cwd1[4096];
    getcwd(cwd1, sizeof(cwd1));
    // printf("%s\n", cwd1);
    chdir(path1);
    char cwd[4096];
    getcwd(cwd, sizeof(cwd));
    if (flag1 == 0 && flag2 == 0 && flag == 0 && i == 2)
    {
        struct dirent **namelist;
        int n = scandir(".", &namelist, NULL, alphasort);
        // struct dirent *Data;
        // int long total_size = 0;
        // DIR *d = opendir(".");
        // while ((Data = readdir(d)) != NULL)
        // {
        //     if (Data->d_name[0] == '.')
        //     {
        //         continue;
        //     }
        //     struct stat fileStat;
        //     char entryPath[4096];
        //     snprintf(entryPath, sizeof(entryPath), "%s/%s", path, Data->d_name);
        //     if (stat(entryPath, &fileStat) == 0)
        //     {
        //         total_size += fileStat.st_blocks;
        //         // printf("%ld ", fileStat.st_blocks);
        //     }
        // }
        // printf("total %ld\n", total_size);
        for (int i = 0; i < n; i++)
        {
            if (namelist[i]->d_name[0] != '.')
            {
                struct stat fileStat;
                if (stat(namelist[i]->d_name, &fileStat) < 0)
                    return;
                if (S_ISDIR(fileStat.st_mode))
                {
                    printf("\033[1;34m");
                    printf("%s\n", namelist[i]->d_name);
                    printf("\033[0m");
                }
                else if (fileStat.st_mode & S_IXUSR)
                {
                    printf("\033[1;32m");
                    printf("%s\n", namelist[i]->d_name);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", namelist[i]->d_name);
                }
                free(namelist[i]);
            }
        }
        free(namelist);
        chdir(cwd1);
        return;
    }
    // printf("%d %d %d\n", flag, flag1, flag2);
    if (flag == 0 && flag1 == 0 && flag2 == 0)
    {
        struct dirent **namelist;
        int n = scandir(".", &namelist, NULL, alphasort);
        // struct dirent *Data;
        // int long total_size = 0;
        // DIR *d = opendir(".");
        // while ((Data = readdir(d)) != NULL)
        // {
        //     if (Data->d_name[0] == '.')
        //     {
        //         continue;
        //     }
        //     struct stat fileStat;
        //     char entryPath[4096];
        //     snprintf(entryPath, sizeof(entryPath), "%s/%s", path, Data->d_name);
        //     if (stat(entryPath, &fileStat) == 0)
        //     {
        //         total_size += fileStat.st_blocks;
        //         // printf("%ld ", fileStat.st_blocks);
        //     }
        // }
        // printf("total %ld\n", total_size);
        for (int i = 0; i < n; i++)
        {
            if (namelist[i]->d_name[0] != '.')
            {
                struct stat fileStat;
                if (stat(namelist[i]->d_name, &fileStat) < 0)
                    return;
                if (S_ISDIR(fileStat.st_mode))
                {
                    printf("\033[1;34m");
                    printf("%s\n", namelist[i]->d_name);
                    printf("\033[0m");
                }
                else if (fileStat.st_mode & S_IXUSR)
                {
                    printf("\033[1;32m");
                    printf("%s\n", namelist[i]->d_name);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", namelist[i]->d_name);
                }
                free(namelist[i]);
            }
        }
        free(namelist);
        chdir(cwd1);
        return;
    }
    if ((flag == 0 && flag1 == 1))
    {
        struct dirent **namelist;
        int n = scandir(".", &namelist, NULL, alphasort);
        // struct dirent *Data;
        // int long total_size = 0;
        // DIR *d = opendir(".");
        // while ((Data = readdir(d)) != NULL)
        // {
        //     struct stat fileStat;
        //     char entryPath[4096];
        //     snprintf(entryPath, sizeof(entryPath), "%s/%s", path, Data->d_name);
        //     if (stat(entryPath, &fileStat) == 0)
        //     {
        //         total_size += fileStat.st_blocks;
        //         // printf("%ld ", fileStat.st_blocks);
        //     }
        // }
        // printf("total %ld\n", total_size);
        for (int i = 0; i < n; i++)
        {
            struct stat fileStat;
            if (stat(namelist[i]->d_name, &fileStat) < 0)
                return;
            if (S_ISDIR(fileStat.st_mode))
            {
                printf("\033[1;34m");
                printf("%s\n", namelist[i]->d_name);
                printf("\033[0m");
            }
            else if (fileStat.st_mode & S_IXUSR)
            {
                printf("\033[1;32m");
                printf("%s\n", namelist[i]->d_name);
                printf("\033[0m");
            }
            else
            {
                printf("%s\n", namelist[i]->d_name);
            }
            free(namelist[i]);
        }
        free(namelist);
    }
    if ((flag == 1 && flag1 == 0))
    {
        struct dirent **namelist;
        int n = scandir(".", &namelist, NULL, alphasort);
        struct dirent *Data;
        int long total_size = 0;
        DIR *d = opendir(".");
        while ((Data = readdir(d)) != NULL)
        {
            if (Data->d_name[0] == '.')
            {
                continue;
            }
            struct stat fileStat;
            char entryPath[4096];
            snprintf(entryPath, sizeof(entryPath), "%s/%s", path, Data->d_name);
            if (stat(entryPath, &fileStat) == 0)
            {
                total_size += fileStat.st_blocks;
                // printf("%ld ", fileStat.st_blocks);
            }
        }
        printf("total %ld\n", total_size);
        for (int i = 0; i < n; i++)
        {
            if (namelist[i]->d_name[0] != '.')
            {
                struct stat fileStat;
                if (stat(namelist[i]->d_name, &fileStat) < 0)
                    return;
                printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
                printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
                printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
                printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
                printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
                printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
                printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
                printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
                printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %ld", fileStat.st_nlink);
                printf(" %s", getpwuid(fileStat.st_uid)->pw_name);
                printf(" %s", getgrgid(fileStat.st_gid)->gr_name);
                printf(" %ld", fileStat.st_size);
                // print time like terminal ls -l
                char time[1024];
                strftime(time, 1024, "%b %d %H:%M", localtime(&(fileStat.st_ctime)));
                printf(" %s ", time);
                // print folder in blue and executable in green
                if (S_ISDIR(fileStat.st_mode))
                {
                    printf("\033[1;34m");
                    printf("%s\n", namelist[i]->d_name);
                    printf("\033[0m");
                }
                else if (fileStat.st_mode & S_IXUSR)
                {
                    printf("\033[1;32m");
                    printf("%s\n", namelist[i]->d_name);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", namelist[i]->d_name);
                }
                free(namelist[i]);
            }
        }
        free(namelist);
    }
    if ((flag == 1 && flag1 == 1) || flag2 == 1)
    {
        struct dirent **namelist;
        int n = scandir(".", &namelist, NULL, alphasort);
        struct dirent *Data;
        int long total_size = 0;
        DIR *d = opendir(".");
        while ((Data = readdir(d)) != NULL)
        {
            struct stat fileStat;
            char entryPath[4096];
            snprintf(entryPath, sizeof(entryPath), "%s/%s", path, Data->d_name);
            if (stat(entryPath, &fileStat) == 0)
            {
                total_size += fileStat.st_blocks;
                // printf("%ld ", fileStat.st_blocks);
            }
        }
        printf("total %ld\n", total_size);
        for (int i = 0; i < n; i++)
        {
            struct stat fileStat;
            if (stat(namelist[i]->d_name, &fileStat) < 0)
                return;
            printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
            printf(" %ld", fileStat.st_nlink);
            printf(" %s", getpwuid(fileStat.st_uid)->pw_name);
            printf(" %s", getgrgid(fileStat.st_gid)->gr_name);
            printf(" %ld", fileStat.st_size);
            // print time like terminal ls -l
            char time[1024];
            strftime(time, 1024, "%b %d %H:%M", localtime(&(fileStat.st_ctime)));
            printf(" %s ", time);
            // print folder in blue and executable in green
            if (S_ISDIR(fileStat.st_mode))
            {
                printf("\033[1;34m");
                printf("%s\n", namelist[i]->d_name);
                printf("\033[0m");
            }
            else if (fileStat.st_mode & S_IXUSR)
            {
                printf("\033[1;32m");
                printf("%s\n", namelist[i]->d_name);
                printf("\033[0m");
            }
            else
            {
                printf("%s\n", namelist[i]->d_name);
            }
            free(namelist[i]);
        }
        free(namelist);
    }
    chdir(cwd1);
}