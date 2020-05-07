#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DATA_SIZE 300000
#define FILE_NAME "simplewrite.bin"

u_int64_t duration(struct timeval* start,struct timeval *end){
      u_int64_t end_time_mic = (int64_t) end->tv_sec * 1000000 + end->tv_usec;
      u_int64_t start_time_mic = (int64_t) start->tv_sec * 1000000 + start->tv_usec;
      return end_time_mic - start_time_mic;
}

void posix_write(){
    int file = creat(FILE_NAME,S_IRWXU);
    char data = 22;
    for(int i = 0; i < DATA_SIZE;++i){
        write(file,&data,1);
    }
    close(file);
    remove(FILE_NAME);
}

void stdio_write(){
    FILE * file = fopen(FILE_NAME,"w");
    char data = 22;
    for(int i = 0; i < DATA_SIZE;++i){
        fwrite(&data,1,1,file);
    }
    fflush(file);
    fclose(file);
    remove(FILE_NAME);
}


int main(int argv,char ** argc){

    struct timeval start_time,end_time;

    gettimeofday(&start_time,NULL);
        posix_write();
    gettimeofday(&end_time,NULL);
    printf("posix_write time: %d\n",duration(&start_time,&end_time));

    gettimeofday(&start_time,NULL);
        stdio_write();
    gettimeofday(&end_time,NULL);
    printf("stdio_write time: %d\n",duration(&start_time,&end_time));
  return 0;
}


