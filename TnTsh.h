#include <unistd.h>
#define true 1
#define false 0

void init_sh();
void redirection();
int getargs(char *cmd, char **argv);
void eval();
void run();

//void change_directory(int argc, char *argv[])

char buf[256];
char *argv[50];
int narg;
pid_t pid;
int check_cmd;


