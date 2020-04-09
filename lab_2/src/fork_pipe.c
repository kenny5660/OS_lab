#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signal.h>
int main()
{
  pid_t pid_1,pid_2;
  int rv;
  int x = 100;
  int status;
  int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

  switch(pid_1=fork()) {
  case -1:
          perror("fork");
          exit(1);
  case 0:
   close(pipefd[0]);
   dup2(pipefd[1], STDOUT_FILENO);
   const char* message = "Child_1 with pid=%d write to stdout\n";
   printf(message,getpid());
   close(pipefd[1]);
   exit(EXIT_SUCCESS);
  default:
    switch(pid_2=fork()) {
      case -1:
          perror("fork");
          exit(1);
      case 0:
        close(pipefd[1]);
        printf("Child_2: wait str from Child_1\n");
        dup2(pipefd[0], STDIN_FILENO);
        char* buf;
        size_t size = 0;
        getline (&buf, &size, stdin);
        printf("Child_2: Child_1 send me str %s\n",buf);
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
      default:
      waitpid(pid_1, &status, 0);
      waitpid(pid_2, &status, 0);
    }
  }
}