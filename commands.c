#include "commands.h"
#include "variables.h"
#include "expressions.h"
#include "headers.h"
int cd( const char** path )
{
    //printf("cd says %s\n",path[0]);
    if (strcmp((const char *)path[0],"cd")) {
        //puts(path[0]);
        return -1;
    }
    //printf("%d....\n",path[1]==0);
    if(path[1] == 0 || path[1][0] =='~') {
        char tem[MAXLEN];
        strcpy(tem,lookup_variable("HOME"));
       // puts(tem);
        path[1]+=(path[1]!=0 && path[1][0]=='~');
        strcat(tem,path[1]);
        strcpy(path[1],tem);
    }
    int ret = chdir(path[1]);
    if (!ret )
    {
        char cwd[MAXSIZE];
        if(getcwd(cwd, MAXSIZE))
            set_variable("PWD",cwd);
        return 0;
    }
    return errno;

}

int echo( const char** message ){


  //  printf("echo says %s\n",message[0]);
        if(strcmp((const char *)message[0],"echo")) {
            return -1;
            }
        char out[MAXLEN];
        strcpy(out,"");
        message++;
        while(message[0]) {

            strcat(out,*message++);

            strcat(out," ");
            }
        puts(out);
        return 0;
}

int handle_expression(const char * expression){


    if(is_expression(expression)) {
        char **seg = split(expression,'=');
        set_variable(seg[0],seg[1]);
        free_2d(seg);
        return 0;
    }
    return -1;

}

int execute_prog(const char** command) {
   pid_t pid = createProcess(1);
    if(pid) {
        int status ;
        waitpid(pid,&status,0);
        if(!WIFEXITED(status)) {
            return -1;
        }
        if(WEXITSTATUS(status) > 131)
            return -1;
        return WEXITSTATUS(status);
    }
    char **all = split(getenv("PATH"),':');
    char **hold=all;
    errno = 0;
    int ret = execv(command[0],command);

    while (all[0]) {
        char str[MAXLEN];
        strcpy(str,*all);

        strcat(str,"/");
        strcat(str,command[0]);
        ret = execv(str,command);
        if(!ret)
            exit(0) ;
        all++;
    }
    free_2d(hold);
    exit(132);
}
