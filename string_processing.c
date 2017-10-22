#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "string_processing.h"
#include"headers.h"
int count_parts(const char *input,char del)
{

    char *c = &(input[0]);
    int parts = 0,len = 0;
    bool ter = false;
    while(*c !=0)
    {
        //printf("%c ",*c);
        if(del == *c && len > 0 && !ter)
        {
            parts++;
            len =0 ;
        }
        else if(*c =='"')
        {
            ter = !ter &&(del ==' ');

        }
        else if(del !=*c || ter)
            len++;
        c++;
    }

    return parts + (len >0);
}
char ** split(char *input,char delimeter)
{
    int parts = count_parts(input,delimeter);
    //printf("%d",parts);
    char comm[MAXLEN];
    //strcpy(comm,input);
    int i=0;
    bool enfin = 1,ter = 0;
    while(*input)
    {


        if (*input == '"' &&(delimeter ==' '))
        {
            ter = !ter &&(delimeter ==' ');
            input++;
        }
        else if(*input!=delimeter || ter)
        {
            comm[i++] =*input++;
            enfin = 0;
        }
        else if(enfin)
            input++;
        else
        {
            comm[i++] = 0;
            enfin = 1;
        }
    }
        if(!enfin)
            comm[i] = 0;
    char *st = &(comm[0]);
    char **sets =(char**)malloc((parts+1)*sizeof(char*));
    for( i = 0; i<parts; i++)
    {
        sets[i] = (char*)malloc(MAXLEN*sizeof(char));
        //puts(st);
        strcpy(sets[i],st);
        st+=strlen(st)+1;
    }

    sets[i] = (char*)malloc(MAXLEN*sizeof(char));
    sets[i] = (char *)0;
    return sets;
}

int is_variable(char *name,int offset)
{
    if(name == NULL)
        return 0;
    name = name+offset;
    int mval = 0;
    while((*name >='a' && *name <='z') || (*name>='A' && *name<='Z')
        ||*name =='_' || (*name >='0' && *name<='9'))
    {
        mval++;
        name++;
    }
    return mval;

}


void copy_str(const char *src,char *dest,int n)
{
    int len = (n>strlen(src))?strlen(src):n;
    int i =0;
    for( i = 0; i<len; i++)
    {
        dest[i] = src[i];

    }

    dest[i] = 0;
}
