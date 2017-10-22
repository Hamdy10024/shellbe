#ifndef STRING_PROCESSING_H /* Include guard */
#define STRING_PROCESSING_H

/**
function splits string using a delimeter
**/
char ** split(char *input,char delimeter);

/**
validates variable names to match [a-zA-Z_]+
and returns end index of match starting from offset
**/
int is_variable(char* name,int offset);



void copy_str(const char *src,char *dest,int n);
#endif // COMMAND_PARSER_H
