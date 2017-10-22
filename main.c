#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "string_processing.h"
#include "expressions.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include "environment.h"


int myFork() {
    int ret = fork();
    if(ret)
        {

        printf("parent started %d\n",ret);
        return ret;

}
long long t = 1e18;
while(t--){
printf(".");
}
return ret;

}
extern int bigpid;
int k = 0;



void my_handler(int s){
           printf("Caught signal %d\n",s);
           //exit(1);
           //kill(0,SIGCONT);

}
int main(int n,char **args)
{
//  set_variable("xanex","Amira");
//
//  set_variable("hag","Dalia");
//  puts(lookup_variable("xanex"));
//
//  puts(lookup_variable("hag"));
//  char out[255];
//  replace_variables("I love $xanex so much no $hag at all $$",out);
//  puts(out);
//
//    struct sigaction sigIntHandler;
//
//   sigIntHandler.sa_handler = my_handler;
//   sigemptyset(&sigIntHandler.sa_mask);
//   sigIntHandler.sa_flags = 0;
//
//   sigaction(SIGINT, &sigIntHandler, NULL);

//int pr = myFork();
//bigpid = pr;
//if(pr){
//    int status;
//    waitpid(pr,&status,0);
//    if(WIFEXITED(status)) {
//        printf("process terminated successfuly %d",WEXITSTATUS(status));
//
//    }
//    else
//        {printf("process signal error %d %d %d %d",WEXITSTATUS(status),SIGCHLD,WIFSIGNALED(status),WTERMSIG(status));
//        printf(" %d %d",WIFSTOPPED(status),WSTOPSIG(status));
//
//}
//getchar();
//puts("\nvoila");
//}
//set_variable("var","val");
//setpgid(getpid(),getpid());
//printf("%d %d %d",getpid(),getppid(),getpgrp

FILE *input = NULL;
if(n > 1)
     input = fopen((const char*)args[1],"r");
if(input == NULL) {
    input = stdin;
}

setup_environment();

printf("shellbe>");

char line[MAXLEN+1];
while (fgets(line,MAXLEN+1,input)){
if(strlen(line)>0 &&line[strlen(line)-1] == '\n')
    line[strlen(line)-1] = 0;
//puts(line);
if(strcmp(line,"") ==0)
{

  printf("shellbe>");
  continue;
}
if(strcmp(line,"exit") ==0)
    break;
push_hist(line);
exec_command(line);
report_all();
strcpy(line,"");
printf("shellbe>");
}
close_history_file();
fclose(input);
//execv("/bin/ls",comm);
return 0;

}
