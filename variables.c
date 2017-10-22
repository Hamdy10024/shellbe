#include <stdlib.h>
#include "variables.h"
#include <stdio.h>
#include "headers.h"
char keys[1024][512];
char values[1024][512];
char env_keys[1024][512];
int n=0;
char * lookup_env( char* key ){
    //puts(getenv(key));
        char *s=getenv(key);
        char* x = malloc(sizeof(char) *(strlen(s)+1));
        strcpy(x,s);
        return x;
}
char* lookup_variable(  char* key ){

    if(getenv(key)!= NULL){
        char *env;
        env = (char *)lookup_env(key);
        return env;
    }
    int i =0;
    for(i = 0 ;i < n ;i ++) {
        if(!strcmp(key,keys[i])) {
            return values[i];
        }
    }
    return "";
}

void set_variable( const char* key , const char* value ) {
    if(getenv(key)) {
        setenv(key,value,1);
        return;
    }
 int i =0;
    for(i = 0 ;i < n ;i ++) {
        if(!strcmp(key,keys[i])) {
            strcpy(values[i],value);
            return;
        }
    }

    strcpy(keys[n],key);
    strcpy(values[n++],value);
    //puts(key);
    //puts(value);

    //printf("%d")
}

/*
	[OPTIONAL] Doesn't affect the code logic
	- This is a helper function to print all your variables
	- Might help much in the debugging or testing
*/
void print_all_variables( void );

