#include "headers.h"


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
int is_valid_command(const char *command) {
    char check_command[100];
    snprintf(check_command, sizeof(check_command), "which %s >/dev/null 2>&1", command);
    return system(check_command) == 0;
}

int foreground(char *token)
{
    //  runs token in back ground and when its start run pid and when it ends run pid with exit status using execvp
    char **tokenn = (char **)malloc(4096 * sizeof(char *));
    char *copy = malloc(4096);
    strcpy(copy, token);
    int i = 0;
    tokenn[i] = strtok(copy, " \t\n");
    while (tokenn[i] != NULL)
    {
        i++;
        tokenn[i] = strtok(NULL, " \t\n");
    }
    tokenn[i] = NULL;
    bool flag = is_valid_command(tokenn[0]);
    if (flag == false)
    {
        printf("ERROR : %s is not a valid command\n", tokenn[0]);
        return -1;
    }
    int parent_id = getpid();
    time_t start, end;
    time(&start);
    double time_taken;
    //printf("%s\n", token);
    int pid = fork();
    if (pid == 0)
    {
        char *args[] = {"/bin/bash", "-c", token, NULL};
        int status = execvp(args[0], args);
        if (status < 0)
        {
            printf("Error in executing command\n");
            exit(-1);
        }
        //printf("Child process created with PID: %d\n", pid);
        exit(0);
    }
    else if (pid > 0)
    {

        printf("Child process foreground created with PID: %d\n", pid);
        int status;
        // give error if command not found

        waitpid(pid, &status, 0);
        //signal(SIGCHLD,childHandler);
        time(&end);
        time_taken = end - start;
        //printf("Process with pid %d exited with status %d\n", pid, status);
        if(time_taken>2)
        printf("Process with pid %d ran for %f seconds\n", pid, time_taken);
    }
    return time_taken;
}