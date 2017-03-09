#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 256

#define CMD_CREATE 0
#define CMD_DELETE 1
#define CMD_DISPLAY 2
#define CMD_FIND 3
#define CMD_LIST 4
#define CMD_TREE 5

void main(){

    int cmd;
    int tokn;
    int readsize;
    FILE *fp;
    char *ptr;
    char command[100];//to store users command
    char buffer[100]; // text buffer
    char fn[90]; //filename

    while (1) {
        printf("csh> ");
        fgets(command, MAX_INPUT, stdin);
        command[strcspn(command, "\n")] = 0;

        ptr = strtok(command, " ");

        if ( strcmp(ptr, "create") == 0 ) {
            cmd = CMD_CREATE;
        } else if ( strcmp(ptr, "delete") == 0 ) {
            cmd = CMD_DELETE;
        } else if ( strcmp(ptr, "display") == 0 ) {
            cmd = CMD_DISPLAY;
        } else if ( strcmp(ptr, "list") == 0 ) {
            cmd = CMD_LIST;
        } else if ( strcmp(ptr, "find") == 0 ) {
            cmd = CMD_FIND;
        } else if ( strcmp(ptr, "tree") == 0 ) {
            cmd = CMD_TREE;
        } else {
            printf("error\n\n");
            continue;
        }

        if ( cmd <= CMD_FIND ) {
            strcpy(fn, strtok(NULL, " "));
            switch (cmd) {
                case CMD_CREATE:
                    if( fopen(fn, "w") == NULL ) printf("could not create %s\n", fn);
                    break;
                case CMD_DELETE:
                    if( remove(fn) != 0 ) printf("could not delete %s\n", fn);
                    break;
                case CMD_DISPLAY:
                    fp = fopen(fn, "r");
                    if( fp == NULL ) {
                        printf("could not open %s\n", fn);
                        break;
                    }
                    while (!feof(fp)) {
                        readsize = fread(buffer, 1, 99, fp);
                        buffer[readsize] = 0;
                        printf("%s", buffer);
                    }
                    fclose(fp);
                    break;
                default: // FIND
                    printf("finding %s\n", fn);

            }
        } else {
            ptr = strtok(NULL, " ");
        }
    }//end while
}//end main