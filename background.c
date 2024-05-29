#include "headers.h"
int flag = 0;
// void childHandler(int signum)
// {
//     int status;
//     pid_t completedPid;

//     while ((completedPid = waitpid(-1, &status, WNOHANG)) > 0)
//     {
//         Node *newNode = (Node *)malloc(sizeof(Node));
//         if (newNode == NULL)
//         {
//             perror("Memory allocation error");
//             exit(EXIT_FAILURE);
//         }
//         newNode->pid = completedPid;
//         newNode->status = status;
//         newNode->next = completedList;
//         completedList = newNode;
//     }
// }

int back(char *token, char *path_text)
{
    char *args[] = {"/bin/bash", "-c", token, NULL};
    flag = 1;
    int status = execvp(args[0], args);
    if (status < 0)
    {
        printf("Error in executing command\n");
        exit(-1);
    }
    return status;
}

void background(char *token, char *path_text)
{
    // printf("%s\n", token);
    // printf("background\n");
    // printf("%s\n", token);
    //   runs token in back ground and when its start run pid and when it ends run pid with exit status using execvp
    int parent_id = getpid();
    time_t start, end;
    time(&start);
    double time_taken;
    // signal(SIGCHLD, print_handler);
    int pid = fork();
    if (pid == 0)
    {
        // printf("aaaaa\n");
        //strcat(token, " &");
        int rr = back(token, path_text);
        if (rr < 0)
        {
            printf("Error in executing command\n");
            exit(-1);
        }
        // else
        // {
        //     printf("Child process background created with PID: %d\n", pid);
        //     char merged[4096];
        //     strcpy(merged, path_text);
        //     strcat(merged, "/background.txt");
        //     FILE *file = fopen(merged, "a+");
        //     fprintf(file, "process is completed with pid %d\n", pid);
        //     fclose(file);
        // }
    }
    else if (pid > 0)
    {
        printf("Child process background created with PID: %d\n", pid);
        // int pid1 = getpid();
        arr_for_back[no_of_back++] = pid;
        // if (flag == 0)
        // {
        //     signal(SIGCHLD, childHandler);
        // }
        // char merged[4096];
        // strcpy(merged, path_text);
        // strcat(merged, "/background.txt");
        // FILE *file = fopen(merged, "a+");
        // fprintf(file, "process is completed with pid %d\n", pid);
        // fclose(file);
        // printf("completed\n");
    }
    return;
}