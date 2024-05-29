#include "headers.h"

void pastevents_show()
{
    char merged[4096];
    strcpy(merged, path_text);
    strcat(merged, "/pastevents.txt");
    FILE *file = fopen(merged, "r");
    char line[4096]; // Adjust the buffer size as needed
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }
    fclose(file);
}

void past_events_add(char *command)
{
    // printf("a");
    // only store 15 line AND DELETE THE FIRST LINE

    char ch;
    char merged[4096];
    strcpy(merged, path_text);
    strcat(merged, "/pastevents.txt");
    FILE *file = fopen(merged, "a+");
    // printf("%s\n",command);
    int linesCount = 0;
    fseek(file, 0, SEEK_SET);
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
            linesCount++;
    }
    fclose(file);
    FILE *file1 = fopen(merged, "r");
    char line[256]; // Adjust the buffer size as needed
    char temp[4096];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        size_t lineLength = strlen(line);
        if (lineLength > 0 && line[lineLength - 1] == '\n')
        {
            // line[lineLength - 1] = '\0';
        }
        strcpy(temp, line);
    }
    if(strcmp(temp,command)==0){
        return;
    }
    fclose(file1);
    file = fopen(merged, "a+");
    fwrite(command, 1, strlen(command), file);
    fclose(file);
    // pastevents_show();
    if (linesCount >= 15)
    {
        char **store = malloc(15 * sizeof(char *));
        for (int i = 0; i < 15; i++)
        {
            store[i] = NULL;
        }
        char merged[4096];
        strcpy(merged, path_text);
        strcat(merged, "/pastevents.txt");
        FILE *file = fopen(merged, "r");
        char line[4096]; // Adjust the buffer size as needed
        int i = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            if (i == 0)
            {
                i++;
                continue;
            }
            else
            {
                store[i - 1] = malloc(strlen(line) * sizeof(char));
                // printf("%s\n", line);
                strcpy(store[i - 1], line);
                if(store[i - 1][strlen(store[i - 1]) - 1]=='\n')
                store[i - 1][strlen(store[i - 1]) - 1] = '\0';
                i++;
            }
        }
        fclose(file);
        file = fopen(merged, "w");
        fclose(file);
        file = fopen(merged, "a+");
        for (int i = 0; i < 15; i++)
        {
            fprintf(file, "%s\n", store[i]);
        }
        fclose(file);
    }
    // fclose(file);
}

void pastevents_purge()
{
    char merged[4096];
    strcpy(merged, path_text);
    strcat(merged, "/pastevents.txt");
    FILE *file = fopen(merged, "w");
    fclose(file);
}

char *pastevents_get(int index)
{
    char **store = malloc(16 * sizeof(char *));
    for (int i = 0; i < 16; i++)
    {
        store[i] = NULL;
    }
    char merged[4096];
    strcpy(merged, path_text);
    strcat(merged, "/pastevents.txt");
    FILE *file = fopen(merged, "r");
    char line[4096]; // Adjust the buffer size as needed
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        store[i] = malloc(strlen(line) * sizeof(char));
        // printf("%s\n", line);
        strcpy(store[i], line);
        if(store[i][strlen(store[i])-1]=='\n')
        store[i][strlen(store[i])-1] = '\0';
        i++;
    }
    fclose(file);
    return store[i - index];
}