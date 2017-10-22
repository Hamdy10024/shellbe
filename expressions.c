#include "expressions.h"
#include<stdio.h>
#include <stdlib.h>
#include "headers.h"
#include "string_processing.h"
#include "variables.h"

/**
replaces all variable expressions with
**/
void replace_variables(const char *input,char *output)
{
    strcpy(output,"");
    while(*input){
    while(*input >0 && *input !='$') {
        *output++ = *input++;
    }
        int n = is_variable(input,1);
        if(n == 0) {
         *output++ = *input++;
         continue;
        }
        input++;
        char var[MAXLEN];
        copy_str(input,var,n);
        input+=n;
        char *val;
        val = lookup_variable(var);
        strcpy(output,val);
       // printf(".%s. .%s. %s..\n",var,val ,output);
        output+=strlen(val);
    }
    *output =0;

}


bool isnumeric(char* input)
{
    if(*input=='-')
        input++;
    bool valid = strlen(input) >0;
    while(*input)
    {
        if (!((*input) -'0' < 10 && (*input) >='0'))
        {
            return 0;
        }
        input++;

    }

    return valid;
}



int convert(char *num,int *res)
{
    if(!isnumeric(num))
        return -1;
    int fact =1;
    if(*num =='-')
    {
        fact = -1;
        num++;
    }
    int number = 0;
    while(*num)
    {
        number*=10;
        number+=(*num -'0');
        num++;
    }
    *res = number*fact;
    return 0;

}


/**
returns 0 on success and -1 on error
**/
int eval_arithmetic(char *ex,int *result)  //TODO: implement prorder evaluation
{
    int res = 0;
    int b = 0;
    int op = 1;

    while (!(*(ex+b) ==')'))
    {
        if(*(ex+b) ==0)
            return -1;
        if(*(ex+b)=='(')
        {

            if(b!=0)
            {
                return -1;
            }
            int val;
            if(eval_arithmetic(ex+1,&val))
            {
                printf("%s ..a\n",ex+1);
                return -1;
            }
            printf("%s %d..a  .",ex+1,b);

            ex = ex + is_arithmetic_expression(ex);

            printf("%s. %d..a\n",ex,val);
            b = 0;
            op=0;
            //perform calculation
            res+=val;

        }
        else if(*(ex+b) =='+' || *(ex+b) =='-' || *(ex+b) =='*'||*(ex+b) =='/')
        {
            char te[512];
            copy_str(ex,te,b);
            //*(ex+b) = 0;
            int val = 0;
            if(isnumeric(te))
                convert(te,&val);
            else if(isnumeric(lookup_variable(ex))) {
              convert(lookup_variable(ex),&val);
            }
            else
                return -1;

            //puts(ex);
            ex = ex+b+1;
            b = 0;
            //perform calculation
            res+=val;
        }
        else
            b++;

    }

    *result = res;
    return 0;

}

/**
validates expression to match (variable)=(.*)
and returns end index of match starting from offset
**/
bool is_expression(char* name)
{
    if(count_parts(name,'=') !=2)
        return false;

    char **var = split(name,'=');
    return is_variable(var[0],0) == strlen(var[0]);
}

/**
validates expression in double square brackets
returns end index of match starting from offset
**/
int is_arithmetic_expression(char *name)
{
    int i = 0;
    char *ori = name+1;
    if(*name !='(')
        return 0;
    int opens = 1;
    while(opens)
    {
        opens += (*ori =='(');
        opens -= (*ori ==')');
        ori++;
    }

    return ori-name;
}

