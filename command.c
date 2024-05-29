#include "headers.h"

void command_fun(char *input, char *path, char *previous, char *path_text, char *past_exec)
{
    // printf("input--%s--\n", input);
    char neel[4096];
    strcpy(neel, input);
    // printf("input--%s--\n", neel);
    strcat(neel, "\n");
    char **oppp1 = malloc(4096);
    char *opp1 = strtok(past_exec, ";");
    int i1 = 0;
    while (opp1 != NULL)
    {
        oppp1[i1] = opp1;
        opp1 = strtok(NULL, ";");
        i1++;
    }
    int oppp = 0;
    char *add_past = malloc(4096);
    int flag = 0;
    //printf("i1--%d\n", i1);
    for (int uiop = 0; uiop < i1; uiop++)
    {
       // printf("%s\n", oppp1[uiop]);
        if (strncmp(oppp1[uiop], " pastevents", 11) == 0 || strncmp(oppp1[uiop], "pastevents", 10) == 0)
        {
            flag = 1;
            strcat(add_past, input);
            if(uiop!=i1-1)
            strcat(add_past, " ; ");
        }
        else
        {
            strcat(add_past, oppp1[uiop]);
            if(uiop!=i1-1)
            strcat(add_past, " ; ");
        }
    }
    //add_past[strlen(add_past) - 1] = '\0';
    strcat(add_past, "\n");
    if (flag == 1)
    {
        past_events_add(add_past);
    }
    else
    {
        past_events_add(neel);
    }
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
    char *copy = malloc(4096);
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
    // tokens[i - 1][strlen(tokens[i - 1]) - 1] = '\0';
    char **tokens1 = malloc(4096);
    char name[4096];
    // if (pid != -100)
    // {
    //     printf("%s with pid %d exited normally\n", name, pid);
    // }
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
        // int flag = 0;
        // for (int uu = 0; uu < j; uu++)
        // {
        //     if (strcmp(tokens1[uu], "pastevent") == 0)
        //     {
        //         flag = 1;
        //     }
        // }
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
                for (int last_command = 0; last_command < k; last_command++)
                {
                    // printf("%s\n", tokens2[last_command]);
                    if (strcmp(tokens2[last_command], "pastevents") == 0)
                    {
                        // flag = 1;
                        // gg = 1;
                        if (last_command == k - 1)
                        {
                            pastevents_show();
                        }
                        else if (strcmp(tokens2[last_command + 1], "purge") == 0)
                        {
                            pastevents_purge();
                        }
                        else if (strcmp(tokens2[last_command + 1], "execute") == 0)
                        {
                            char *back = pastevents_get(atoi(tokens2[last_command + 2]));
                            command_fun(back, path, previous, path_text, past_exec);
                            // pastevent_execute(back);
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
                        // printf("a\n");
                        char current[4096];
                        getcwd(current, sizeof(current));
                        // printf("start---%s\n",current);
                        seek(command, path, last_command, k, tokens2, current, previous);
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
                        break;
                    }
                }
            }
        }
    }
    return;
}