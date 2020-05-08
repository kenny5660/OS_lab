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

#define BUF_SIZE 30

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


int main(int argv,char ** argc){

u_int16_t sum = 0;
u_int8_t* buf = malloc(BUF_SIZE*sizeof(u_int8_t));
for (int i = 1; i < argv;++i){
    FILE* file = fopen(argc[i],"rb");

    size_t read_size;
    while ((read_size = fread(buf,1,BUF_SIZE,file)) != 0)
    {
        checksum_fletcher_16(&sum,buf,read_size);
    }
    fclose(file);
    printf("%s fletcher sum: %x\n",argc[i],sum);
}
}
