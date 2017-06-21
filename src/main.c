#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <memory.h>
#include "check.h"

int main() {
    printf("%d\n",check_end());
    char buf[1024] = {};
    int fd,n,val;
    fd = open("test",O_RDWR);
    if((val = fcntl(fd,F_GETFL)) < 0){
        perror("fcntl error test");
        exit(EXIT_FAILURE);
    }

    struct stat st; //定义文件信息结构体
    int r=fstat(fd,&st);
    if(r < 0){
        printf("获取文件大小失败:%m\n");
        close(fd);
        exit(-1);
    }

    char* p = mmap(NULL,st.st_size,PROT_READ,MAP_PRIVATE,fd,0);
    if(p == NULL || p == MAP_FAILED){
        perror("mmap error");
        exit(EXIT_FAILURE);
    }
    char* result = malloc(st.st_size);
    memcpy(result,p,st.st_size);
    printf("%s\n",result);
    munmap(fd,st.st_size);

    switch(val & O_ACCMODE){
        case O_RDONLY:
            printf("read only");
            break;
        case O_WRONLY:
            printf("write only");
            break;
        case O_RDWR:
            printf("read write");
            break;
        default:
            perror("invalid access mode!");
            exit(EXIT_FAILURE);
    }
    printf("\n");

    if(fd < 0){
        perror("open test");
        exit(EXIT_FAILURE);
    }

    while(1){
        n = read(fd,buf,1024);

        if(n <= 0)
            break;

        printf("%s");
    }
    close(fd);
    return 0;
}