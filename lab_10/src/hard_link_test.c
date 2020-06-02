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
#define FILE_NAME_LINK_SUFIX ".link"
int main(int argv,char ** argc){
  pid_t pid;
  int rv;
  int status;
  int file;
  char buf[101];
  char link_path[100];
  link_path[0] = '\0';
  strcat(link_path,argc[1]);
  strcat(link_path,FILE_NAME_LINK_SUFIX);
  link(argc[1],link_path);
  switch(pid=fork()) {
  case -1:
          perror("fork"); /* произошла ошибка */
          exit(1); /*выход из родительского процесса*/
  case 0:
          printf(" CHILD: Это процесс-потомок!\n");
         if(remove(link_path) == 0){
          printf(" CHILD: Жесткая сылка удалена\n");
         }
          exit(rv);
  default:
        file = open(link_path,O_CREAT);
        size_t n;
        while((n = read(file ,buf,100)) > 0){
        buf[n] = '\0';
        scanf("%d",&rv);
        printf("Result: %s \n",buf);
        }
        close(file);
  }
}