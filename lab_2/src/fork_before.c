#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signal.h>
int main()
{
  pid_t pid;
  int rv;
  int x = 100;
  switch(pid=fork()) {
  case -1:
          perror("fork"); /* произошла ошибка */
          exit(1); /*выход из родительского процесса*/
  case 0:
   printf(" CHILD: Это процесс-потомок!\n");
   kill(getppid(),SIGCONT);
   exit(0);
  default:
    raise(SIGSTOP);
    printf("PARENT: Это процесс-родитель!\n");
    exit(0);
  }
}