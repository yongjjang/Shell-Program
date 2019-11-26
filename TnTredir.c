#include "TnTsh.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// < file    // 파일로부터 표준 입력을 받는다.
void redirect_in(char **argv){
    int i;
    int fd;

    for(i=0; argv[i] != NULL; i++){
        if(!strcmp(argv[i], "<"))
            break;
    }

    if(argv[i]){
        if(!argv[i+1]){
            return -1;
        }
        else{
            if((fd = open(argv[i+1], O_RDONLY)) == -1){
                perror(argv[i+1]);
                return -1;
            }
        }
        
        dup2(fd, STDIN_FILENO);
        close(fd);

        for(i=i; argv[i] != NULL; i++){
            argv[i] = argv[i+2];
        }

        argv[i] = NULL;
    }
}

// redir >   // 파일 전체를 새로 저장
void redirect_out(char **argv){
    int i;
    int fd;

    for(i=0; argv[i] != NULL; i++){
        if(!strcmp(argv[i], ">"))
            break;
    }

    if(argv[i]){
        if(!argv[i+1]){
            return -1;
        }
        else{
            if((fd = open(argv[i+1], O_RDWR | O_CREAT| S_IRUSR, 0644)) == -1){
                perror(argv[i+1]);
                return -1;
            }
        }
        
        dup2(fd, STDOUT_FILENO);
        close(fd);
        argv[i] = NULL;
        argv[i+1] = NULL;
        for(i=i; argv[i] != NULL; i++){
            argv[i] = argv[i+2];
        }

        argv[i] = NULL;
    }
}

// redir >>  // 파일 끝에 덧붙임
void redirect_append(char **argv){
    int i;
    int fd;

    for(i=0; argv[i] != NULL; i++){
        if(!strcmp(argv[i], ">>"))
            break;
    }

    if(argv[i]){
        if(!argv[i+1]){
            return -1;
        }
        else{
            if((fd = open(argv[i+1], O_RDWR | O_APPEND | O_CREAT, 0644)) == -1){
                perror(argv[i+1]);
                return -1;
            }
        }
        
        dup2(fd, STDOUT_FILENO);
        close(fd);
        argv[i] = NULL;
        argv[i+1] = NULL;
        for(i=i; argv[i] != NULL; i++){
            argv[i] = argv[i+2];
        }

        argv[i] = NULL;
    }
}
void pipe_tnt(char **argv){
    int i;
    int k = 0;
    pid_t pid1, pid2;
    int fd[2];
    char cmdvectorPipe1[50], cmdvectorPipe2[50];

    for(i=0; argv[i] != NULL; i++){
        if(!strcmp(argv[i], "|")){
            cmdvectorPipe1[i] = NULL;
            break;
        }
        cmdvectorPipe1[i] = argv[i];
    }
    for(i=i+1; argv[i] != NULL; i++){
        cmdvectorPipe2[k] = argv[i];
        k++;
    }

    pipe(fd);
    
    pid1 = fork();
    switch(pid1){
        case -1: perror("fork error"); break;
        case 0:
            redirect_in(cmdvectorPipe1);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            close(fd[0]);
            execvp(cmdvectorPipe1[0], cmdvectorPipe1);
            exit(0);
    }
}
