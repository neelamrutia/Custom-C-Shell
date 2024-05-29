#include "headers.h"

void prompt(char *path)
{
    char cwd[4096];
    getcwd(cwd, sizeof(cwd));
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);
    char *user = pw->pw_name;
    char hostname[1024];
    gethostname(hostname, 1024);
    //printf("%s\n", path);
    char *home = getenv("HOME");
    if (strstr(cwd, path) != NULL)
    {
        char temp[4096];
        strcpy(temp, "~");
        strcat(temp, cwd + strlen(path));
        strcpy(cwd, temp);
    }
    printf("<%s@%s:%s>", user, hostname, cwd);
    return;
}
