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

#define BUF_SIZE 4000

/*
  Name  : CRC-16/BUYPASS
  Poly  : 0x8005
  Init  : 0x0
  Revert: false
  XorOut: 0x0000
  Check : 0xfee8 ("123456789")
*/
void checksum_CRC_16(u_int16_t* crc,u_int8_t *buf, size_t size) {
    while (size--)
    {
        *crc ^= *buf++ << 8;

        for ( size_t i = 0; i < 8; i++)
            *crc = *crc & 0x8000 ? (*crc << 1) ^ 0x8005 : *crc << 1;
    }
}

u_int16_t checksum_CRC_16_file(char* file_name){
    u_int16_t crc_sum = 0;
    u_int8_t* buf = malloc(BUF_SIZE*sizeof(u_int8_t));
    FILE* file = fopen(file_name,"rb");
    size_t read_size;
    while ((read_size = fread(buf,1,BUF_SIZE,file)) != 0)
    {
        checksum_CRC_16(&crc_sum,buf,read_size);
    }
    fclose(file);
    printf("%s CRC-16/BUYPASS: %x\n",file_name,crc_sum);
}

void checksum_xor_8(u_int8_t* c,u_int8_t *s, size_t size) {
    for(size_t i = 0; i < size; ++i)
        (*c) ^= *s++;
}

u_int16_t checksum_xor_8_file(char* file_name){
    u_int8_t xor_sum = 0;
    u_int8_t* buf = malloc(BUF_SIZE*sizeof(u_int8_t));
    FILE* file = fopen(file_name,"rb");
    size_t read_size;
    while ((read_size = fread(buf,1,BUF_SIZE,file)) != 0)
    {
        checksum_xor_8(&xor_sum,buf,read_size);
    }
    fclose(file);
    printf("%s xor_sum: %x\n",file_name,xor_sum);
}

void checksum_fletcher_16(u_int16_t* s,u_int8_t *buf, size_t size) {
   u_int16_t sum1 = *s & 0xFF00;
   u_int16_t sum2 = *s >>8;
   int index;
   for( int i = 0; i < size; ++i)
   {
      sum1 = (sum1 + buf[i]) % 255;
      sum2 = (sum2 + sum1) % 255;
   }
   *s = (sum2 << 8) | sum1;
}

u_int16_t checksum_fletcher_16_file(char* file_name){
    u_int16_t f_sum = 0;
    u_int8_t* buf = malloc(BUF_SIZE*sizeof(u_int8_t));
    FILE* file = fopen(file_name,"rb");
    size_t read_size;
    while ((read_size = fread(buf,1,BUF_SIZE,file)) != 0)
    {
        checksum_fletcher_16(&f_sum,buf,read_size);
    }
    fclose(file);
    printf("%s fletcher_sum: %x\n",file_name,f_sum);
}


u_int64_t duration(struct timeval* start,struct timeval *end){
      u_int64_t end_time_mic = (int64_t) end->tv_sec * 1000000 + end->tv_usec;
      u_int64_t start_time_mic = (int64_t) start->tv_sec * 1000000 + start->tv_usec;
      return end_time_mic - start_time_mic;
}

int main(int argv,char ** argc){
    struct timeval start_time,end_time;

    gettimeofday(&start_time,NULL);
        checksum_xor_8_file(argc[1]);
    gettimeofday(&end_time,NULL);
    printf("checksum_xor_8 time: %d\n",duration(&start_time,&end_time));

    gettimeofday(&start_time,NULL);
        checksum_fletcher_16_file(argc[1]);
    gettimeofday(&end_time,NULL);
    printf("checksum_fletcher_16 time: %d\n",duration(&start_time,&end_time));

    gettimeofday(&start_time,NULL);
        checksum_CRC_16_file(argc[1]);
    gettimeofday(&end_time,NULL);
    printf("checksum_CRC_16_file time: %d\n",duration(&start_time,&end_time));
}
