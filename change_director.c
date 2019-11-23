#include "header.h"

#define MAX_BUF 256

void change_directory(int argc, char *argv[]){
    char cd_buf[MAX_BUF];

    if(argc < 2){
        fatal("Bad directory. \n");
    }
    memset(cd_buf, 0, MAX_BUF);

    if(getcwd(cd_buf, MAX_BUF) < 0)
        fatal("getcwd");

    printf("before dir : %s\n",cd_buf);

    if(chdir(argv[1]) < 0)
        fatal("chdir");

    memset(cd_buf, 0, MAX_BUF);
    if(getcwd(cd_buf, MAX_BUF) < 0)
        fatal("getcwd");
    printf("after dir : %s\n", cd_buf);
}