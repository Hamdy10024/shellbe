#include "headers.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "commands.h"

#include <stdlib.h>
int bigpid;
extern char **environ;
void signal_handler (int signo) {
    signal(signo, SIG_IGN);

    if(bigpid  == getpid() && signo == SIGINT) {
            //printf("HOHO %d %d %d %d\n",bigpid,getpid(),getpgrp(),getppid());
            kill_all();

    signal(signo,(*signal_handler));
    }
    else if(signo == SIGINT)
        exit(ECANCELED);

}
void setup_environment( ){
bigpid = getpid();
signal(SIGINT,(*signal_handler));
siginterrupt(SIGINT, 1);

open_log_file("logger.txt");

open_history_file();
chdir(getenv("HOME"));
setenv("PWD",getenv("HOME"),1);






}
