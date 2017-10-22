#ifndef PROCESS_HANDLER_H /* Include guard */
#define PROCESS_HANDLER_H
#include "headers.h"
/**
creates process and attaches it to running processes
returns 0 for child, 1 for parent , -1 for error
**/
int createProcess(bool wait ) ;

/**
clears required data unneeded from parent
returns 0 for successful initiation , -1 for error
**/
int start_process(void);

/**
rerports status of all active processes
**/
void report_all();

/**
responsible for killing all foreground active processes
**/
int kill_all();
#endif
