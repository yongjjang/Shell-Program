/* handlesignal.c */
/* sigaction example */
#ifndef __DD_H__
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#endif
void handlerInt(int signo)
{
    printf("CTRL + c 입력!! -> SIGINT 실행\n");
    pid_t ppid = getppid();
    kill(ppid, SIGINT);
}

void handlerQuit(int signo){
    printf("CTRL + z 입력!! -> SIGQUIT 실행\nQuit (core dumped)");
    pid_t ppid = getppid();
    kill(ppid, SIGQUIT);
}

void sig_int(){
    struct sigaction sig_int;

    // signal int
    sig_int.sa_handler = handlerInt; // callback function
    sigfillset(&(sig_int.sa_mask)); // 모든 시그널을 포함하는 집합 생성
    sigaction(SIGINT, &sig_int, NULL);// sigInt
}

void sig_quit(){
    struct sigaction sig_quit;

    // signal quit
    sig_quit.sa_handler = handlerQuit;
    sigfillset(&(sig_quit.sa_mask));
    sigaction(SIGTSTP, &sig_quit, NULL);
}
