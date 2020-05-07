#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>


int main(int argv,char ** argc){
    struct stat st;
    stat(argc[1],&st);
    printf("File size: %d\n",st.st_size);
    printf("File blocks: %d\n",st.st_blocks);
    printf("File links: %d\n",st.st_nlink);
    printf("File mode: %d\n",st.st_mode);
}