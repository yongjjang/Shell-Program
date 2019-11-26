/* handlesignal.c */
/* sigaction example */
#include "header.h"
#include <signal.h>
void handler_int(int signo){
    printf("\nCTRL + c 입력!! -> SIGINT 실행\n");
    pid_t ppid = getppid();
    kill(ppid, SIGINT);
}

void handler_quit(int signo){
    printf("\nCTRL + z 입력!! -> SIGQUIT 실행\nQuit (core dumped)\n");
    pid_t ppid = getppid();
    kill(ppid, SIGQUIT);
}

void sig_int(){
    struct sigaction sig_int;

    // signal int
    sig_int.sa_handler = handler_int; // callback function
    sigfillset(&(sig_int.sa_mask)); // 모든 시그널을 포함하는 집합 생성
    sigaction(SIGINT, &sig_int, NULL);// sigInt
}

void sig_quit(){
    struct sigaction sig_quit;

    // signal quit
    sig_quit.sa_handler = handler_quit;
    sigfillset(&(sig_quit.sa_mask));
    sigaction(SIGTSTP, &sig_quit, NULL);
}
