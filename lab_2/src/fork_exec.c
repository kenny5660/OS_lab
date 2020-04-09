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
  char* args[] = { "/bin/ls",  NULL };
  switch(pid=fork()) {
  case -1:
          perror("fork"); /* произошла ошибка */
          exit(1); /*выход из родительского процесса*/
  case 0:

    execv("/bin/ls", args);
    exit(0);
  default:
  printf("Parent\n");
  wait(&rv);
  }
}