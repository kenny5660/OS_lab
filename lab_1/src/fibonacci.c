#include "fibonacci.h"
int get_fibonacci_number(int num){
    if(num < 1){
        return 0;
    }
    if(num == 1){
        return 1;
    }
    return get_fibonacci_number(num-1) + get_fibonacci_number(num - 2);
}