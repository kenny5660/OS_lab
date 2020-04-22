#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int *p = ((int*)malloc(sizeof(int)*100));
    p[100] = 0;
    printf("p[100] = %d\n ",p[100]);
    free(p);
    return 0;
}