#include "header.h"

void fatal(char *errlog){
    perror(errlog);
    exit(1);
}