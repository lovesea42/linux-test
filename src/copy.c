//
// Created by parallels on 6/22/17.
//

#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "copy.h"

#define COPY_CLINET_BUFF_SIZE   1024
#define COPY_FILE_BUFF_SIZE     1024


/* ----------------------------------------------------------------------------
 * copy file by shell command
 * ------------------------------------------------------------------------- */

/* this is a command to copy file
 * */
void cliCopyFile(){
    ssize_t size;
    char cmd[COPY_CLINET_BUFF_SIZE] = {};
    while(1){
        printf("please input the filename to copy,quit to leave!\n");
        size = read(STDIN_FILENO,cmd,COPY_CLINET_BUFF_SIZE);

        if(size <= 0)
            continue;
        int n = strlen(cmd);
        cmd[n-1] = '\0';

        if (strcmp(cmd, "quit") == 0){
            exit(EXIT_SUCCESS);
        }else
            copyFile(cmd);
    }
}


/* copy file by finename,new file will be created by the name of filename+ "_copy"
 * */
void copyFile(char* filename){
    char buf[COPY_FILE_BUFF_SIZE];

    int src = open(filename,O_RDONLY);
    if(src < 0){
        perror("open src file error!");
        return;
    }

    char str[100];
    strcpy(str,filename);

    int des = open(strcat(str,"_copy"),O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
    if(des < 0){
        close(src);
        perror("open des file error!");
        return;
    }

    int real,all = 0;
    while((real = read(src,buf,COPY_FILE_BUFF_SIZE)) > 0){
        write(des,buf,real);
        all+=real;
    }

    close(des);
    close(src);

    printf("read completed! %d bytes is done!\n",all);
}