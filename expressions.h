#ifndef EXPRESSIONS_H_INCLUDED
#define EXPRESSIONS_H_INCLUDED
#include "headers.h"

/**
replaces all variable expressions with
**/
void replace_variables(const char *input,char *output);
bool isnumeric(char* input);
/**
returns 0 on success and -1 on error
**/
int convert(char *num,int *res);
/**
returns 0 on success and -1 on error
**/
int eval_arithmetic(char *express,int *result);

/**
validates expression to match (variable)=(variable|[0-9]+)[+-/*%]+
and returns end index of match starting from offset
**/
bool is_expression(char* name);

/**
validates expression in double square brackets
returns end index of match starting from offset
**/
int is_arithmetic_expression(char *name);



#endif // EXPRESSIONS_H_INCLUDED
