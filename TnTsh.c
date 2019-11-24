#include "TnTsh.h"
#include "header.h"
#include<signal.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

void handler_quit(int signo);
void sig_quit();
void redirect_in(char **argv);

void init_sh(){
  printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNdddmNMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMNdhyhmMMMNho+osso/ohMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMNs/+////+oy++yNMMMMms/sMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMNy//+osso//+//dMMMMMMMMo/dMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMNy+/::/oyyy+++/++dMMMMMMN+/mMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMNy//://///+syyyy+:++MMMMMho+yMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMNs//:///:::://+osss/++MMMdo+smMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMNs/::///::::::::://///sNMho+smMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMNs/::://::::::::::::::omMdo+smMMNMMMMMNMMMMMMMMM\nMMMMMMMMMMNs/::://::::::::::::::smMho+smMMMMNmNMNmNMMMMMMMMM\nMMMMMMMMNs/:::///:::::::::::::smMMs+smMNNNNNN****mNNNNNMMMMM\nMMMMMMNs/::://:::::::::--:::smMMMh+oMMMMM****ysssy**NMMMMMMM\nMMMMMMy::://::::::::::::::smMMMMMd++MMMMMM**yyss**hmNMMMMMMM\nMMMMMMy://:::::::::::///smMMMMMMMMs/odNNNm**oyy**mNmNNNMMMMM\nMMMMMMN+::::::::::-::/smMMMMMMMMMMMdyo+++++sddNNmmNMMMMMMMMM\nMMMMMMMNy/::::::::::smMMMMMMMMMMMMMMMMNNNNMMNMMMMNNMMMMMMMMM\nMMMMMMMMMNy+::::::smMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMNmdddNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\nMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n\n");
  printf("Welcome To TnT Shell!! \n");
}

void redirection(){

}

void eval(){

}

int getargs(char *cmd, char **argv){
  int narg = 0;

  while (*cmd){
    if(*cmd == ' ' || *cmd == '\t')
      *cmd++ = '\0';
    else{
      argv[narg++] = cmd++;
      while(*cmd != '\0' && *cmd != ' ' && *cmd != '\t') cmd ++;
    }

    if(strcmp("exit", argv[0]) == 0){
      printf("\n\nTnT Shell is Die TnT,,,\n");
      exit(1);
    }

    //if(strcmp("cd", argv[0]) == 0)
   //   change_directory(narg, argv);
  }
  
    
  argv[narg] = NULL;
  return narg;

}

void run(){
  while(1){
    signal(SIGQUIT,SIG_IGN);
    signal(SIGINT,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    getcwd(pwd,BUF_SIZE);
    printf("%s$ ", pwd);
    gets(buf);
    narg = getargs(buf, argv);

    pid = fork();

    if (pid == 0){
      signal(SIGINT,SIG_DFL);
      //signal(SIGTSTP,SIG_DFL);
      sig_quit();
      redirect_in(argv);
      redirect_out(argv);
      redirect_append(argv);
      execvp(argv[0], argv);
      exit(1);
    }
    else if(pid > 0){
      wait((int *) 0);
    }
    else
      perror("fork failed");
  }
}

void main(){
  init_sh();
  run();
}

void handler_quit(int signo){
    printf("CTRL + z 입력!! -> SIGQUIT 실행\nQuit (core dumped)");
    pid_t ppid = getppid();
    kill(ppid, SIGQUIT);
}

void sig_quit(){
    struct sigaction sig_quit;

    // signal quit
    sig_quit.sa_handler = handler_quit;
    sigfillset(&(sig_quit.sa_mask));
    sigaction(SIGTSTP, &sig_quit, NULL);
}
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
//void pipe_tnt(char **argv){
//    int i;
//    int k = 0;
//    pid_t pid1, pid2;
//    int fd[2];
//    int status1, status2
//
//    for(i=0; argv[i] != NULL; i++){
//        if(!strcmp(cmd[i], "|")){
//            cmdvectorPipe1[i] = NULL;
//            break;
//        }
//        cmdvectorPipe1[i] = argv[i];
//    }
//    for(i=i+1; cmdvector[i] != NU:\LL; i++){
//        cmdvectorPipe2[i] = argv[i];
//        k++;
//    }
//
//    pipe(fd)
//    
//    pid1 = fork();
//    switch(pid1){
//        case -1: perror("fork error"); break
//
//
//}
