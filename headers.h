#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED
#define MAXLEN 512
#define INACTIVE_PROCESS 0

#define RUNNING_PROCESS 1

#define TERMINATED_PROCESS 2
#define DONE_PROCESS 3

#define BLOCKING_PROCESS 4

#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>
#define ERRNTCMD -1
#define MAXSIZE 1024
enum bool {
    false,true
};
typedef enum bool bool;

#endif // HEADERS_H_INCLUDED
