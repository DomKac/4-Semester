#include <stdio.h>
#include <stdlib.h>

int main(void){

    int  a;
    int* b;
    int* c;

    a = 5;
    b = &a;
    printf("a = %d, b = %d\n", a, *b);

    a = 2;
    printf("a = %d, b = %d\n", a, *b);

    c = b;
    printf("a (memory adress) = %p, b = %d, c = %p\n", &a, *b, c);

    return 0;
}
