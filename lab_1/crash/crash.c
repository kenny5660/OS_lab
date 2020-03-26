#include <stdio.h>
void main(){
    int num  = 123;
    int* ptr = 0;
    int num2 = *ptr;
    printf("All OK %d",num2);
}