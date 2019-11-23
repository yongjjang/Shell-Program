#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void init_sh();
void redirection();
int getargs(char *cmd, char **argv);
void eval();
void run();

char buf[256];
char *argv[50];
int narg;
pid_t pid;




