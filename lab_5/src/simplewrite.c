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

int main(int argv,char ** argc){

    struct timeval start_time,end_time;

    gettimeofday(&start_time,NULL);
        int file = creat(FILE_NAME,S_IRWXU);
    gettimeofday(&end_time,NULL);
    printf("Create time: %d\n",duration(&start_time,&end_time));

    void *data = calloc(DATA_SIZE,1);

    gettimeofday(&start_time,NULL);
        write(file,data,DATA_SIZE);
    gettimeofday(&end_time,NULL);
    printf("Write time: %d\n",duration(&start_time,&end_time));

    // gettimeofday(&start_time,NULL);
    //     fflush(file);
    // gettimeofday(&end_time,NULL);
    // printf("fflush time: %d\n",duration(&start_time,&end_time));

    gettimeofday(&start_time,NULL);
        close(file);
    gettimeofday(&end_time,NULL);
    printf("close time: %d\n",duration(&start_time,&end_time));

    gettimeofday(&start_time,NULL);
        remove(FILE_NAME);
    gettimeofday(&end_time,NULL);
    printf("remove time: %d\n",duration(&start_time,&end_time));

  return 0;
}


