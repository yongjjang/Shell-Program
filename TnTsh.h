#include <unistd.h>

void init_sh();
void redirection();
int getargs(char *cmd, char *argv[]);
void eval();
void run();
void change_directory(int argc, char *argv);

#define BUF_SIZE 256

char buf[BUF_SIZE];
char *argv[50];
int narg, status;
pid_t pid;
char pwd[BUF_SIZE];
int IS_BACKGROUND = 0;
