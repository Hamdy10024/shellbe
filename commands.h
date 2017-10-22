#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

/*
	- This function should be responsible for implementing the "cd" shell command
*/
int  cd( const char** path );

/*
	- This function should be responsible for implementing the "echo" shell command
	- Typically should lookup any variable included in the message
*/
int  echo( const char** message );


int  handle_expression(const char * expression);

int  execute_prog(const char** command);

#endif // COMMANDS_H_INCLUDED
