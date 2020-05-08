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
#include <string.h>

#define BUF_SIZE 30
#define FILE_NAME_CSUM_SUFIX  ".csum"
/*
  Name  : CRC-8
  Poly  : 0x7
  Init  : 0x0
  Revert: false
  XorOut: 0x0000
  Check : 0xF4 ("123456789")
*/
void checksum_CRC_8(u_int8_t* crc,u_int8_t *buf, size_t size) {
    while (size--)
    {
        *crc ^= *buf++;

        for ( size_t i = 0; i < 8; i++)
            *crc = *crc & 0x80 ? (*crc << 1) ^ 0x07 : *crc << 1;
    }
}


int main(int argv,char ** argc){


u_int8_t crc_from_file = 0;
u_int8_t* buf = malloc(BUF_SIZE*sizeof(u_int8_t));
    FILE* file = fopen(argc[1],"rb");
    FILE* file_csum = fopen(argc[2],"rb");
    size_t read_size;
    while ((read_size = fread(buf,1,BUF_SIZE,file)) != 0)
    {
        u_int8_t crc = 0;
        checksum_CRC_8(&crc,buf,read_size);
        fread(&crc_from_file,1,1,file_csum);
        if(crc_from_file != crc){
            printf("Error check crc.\n");
            return 0;
        }
    }
    fclose(file);
    fclose(file_csum);
    printf("Verification completed\n");
}
