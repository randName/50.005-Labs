#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define HISTSIZE 100
#define MAX_INPUT 256

int is_pos(char *str){
    for(int i=0;i<strlen(str)-1;i++){
        if(!isdigit(str[i])){ return -1; }
    }
    return atoi(str);
}

void changedir(char *str){
    char cwd[MAX_INPUT], dir[MAX_INPUT];
    if(strlen(str) > 3){
        memmove(str, str+3, strlen(str));
    }
    str[strcspn(str, "\n")] = 0;
    getcwd(cwd,MAX_INPUT);
    snprintf(dir,MAX_INPUT,"%s/%s",cwd,str);
    chdir(dir);
}

void cmd(char *command){
    if(strncmp(command, "cd", 2) == 0){
        changedir(command);
    } else {
        system(command);
    }
}

void main(){//start main

    char command[MAX_INPUT];//to store users command
    char history[HISTSIZE][MAX_INPUT];//for history
    int curhis = -1, i;

    //while loop to keep asking user for more inputs
    while(1){
        //Q1
        printf("csh > ");
        fgets(command,MAX_INPUT,stdin);//take input from user
        //printf("%d\tcommand %s\n",is_pos(command),command);
 
        i = is_pos(command);
        if(curhis != -1 && ((strncmp(command,"!!",2)==0)||(i!=-1 && i<curhis))){
            if (i == -1){ i = curhis-1; }
            strcpy(command, history[i%HISTSIZE]);
            printf("%s", command);
            cmd(command);
        } else {
            //check if user enters history option
            if(strncmp(command,"history",7) == 0){
                for(i=(curhis<100?0:(curhis-100));i<curhis;i++){
                    printf("%4d\t%s",i,history[i%HISTSIZE]);
                }
            } else {
                strcpy(history[(curhis++)%HISTSIZE], command);
                cmd(command);
            }            
        }
    }//end while1
}// end main

