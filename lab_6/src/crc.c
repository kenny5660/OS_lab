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


int main(int argv,char ** argc){

u_int16_t crc_sum = 0;
u_int8_t* buf = malloc(BUF_SIZE*sizeof(u_int8_t));
for (int i = 1; i < argv;++i){
    FILE* file = fopen(argc[i],"rb");

    size_t read_size;
    while ((read_size = fread(buf,1,BUF_SIZE,file)) != 0)
    {
        checksum_CRC_16(&crc_sum,buf,read_size);
    }
    fclose(file);
    printf("%s CRC-16/BUYPASS: %x\n",argc[i],crc_sum);
}
}
