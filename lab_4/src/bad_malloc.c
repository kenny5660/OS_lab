#include <stdio.h>
#include <stdlib.h>

int global;

int main ()
{
    int local = 5;
    void *p = malloc(128);
    p = malloc(128);
    ((int*)p)[1] = 100;
    printf("p[1] = %d\n ",((int*)p)[1]);

    free(p);
    return 0;
}