#include "headers.h"

FILE *history;


FILE *logger;
void open_history_file(char *path) {

    if(path == NULL)
        history = fopen("history.txt","a+");
    else
        history = fopen(path,"a+");

}
FILE* get_history_file() {
    return history;
}
void push_hist(char *msg) {
    //if(history)
    fprintf(history,"%s\n",msg);

}
void close_history_file() {
    fclose(history);

}
void print_hist() {
    //close_history_file();
    fseek(history,0,SEEK_SET);
    char t[MAXLEN];
    int i = 1;
    while(fgets(t,MAXLEN,history)) {
        printf("%d %s",i++,t);
    }

}


void open_log_file(char * path) {

    if(path == NULL)
     logger = fopen("logger.txt","a+");
    else
        logger = fopen(path,"a+");

}
FILE* get_log_file() {
    return logger;
}
void close_log_file(){
    fclose(logger);

}
void log_msg(int pid,char *msg){

    fprintf(logger,"[%d] [%s]\n",pid,msg);
    printf("[%d] [%s]\n",pid,msg);

}

