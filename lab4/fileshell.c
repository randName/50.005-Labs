#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define CMD_CREATE 0
#define CMD_DELETE 1
#define CMD_DISPLAY 2
#define CMD_FIND 3
#define CMD_LIST 4
#define CMD_TREE 5

#define PROP_NAME 0
#define PROP_TIME 1
#define PROP_SIZE 2

char fn[90]; //filename
int t_depth;
int sortprop;

int recursive_find(const char *dirname) {
    struct dirent *pent;
    DIR *dp = opendir(dirname);
    if ( dp == NULL ) return -1;
    while ( pent = readdir(dp) ) {
        if ( strncmp(pent->d_name, ".", 1) == 0 ) continue;
        recursive_find(pent->d_name);
        if ( strstr(pent->d_name, fn) != NULL ) {
            printf("%s/%s\n", dirname, pent->d_name);
        }
    }
}

int filter_hidden(const struct dirent *entry)
{
    return strncmp(entry->d_name, ".", 1) != 0;
}

int tsort(const struct dirent **a, const struct dirent **b) {
    struct stat astat, bstat;
    if ( sortprop == -1 ) return 0;
    if ( sortprop == PROP_NAME ) return alphasort(a, b);
    stat((*a)->d_name, &astat);
    stat((*b)->d_name, &bstat);
    if ( sortprop == PROP_TIME ) {
        return (astat.st_mtim).tv_sec > (bstat.st_mtim).tv_sec;
    } else if ( sortprop == PROP_SIZE ) {
        return astat.st_size > bstat.st_size;
    }
    return 0;
}

int recursive_tree(const char *dirname, int level) {
    struct dirent **filelist;
    char filed[80];
    int num_files = scandir(dirname, &filelist, filter_hidden, tsort);
    if ( level >= t_depth || num_files < 0 ) return -1;
    for ( int i = 0; i < num_files; i++ ) {
        for ( int j = 0; j < level; j++ ) printf("   ");
        if ( level ) printf("|- ");
        printf("%s\n", filelist[i]->d_name);
        snprintf(filed, sizeof(filed), "%s/%s", dirname, filelist[i]->d_name);
        recursive_tree(filed, level+1);
    }
}

int list_dir() {
    struct dirent **filelist;
    struct stat st;
    char filed[80];
    int num_files = scandir(".", &filelist, filter_hidden, tsort);
    if ( num_files < 0 ) return -1;
    for ( int i = 0; i < num_files; i++ ) {
        printf("%s", filelist[i]->d_name);
        if ( sortprop != -1 ) {
            snprintf(filed, sizeof(filed), "./%s", filelist[i]->d_name);
            stat(filed, &st);
            printf("\tSize: %ld\tLast Modified: %ld", st.st_size, (long)(st.st_mtim).tv_sec);
        }
        printf("\n");
    }
}

void main(){

    int cmd;
    int tokn;
    int readsize;
    FILE *fp;
    char *ptr;
    char *prop;
    char command[100];//to store users command
    char buffer[100]; // text buffer

    while (1) {
        printf("csh> ");
        fgets(command, MAX_INPUT, stdin);
        command[strcspn(command, "\n")] = 0;

        ptr = strtok(command, " ");

        // command ladder to use switch case later
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
            // take in next argument as filename
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
                    recursive_find(".");

            }
        } else {
            sortprop = -1;
            ptr = strtok(NULL, " ");
            if ( cmd == CMD_TREE ) {
                t_depth = ptr == NULL ? 99 : atoi(ptr);
            } else if ( cmd == CMD_LIST ) {
                sortprop = ptr == NULL ? -1 : 0;
            }

            prop = strtok(NULL, " ");
            if ( prop != NULL ) {
                if ( strcmp(prop, "time") == 0 ) {
                    sortprop = PROP_TIME;
                } else if ( strcmp(prop, "size") == 0 ) {
                    sortprop = PROP_SIZE;
                } else {
                    sortprop = PROP_NAME;
                }
            }

            if ( cmd == CMD_TREE ) {
                recursive_tree(".", 0);
            } else if ( cmd == CMD_LIST ) {
                list_dir();
            }
        }
    }//end while
}//end main