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

int main(int argv,char ** argc){
    int max_rows = 10;
    if (argc[1][0] == '-' && argc[1][1] == 'n'){
        if(argc[1][2] == '\0'){
            max_rows = atoi(argc[2]);
        }
        else{
            max_rows = atoi((argc[1]+2));
        }
    }
    int file = open(argc[argv-1],NULL);
    if(file == -1){
        printf("Error: file not exist");
    }
    else{
        int j_poss = 0;
        char* buf = malloc(BUF_SIZE);
        int n_read = BUF_SIZE;
        int file_size = lseek(file,0,SEEK_END);
        int file_pos = lseek(file,-BUF_SIZE,SEEK_END);
        int block_start_pos = 0;
        int read_size = BUF_SIZE;
        while(j_poss < max_rows && n_read == BUF_SIZE){
            n_read = read(file,buf,read_size);
            for(int i = n_read; i >=0; --i){
                    if(buf[i] == '\n'){
                        block_start_pos = file_pos + i;
                        ++j_poss;
                        if(j_poss == max_rows){
                            break;
                        }
                    }
            }
            if(file_pos == 0){
                break;
            }
            file_pos = lseek(file,-(BUF_SIZE*2),SEEK_CUR);
            if(file_pos == -1){
                read_size = file_pos;
                file_pos = lseek(file,0,SEEK_SET);
            }

        }
            if(file_pos == 0 && j_poss < max_rows){
                block_start_pos = 0;
            }
            lseek(file,block_start_pos,SEEK_SET);
            int out_block_size = file_size-block_start_pos;
            char* buf_2 = malloc(out_block_size+1);
            size_t n_r = read(file,buf_2,out_block_size);
            buf_2[out_block_size] = '\0';
            printf("%s\n",buf_2);
            fflush(stdout);
    }
  return 0;
}
