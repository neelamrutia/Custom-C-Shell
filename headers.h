#ifndef HEADERS_H_
#define HEADERS_H_
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <unistd.h>
#include <time.h>
#include <inttypes.h>
#include <grp.h>
#include <unistd.h>
#include "prompt.h"
#include "warp.h"
#include "pastevent.h"
#include "peek.h"
#include "proc.h"
#include "background.h"
#include "foreground.h"
#include "seek.h"
#include "prompt1.h"
#include "command.h"

//FILE *file;
extern char *path_text;

typedef struct Node
{
    int pid;
    int status;
    struct Node *next;
} Node;

extern int no_of_back;
extern int *arr_for_back;

extern Node *completedList;

#endif