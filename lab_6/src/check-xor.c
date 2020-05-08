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

void checksum_xor_8(u_int8_t* c,u_int8_t *s, size_t size) {
    for(size_t i = 0; i < size; ++i)
        (*c) ^= *s++;
}


int main(int argv,char ** argc){

u_int8_t sum_xor = 0;
u_int8_t* buf = malloc(BUF_SIZE*sizeof(u_int8_t));
for (int i = 1; i < argv;++i){
    FILE* file = fopen(argc[i],"rb");

    size_t read_size;
    while ((read_size = fread(buf,1,BUF_SIZE,file)) != 0)
    {
        checksum_xor_8(&sum_xor,buf,read_size);
    }
    fclose(file);
    printf("%s xor sum: %x\n",argc[i],sum_xor);
}
}
