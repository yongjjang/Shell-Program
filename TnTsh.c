#include "TnTsh.h"
#include "header.h"

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

    if(strcmp("cd", argv[0]) == 0){
      cmd_check = true;
    }
    else if(strcmp("exit", argv[0]) == 0){
      printf("\n\nTnT Shell is Die TnT,,,\n");
      exit(1);
    }
    argv[narg] = NULL;
    return narg;
  }
}

void run(){
  while(1){
    cmd_check = false;
    printf("%s $", getenv("PWD"));
    gets(buf);
    narg = getargs(buf, argv);

    if(cmd_check){
      pid = fork();

      if (pid == 0){
	execvp(argv[0], argv);

      }
      else if(pid > 0){
	//sig_int();
	//sig_quit();
	wait((int *) 0);
      }
      else
	perror("fork failed");
    }
  }

}
void main(){
  init_sh();
  run();
}
