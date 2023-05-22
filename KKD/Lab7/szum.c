#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lab7.h"

unsigned char fromBinary(const char *s) {
  return (unsigned char)strtol(s, NULL, 2);
}

void dec_to_bin(int n, char* bin) {
    int x = 0;
    int product = 1; 
    while (n > 0) {
        x = x + ((n%2) * product);
        product *= 10;
        n /= 2;
    }      
    sprintf(bin, "%0*d", 8, x);
}


int main(int argc, char* argv[argc+1]) {

    srand(time(NULL));
    FILE *f_in = freopen(argv[1], "rb", stdin);
    FILE *f_out = fopen(argv[2], "wb");
    const size_t p = 1;
    // printf("p = %zu\n", p ); 

    
    char binary[8];
    int sym;
    size_t r;
    unsigned char x;
    // printf("p = %zu\n", p );
    while ((sym = getchar()) != EOF) {
        // printf("p = %zu\n", p );
        dec_to_bin(sym,binary);
        // printf("p = %zu\n", p );

        // printf("binary: %s\n", binary);
        for (size_t i = 0; i < 8; i++) {
            r = (size_t)rand() % 100;
            // printf("r = %zu\n", r);
            if (p > r) { //p > r
                // printf("szumie!\n");
                if(binary[i] == '0')
                    binary[i] = '1';
                else
                    binary[i] = '0';
            }
        }
        // printf("zaszumiony binary: %s\n", binary);
        x = fromBinary(binary);
        // printf("x = %hhu\n",x);
        fwrite(&x, sizeof(unsigned char), 1, f_out);
    
    }
    // printf("p = %zu\n", p );


    fclose(f_in);
    fclose(f_out);

    return EXIT_SUCCESS;
}
