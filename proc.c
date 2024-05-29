#include "headers.h"

void proclore(char **token, int last_command, int k)
{
    pid_t pid;
    if (last_command == k - 1)
    {
        pid = getpid();
    }
    else
    {
        pid = atoi(token[last_command + 1]);
    }
    // pid = k;
    printf("pid -- %d\n", pid);
    char path[1000];
    sprintf(path, "/proc/%d/status", pid);
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        printf("Process does not exist\n");
        return;
    }
    char executablePath[2048];
    char line[1000];
    printf("Group -- %d\n", getpgid(pid));
    while (fgets(line, sizeof(line), f) != NULL)
    {
        char **token3 = malloc(1000);
        char *token1 = strtok(line, " \t\n");
        int i = 0;
        int long gpid = getpgid(pid);
        while (token1 != NULL)
        {
            token3[i] = token1;
            token1 = strtok(NULL, " \t\n");
            i++;
        }
        if (strncmp(line, "State:", 6) == 0)
        {
            printf("process status -- %s", token3[1]);
            if (gpid == pid)
            {
                printf("+\n");
            }
            else
            {
                printf("\n");
            }
        }
        if (strncmp(line, "VmSize:", 7) == 0)
        {
            printf("virtula memory -- %s\n", token3[1]);
        }
        if (strncmp(line, "path:", 5) == 0)
        {
            printf("Executable path -- %s", line);
        }
    }
    char exePath[4096];
    snprintf(exePath, sizeof(exePath), "/proc/%d/exe", pid);
    ssize_t bytesRead = readlink(exePath, exePath, sizeof(exePath) - 1);
    exePath[bytesRead] = '\0';
    printf("Executable Path: %s\n", exePath);
    // printf("Executable path -- %s\n", executablePath);

    fclose(f);
}