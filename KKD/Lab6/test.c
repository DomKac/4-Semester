#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>
#include "TGA.h"

void make_kwantyzator_r2(size_t n, int kwant[], size_t elements) {
    int k = elements/n;
    kwant[(n/2)] = k/2;
    for (size_t i = (n/2)+1; i < n; i++) {
        kwant[i] = kwant[i-1]+k;
    }
    for (size_t i = 0; i < n/2; i++) {
        kwant[i] = -(kwant[n-1-i]);
    }   
}




int main(void)
{
    double x = 2.5;
    unsigned char y;

    y = (unsigned char)(round(x));
    printf("%hhu\n", y);
    size_t n = 128;
    int kwant[n];
    make_kwantyzator_r2(n,kwant,512);
    for (size_t i = 0; i < n; i++)
    {
        printf("kwantyzator[%lu] = %d\n", i, kwant[i]);
    } 

    Pixel_f p = {.R = 2.4, .G = 4.9, .B = 1.1};
    Pixel_f p2 = p;

    printf("p2.R = %lf\tp2.G = %lf\tp2.B = %lf\n", p2.R, p2.G, p2.B);
    double z = y / x;
    printf("%lf\n", z);

    return EXIT_SUCCESS;
}
