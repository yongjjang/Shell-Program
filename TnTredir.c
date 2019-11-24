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
        if(!cmd[i+1]){
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

// redir >>  // 파일 끝에 덧붙임
void redirect_append(){

}

// redir >   // 파일 전체를 새로 저장
void redirect_out(char *cmd){
    int fd; 
    char *buf = "This is a test output file.\n";
    int flags = O_WRONLY | O_CREAT | O_TRUNC;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; /* == 0644 */

    if (argc < 2) {
        fprintf(stderr, "Usage: file_output filename\n");
        exit(1);
    }
    if ( (fd = open(argv[1], flags, mode)) == -1 ) {
        perror("open"); /* errno에 대응하는 메시지 출력됨*/
        exit(1);
    }
    if ( dup2(fd, 1) == -1 ) {
        perror("dup2"); /* errno에 대응하는 메시지 출력됨 */
        exit(1);
    }
    if ( close(fd) == -1 ) {
        perror("close"); //errno에 대응하는 메시지 출력됨
        exit(1);
    }

    write(1, buf, strlen(buf));
    exit(0);
}

int main(int argc, char *argv[])
{

    return 0;
}
