#include "header.h"

void change_directory(int narg, char *argv[]){
  if(narg > 2){
    printf("Too many argments\n");
  }
  if(narg == 2){
    if(chdir(argv[1]) == 0);
    else perror(NULL);
  }
}

