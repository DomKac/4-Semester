#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>

int max(const int a, const int b);

int max(const int a, const int b) {
    if (a > b)
        return a;
    return b;
}


static int bottom_up_cut_rod(int p[], int n);

static int bottom_up_cut_rod(int p[], int n) {
    int q = -1;
    int r[n];
    r[0] = 0;
    for (size_t j = 1; j < n; j++)
    {
        q = -1;
        for (size_t i = 1; i <= j; i++)
        {
            q = max(q,p[i]+r[j-i]);
            printf("q = %d\n", q);
            printf("p[%zu] = %d\n", i, p[i]);
            printf("p[%zu] = %d\n", j-i, r[j-i]);

        }
        r[j] = q;
        printf("max do n = %zu wynosi %d\n", j, r[j]);
    }
    return r[n-1];
}

int main(void) {

    int n = 11;
    int p[] = {0,1,5,8,9,10,17,17,20,24,30,};

    int r_n = bottom_up_cut_rod(p,7);
    printf("Odp = %d\n" , r_n);


    return EXIT_SUCCESS;
}
