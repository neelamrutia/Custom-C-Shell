#include "headers.h"
// #include <stdback_loop.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>
#include <grp.h>
#include <ctype.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>

int compare_strings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

void handleCtrlC(int sig)
{
    FILE *file = fopen("pastevents.txt", "a+");
    char *command = malloc(4096);
    strcpy(command, "exit\n");
    fwrite(command, 1, strlen(command), file);
    fclose(file);
    printf("\nCtrl+C received. Exiting the program...\n");
    exit(0);
}

Node *completedList = NULL;
char *path_text = NULL;
int no_of_back = 0;
int *arr_for_back = NULL;

int main()
{
    arr_for_back = (int *)malloc(sizeof(int) * 10000);
    path_text = (char *)malloc(sizeof(char) * 4096);
    char for_promt[4096];
    char previous[4096];
    char path[4096];
    char cwd[4096];
    getcwd(cwd, sizeof(cwd));
    strcpy(path_text, cwd);
    strcpy(path, cwd);
    strcpy(previous, cwd);
    int pid = -100;
    int for_flag = 0;
    while (1)
    {
        if (for_flag == 1)
        {
            prompt1(path, for_promt);
        }
        else
        {
            prompt(path);
        }
        for_flag = 0;
        char input[4096];
        char *copy = malloc(4096);
        char *pass = malloc(4096);
        char *past_exec = malloc(4096);
        fgets(input, 4096, stdin);
        strcpy(past_exec, input);
        for (int okl = 0; okl < no_of_back; okl++)
        {
            if(arr_for_back[okl]>0){
                pid_t result = waitpid(arr_for_back[okl], NULL, WNOHANG);
                //printf("%d\n",result);
                if (result>0)
                {
                    printf("Child process with PID %d exited normally with status %d\n", arr_for_back[okl], WEXITSTATUS(result));
                    arr_for_back[okl]=-1;
                }
            }
        }
        strcpy(pass, input);
        char merged[4096];
        strcpy(merged, path_text);
        strcat(merged, "/background.txt");
        FILE *file = fopen(merged, "r");
        char line[4096];
        while (fgets(line, sizeof(line), file) != NULL)
        {
            printf("%s\n", line);
        }
        fclose(file);
        FILE *file1 = fopen(merged, "w");
        fclose(file1);
        strcpy(copy, input);
        char *command = malloc(4096);
        strcpy(command, input);
        char *token = strtok(input, ";");
        char *tokens[4096];
        int check = 0;
        int check1 = 0;
        int i = 0;
        while (token != NULL)
        {
            tokens[i] = token;
            if (strcmp(tokens[i], "&") == 0)
            {
                check = 1;
            }
            if (strcmp(tokens[i], ";") == 0)
            {
                check1 = 1;
            }
            token = strtok(NULL, ";");
            i++;
        }
        tokens[i - 1][strlen(tokens[i - 1]) - 1] = '\0';
        char **pass1 = malloc(4096);
        int pa = 0;
        char *pas = strtok(pass, " ");
        while (pas != NULL)
        {
            pass1[pa] = pas;
            pas = strtok(NULL, " ");
            pa++;
        }
        pass1[pa - 1][strlen(pass1[pa - 1]) - 1] = '\0';
        int flag = 0;
        int flag2 = 0;
        for (int uu = 0; uu < pa; uu++)
        {
            // printf("%lu\n",strlen(pass1[uu]));
            if (strcmp(pass1[uu], "pastevents") == 0)
            {
                flag = 1;
            }
        }
        // printf("%d\n",flag);
        char **tokens1 = malloc(4096);
        char name[4096];
        if (pid != -100)
        {
            printf("%s with pid %d exited normally\n", name, pid);
        }
        int check_for_past = 0;
        for (int p = 0; p < i; p++)
        {
            int sleep = 0;
            int le = strlen(tokens[i - 1]);
            if (tokens[i - 1][le - 1] == '&')
            {
                sleep = 1;
            }
            int j = 0;
            char *token1 = strtok(tokens[p], "&");
            while (token1 != NULL)
            {
                tokens1[j] = token1;
                token1 = strtok(NULL, "&");
                j++;
            }
            // tokens1[j - 1][strlen(tokens1[j - 1]) - 1] = '\0';
            if (flag == 0 && check_for_past == 0)
            {
                past_events_add(copy);
                check_for_past = 1;
            }
            for (int back_loop = 0; back_loop < j; back_loop++)
            {
                if (back_loop != j - 1 || sleep == 1)
                {
                    background(tokens1[back_loop], path);
                    continue;
                }
                else
                {
                    char *copy1 = malloc(4096);
                    strcpy(copy1, tokens1[back_loop]);
                    char **tokens2 = malloc(4096);
                    int k = 0;
                    char *token2 = strtok(tokens1[back_loop], " ");
                    while (token2 != NULL)
                    {
                        tokens2[k] = token2;
                        token2 = strtok(NULL, " ");
                        k++;
                    }
                    // tokens2[k - 1][strlen(tokens2[k - 1]) - 1] = '\0';
                    for (int last_command = 0; last_command < k; last_command++)
                    {
                        // printf("%s\n", tokens2[1]);
                        if (strcmp(tokens2[last_command], "pastevents") == 0)
                        {
                            // flag = 1;
                            // gg = 1;
                            // printf("%s\n",tokens2[last_command+1]);
                            if (last_command == k - 1)
                            {
                                pastevents_show();
                            }
                            else if (strcmp(tokens2[last_command + 1], "purge") == 0)
                            {
                                // printf("purge\n");
                                pastevents_purge();
                            }
                            else if (strcmp(tokens2[last_command + 1], "execute") == 0)
                            {
                                //printf("execute\n");
                                // printf("%s\n", tokens2[last_command + 2]);
                                char *back = pastevents_get(atoi(tokens2[last_command + 2]));
                                // printf("back is--%s--\n", back);
                                command_fun(back, path, previous, path_text,past_exec);
                                //  pastevent_execute(back);
                            }
                            else
                            {
                                pastevents_show();
                            }
                            break;
                        }
                        else if (strcmp(tokens2[last_command], "warp") == 0)
                        {
                            char *previous1 = warp(previous, path, tokens2, k, last_command);
                            // gg = 1;
                            //  printf("return value ---- %s\n", previous1);
                            strcpy(previous, previous1);
                            break;
                        }
                        else if (strcmp(tokens2[last_command], "peek") == 0)
                        {
                            // printf("start---%s\n",previous);
                            // gg = 1;
                            peek(tokens2, k, last_command, previous, path);
                            break;
                        }
                        else if (strcmp(tokens2[last_command], "seek") == 0)
                        {
                            char current[4096];
                            getcwd(current, sizeof(current));
                            // printf("start---%s\n",current);
                            seek(command, path, last_command, k, tokens2, current,previous);
                            break;
                        }
                        else if (strcmp(tokens2[last_command], "proclore") == 0)
                        {
                            proclore(tokens2, last_command, k);
                            break;
                        }
                        else
                        {

                            int a = foreground(copy1);
                            if (a > 2)
                            {
                                for_flag = 1;
                                strcpy(for_promt, copy1);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}