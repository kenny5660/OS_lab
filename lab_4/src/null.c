#include <stdio.h>
#include <stdlib.h>

int global;

int main ()
{
    int a = 5;
    int* p = &a;
    printf("a = %d\n ",*p);
    fflush(stdout);
    p = NULL;
    printf("a = %d",*p);
    return 0;
}