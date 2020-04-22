#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int *p = ((int*)malloc(sizeof(int)*100));
    p[50] = 12;
    free(p);
    printf("p[50] = %d\n ",p[50]);

    return 0;
}