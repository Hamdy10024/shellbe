#include "headers.h"
#include "command_parser.h"
#include "string_processing.h"
#include "commands.h"

extern int bigpid;
void free_2d(char ** x)
{
    int i = 0;
    while(x[i])
        free(x[i++]);
    free(x[i]);
    free(x);
}

int exec_command( const char* command)
{
    if(command && *command =='#' )
        return;
    char **commands= split(command,'&');
    int nc = count_parts(command,'&');
    if(nc == 0)
        return 0;
    int i = strlen(command)-1;
    while(i>=0 && command[i]==' ')i--;
    bool is_back = command[i] =='&';
    for (i = 0 ; i < nc-1 ; i ++)
    {
        int pid = createProcess(0);
        if(!pid)
        {
            int excode=parse_command(commands[i]);
            exit(excode);
        }
        else
        {
            log_msg(pid,"");

        }

    }
    if(is_back)
    {
        int pid = createProcess(0);
        if(!pid)
        {
            int excode=parse_command(commands[i]);
            exit(excode);
        }

        log_msg(pid,"");
    }
    else
        parse_command(commands[i]);
    free_2d(commands);
}

int parse_command( const char* command )
{

    char to_exec[MAXLEN];
    replace_variables(command,to_exec);


    char **args = split(to_exec,' ');
    int n = count_parts(to_exec,' ');

    if(n==0)
        return;

    if (n==1)
    {
        if(!strcmp(args[0],"cd"))
        {
            int ret =  parse_command("cd ~");
            free_2d(args);
            return ret;
        }
        if(!strcmp(args[0],"history"))
        {
            int ret =  0;
            print_hist();
            free_2d(args);
            return ret;
        }
    }

    int e=0;
    if((e=cd(args)) > ERRNTCMD)
    {
        if(!e)
        {
            return 0;

        }
        perror("error cd ");
    }
    if((e=echo(args)) > ERRNTCMD)
    {
        if(!e)
        {
            free_2d(args);
            return 0;

        }
        perror("error echo  ");
    }
    if((e=handle_expression(args[0])) > ERRNTCMD)
    {

        if(!e)
        {
            free_2d(args);
            return 0;

        }
        perror("error expre ");
        bool op = false;
        while(*command &&(*command !=' ' || op) )
        {
            op = (*command =='"')?!op:op;
            command++;
        }
        e=parse_command(command);
        if(!e)
        {
            free_2d(args);
            return 0;

        }
        perror("error ");
    }
    if((e=execute_prog(args) )> ERRNTCMD)
    {
        if(!e)
        {
            free_2d(args);
            return 0;

        }
        perror("error exec ");
    }
    free_2d(args);
}
