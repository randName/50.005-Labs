#include <stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>

#define MAX_INPUT 256

void main(){

    //variables
    char command[100];//to store users command

    //for create option
    char *create;
    create="create";//be careful about \n

    //for delete
    char *delete;
    delete="delete";//be careful about \n

    //for display
    char *display;
    display="display";//be careful about \n

    //for list
    char *list;
    list="list";//be careful about \n

    char *property;
    property="property";//be careful about \n

    char *propertytime;
    propertytime="property time";//be careful about \n

    char *propertysize;
    propertysize="property size";//be careful about \n

    char *propertyname;
    propertysize="property name";//be careful about \n

    char *find;
    find="find";//be careful about \n

    char *tree;
    tree="tree";//be careful about \n

    char *treetime;
    treetime=" time";//be careful about " " 

    char *treesize;
    treesize=" size";//be careful about " "

    char *treename;
    treename=" name";//be careful about " "

    char *fileName;//to store fileName entered by user
    int ret;//check return value


    //pointers
    char *ptr;
    char *ptrTime;//sorting by time
    char *ptrName;//sorting by name
    char *ptrSize;//sorting by size

    while(1){
        //Q1
        printf("csh>");
        fgets(command,MAX_INPUT,stdin);//take input from user and save it in command
        printf("command %s\n",command);

    //Create, Case #1
        ptr=strstr(command,create);
        if(ptr!=NULL)
        {
            //Implement your code to handle create here
        }

    //--------------------------------------------------------------------
    //Delete, Case #2
        ptr=strstr(command,delete);
        if(ptr!=NULL)
        {
            //Implement your code to handle detele here
        }

    //--------------------------------------------------------------------
    //Display, Case #3
        ptr=strstr(command,display);
        if(ptr!=NULL)
        {
        //Implement your code to handle display here


        }


    //--------------------------------------------------------------------
    //list, Case #4
        ptr=strstr(command,list);
        if(ptr!=NULL)
        {
        //Implement your code to handle list here

        /*There are many cases to handle in this part*/

        /*
        //list
        //list 1
        //list 1 property
        //list property time
        //list property size
        //etc..
        */
        }

    //--------------------------------------------------------------------
    //Find, Case #5
        ptr=strstr(command,find);
        if(ptr!=NULL)
        {
        //Implement your code to handle find here
        }
    //--------------------------------------------------------------------
    //tree Case #6
        ptr=strstr(command,tree);
        if(ptr!=NULL)
        {
        //Implement your code to handle tree here
        /*There are many cases to handle in this part*/

        /*
        //tree
        //tree 1 
        //tree 1 time
        //tree size
        //tree name
        //etc..
        */
        }
    //--------------------------------------------------------------------
    //Wrong command, Case #7
            /*	
            printf("You entered wrong command\n");
        
            */


    }//end while
}//end main