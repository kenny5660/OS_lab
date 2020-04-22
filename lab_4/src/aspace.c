/* Example code for Think OS.

Copyright 2015 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

int global;

int main ()
{
    int local = 5;
    void *p = malloc(128);
    void *p2 = malloc(128);

    printf ("Address of main is %p\n", main);
    printf ("Address of global is %p\n", &global);
    printf ("Address of local is %p\n", &local);
    printf ("Address of &p is %p\n", &p);
    printf ("Address of &p2 is %p\n", &p2);
    printf ("Address of p is %p\n", p);
    printf ("Address of p2 is %p\n", p2);

    
    return 0;
}