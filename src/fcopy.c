//
// Created by parallels on 6/23/17.
//

#include "fcopy.h"
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#define COPY_CLINET_BUFF_SIZE   1024
#define COPY_FILE_BUFF_SIZE     1024


/* ----------------------------------------------------------------------------
 * copy file by shell command
 * ------------------------------------------------------------------------- */

/* this is a command to copy file
 * */
void fcliCopyFile(){

    char buf[COPY_CLINET_BUFF_SIZE];

    printf("please input the filename to copy,quit to leave!\n");
    while(fgets(buf,COPY_CLINET_BUFF_SIZE,stdin) != NULL){
        int len = strlen(buf);
        buf[len-1] = '\0';
        if (strcmp(buf, "quit") == 0){
            exit(EXIT_SUCCESS);
        }else
            fcopyFile(buf);
    }

}


/* copy file by finename,new file will be created by the name of filename+ "_copy"
 * */
void fcopyFile(char* filename){
    //verify file
    struct stat state;
    if(lstat(filename,&state) < 0){
        perror("error to lstat file");
        return;
    }

    if(!S_ISREG(state.st_mode)){
        printf("not a regular file!");
        return;
    }

    char buf[COPY_FILE_BUFF_SIZE];

    FILE* src = fopen(filename,"r");
    if(src == NULL){
        perror("open src file error!");
        return;
    }

    char str[100];
    strcpy(str,filename);

    FILE* des = fopen(strcat(str,"_copy"),"w");
    if(des == NULL){
        fclose(src);
        perror("open des file error!");
        return;
    }

    int real,all = 0;
    while((real = fread(buf,sizeof(char),COPY_FILE_BUFF_SIZE,src))){
        fwrite(buf,sizeof(char),real,des);
        all+=real;
        if(real != COPY_FILE_BUFF_SIZE)
            break;
    }

    fclose(des);
    fclose(src);

    printf("read completed! %d bytes is done!\n",all);
}