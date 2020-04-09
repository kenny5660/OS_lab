#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
int main(int argv,char ** argc){
    if(argv < 2){
        printf("Please enter size in Mb as second param");
        return 0;
    }
    size_t size = ((size_t)atoi(argc[1]))*1024*1024;
    char* data;
    int time_work = 0;
    if(argv > 2){
        time_work = atoi(argc[2]);
    }
    data = ((char*)malloc(size));
    if (data == NULL){
        printf("Allocate %d byte error",size);
        return 0;
    }
    time_t start_time = time(NULL);
    while ((time(NULL) - start_time) < time_work | argv < 3)
    {
        for (int i = 0; i < size; ++i){
            data[i] = i;
        } 
    }
  return 0;
}