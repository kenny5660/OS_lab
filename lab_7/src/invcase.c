#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>

#define CASE_MASK_8 0x20
#define CASE_MASK_32 0x20202020
#define CASE_MASK_64 0x2020202020202020
#define INVCASE_PARAM_4_CHAR 4 
#define INVCASE_PARAM_8_CHAR 8
#define INVCASE_PARAM_1_CHAR 1

void invcase_8(char* str, size_t size){
  u_int64_t *str_8 = str;
  for(int i = 0; i < size/8; ++i){
    str_8[i] = str_8[i] ^ CASE_MASK_64;
  }
}

void invcase_4(char* str, size_t size){
  u_int32_t *str_4 = str;
  for(int i = 0; i < size/4; ++i){
    str_4[i] = str_4[i] ^ CASE_MASK_32;
  }
}

void invcase_1(char* str, size_t size){
  for(int i = 0; i < size; ++i){
    str[i] = str[i] ^ CASE_MASK_8;
  }
}

void invcase(char* str, size_t size, int param){
  if(param == INVCASE_PARAM_8_CHAR){
    size_t size_div_8 = (size / 8)*8;
    invcase_8 (str,size_div_8);
    invcase_1 (str+size_div_8,size - size_div_8);
  }

  if(param == INVCASE_PARAM_4_CHAR){
    size_t size_div_4 = (size / 4)*4;
    invcase_4 (str,size_div_4);
    invcase_1 (str+size_div_4,size - size_div_4);
  }
  if(param == INVCASE_PARAM_1_CHAR){
    invcase_1 (str,size);
  }
}

u_int64_t duration(struct timeval* start,struct timeval *end){
      u_int64_t end_time_mic = (int64_t) end->tv_sec * 1000000 + end->tv_usec;
      u_int64_t start_time_mic = (int64_t) start->tv_sec * 1000000 + start->tv_usec;
      return end_time_mic - start_time_mic;
}

int main(int argv,char ** argc){

  FILE * ptrFile = fopen(argc[1],"rb");
  if (ptrFile == NULL) perror ("Ошибка открытия файла");
  else
  {
    struct stat st;
    stat(argc[1],&st);
    size_t size_file = st.st_size;
    size_t size_str = size_file + 1;
    char* str = malloc(size_str);
    fread(str,1,size_file,ptrFile);
    str[size_file] = '\0';
    fclose (ptrFile);
    printf("%d\n",size_file);

    struct timeval start_time,end_time;
    gettimeofday(&start_time,NULL);
    invcase(str,size_str,INVCASE_PARAM_1_CHAR);
    gettimeofday(&end_time,NULL);
    u_int64_t dur1 = duration(&start_time,&end_time);
    printf("Time of 1 char: %d\n",duration(&start_time,&end_time));

    gettimeofday(&start_time,NULL);
    invcase(str,size_str,INVCASE_PARAM_4_CHAR);
    gettimeofday(&end_time,NULL);
    u_int64_t dur4 = duration(&start_time,&end_time);
    printf("Time of 4 char: %d (faster then 1: %f times)\n",dur4,(dur1/(double)dur4));

    gettimeofday(&start_time,NULL);
    invcase(str,size_str,INVCASE_PARAM_8_CHAR);
    gettimeofday(&end_time,NULL);
    u_int64_t dur8 = duration(&start_time,&end_time);
    printf("Time of 8 char: %d (faster then 1: %f times)\n",dur8,(dur1/(double)dur8));

  }
  return 0;
}


