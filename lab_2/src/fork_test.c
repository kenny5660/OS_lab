#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
  pid_t pid;
  int rv;
  int status;
  int x = 100;
  switch(pid=fork()) {
  case -1:
          perror("fork"); /* произошла ошибка */
          exit(1); /*выход из родительского процесса*/
  case 0:
          printf(" CHILD: Это процесс-потомок!\n");
          printf(" CHILD: Мой PID -- %d\n", getpid());
          printf(" CHILD: PID моего родителя -- %d\n",getppid());
          printf(" CHILD:x = %d\n",x);
          printf(" CHILD: Введите мой код возврата (как можно меньше):");
          wait(&rv);
          scanf(" %d",&rv);
          printf(" CHILD: Выход! %d\n", rv);
          exit(rv);
  default:
          printf("PARENT: Это процесс-родитель!\n");
          printf("PARENT: Мой PID -- %d\n", getpid());
          printf("PARENT: PID моего потомка %d\n",pid);
          printf("PARENT: Я жду, пока потомок не вызовет exit()...\n");
          printf("PARENT:x = %d\n",x);
          x= 345;
          printf("PARENT:x = %d\n",x);
          waitpid(pid, &status, 0);
          printf("PARENT: Код возврата потомка:%d\n",WEXITSTATUS(status));
          printf("PARENT: Выход!\n");
  }
}