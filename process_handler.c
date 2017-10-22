#include "headers.h"
#include "process_handler.h"
int _processes;
int processes[MAXSIZE];
int process_state[MAXSIZE]; //  0 inactive 1 running 2 terminated 3 Done 4 blocking
int process_exit_code[MAXSIZE];


/**
creates process and attaches it to running processes
returns 0 for child, 1 for parent , -1 for error
**/
int createProcess(bool wait )  {
    pid_t pid = fork();
    if (pid) {
        processes[_processes] = pid;
        if(!wait)
            process_state[_processes++] = RUNNING_PROCESS;
        if(wait)
            process_state[_processes++] = BLOCKING_PROCESS;
        return pid;
    }
    else {
        start_process();
        return 0;
    }


}

/**
clears required data unneeded from parent
returns 0 for successful initiation , -1 for error
**/
int start_process(void) {
_processes = 0;
return 0;
}

int kill_all() {
int i;
for(i=0;i<_processes;i++){
    if(process_state[i] == BLOCKING_PROCESS)
       {
            if(waitpid(processes[i],NULL,WNOHANG) == processes[i])
                continue;

            printf("%d is killing %d who is is %d \n",getpid(),processes[i],process_state[i]);
            int s= kill(processes[i],SIGINT);
            if(!s)
                process_state[i] = TERMINATED_PROCESS;

        }

        }
       // puts("");

}

void report_all() {
    int i = 0;
    for(i=0;i<_processes;i++) {
        if(process_state[i] ==INACTIVE_PROCESS)
            continue;
        if(process_state[i] == RUNNING_PROCESS || process_state[i] == BLOCKING_PROCESS) {
            int status;
            int b = waitpid(processes[i],&status,WNOHANG);
             //printf("%d %d %d\n",processes[i],process_state[i],b);
             if(b == -1) {
                 process_state[i] = INACTIVE_PROCESS;
                 errno = 0;
             }
            if(b == processes[i]) {

                process_state[i] = INACTIVE_PROCESS;
                process_exit_code[i] = WEXITSTATUS(status);
                if(!WIFSIGNALED(status))
                    log_msg(processes[i] , "DONE");
                else{
                    process_state[i]=TERMINATED_PROCESS;
                    }
            }

        }
        if(process_state[i] == TERMINATED_PROCESS) {
                log_msg(processes[i] , "TERMINATED");
            process_state[i] = INACTIVE_PROCESS;
        }


    }

}
