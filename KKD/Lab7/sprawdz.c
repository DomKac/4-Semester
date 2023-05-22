#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab7.h"

static size_t diff_4bits = 0;
// 01101001
// 01001001

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

void split_check_both(int original, int decoded) {

    char* original_s = (char*)malloc(9);
    char* decoded_s = (char*)malloc(9);

    dec_to_bin(original, original_s);
    dec_to_bin(decoded, decoded_s);
    printf("dlugosc org = %zu\t dlugosc dec = %zu\n", strlen(original_s), strlen(decoded_s));

    for (size_t i = 0; i < 4; i++) { /* sprawdzamy pierwsze 4 bity */
        if (original_s[i] != decoded_s[i]) {
            diff_4bits++;
            break;
        }
    }
    for (size_t i = 4; i < 8; i++) {
        if (original_s[i] != decoded_s[i]) {
            diff_4bits++;
            break;
        }
    }
    free(original_s);
    free(decoded_s);
}

int main(int argc, char* argv[argc+1]) {

    FILE* original_file = fopen(argv[1], "rb+");
    FILE* decoded_file = fopen(argv[2], "rb+");

    int original_byte;
    int decoded_byte;

    while (1) {
        original_byte = fgetc(original_file);
        decoded_byte = fgetc(decoded_file);
        //printf("orignal: %d\tdecoded: %d\n", original_byte, decoded_byte);
        if (original_byte == EOF || decoded_byte == EOF) {
            break;
        }
        if (original_byte != decoded_byte) { /* rożnią się znaki (bajty) */
            split_check_both(original_byte, decoded_byte);
        }
    }
    
    printf("Liczba rozniacych sie 4-bitowych blokow miedzy pierwotnym i odkodowanym plikiem wynosi: %zu\n", diff_4bits);

    fclose(original_file);
    fclose(decoded_file);

    return EXIT_SUCCESS;
}
