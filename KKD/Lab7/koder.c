#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "lab7.h"

static char code[8];
static char binary[8];

static char* numbers[16] = {"0000","0001","0010","0011","0100","0101","0110","0111",
                            "1000","1001","1010","1011","1100","1101","1110","1111",};

static const char G[4][8] = {{'1','1','0','1','0','0','0','1',},
                             {'0','1','1','0','1','0','0','1',},
                             {'0','0','1','1','0','1','0','1',},
                             {'0','0','0','1','1','0','1','1',},};


void dec_to_bin(int n, char* bin)
{
    int x = 0;
    int product = 1; 
    while (n > 0) {
        x = x + ((n%2) * product);
        product *= 10;
        n /= 2;
    }      
    sprintf(bin, "%0*d", 8, x);
}

void hamming(const char* info, char* kod) {
    size_t counter = 0;
    for (size_t k = 0; k < 8; k++) {
        counter = 0;
        for (size_t w = 0; w < 4; w++) { 
            //printf("G[%zu][%zu] = %c, %c * %c\n ", w, k, G[w][k], G[w][k], info[w]);
            if(G[w][k] == '1' && info[w]  == '1')
                counter++;
        }
        //printf("counter = %zu \n", counter);
        if(counter % 2)
            kod[k] = '1'; 
        else
            kod[k] = '0';
    }
}

void decode(const char* kod, char* odkodowana) {
    
    odkodowana[0] = kod[0];
    
    if ((kod[0] == '1' && kod[1] == '1') || (kod[0] == '0' && kod[1] == '0'))
        odkodowana[1] = '0';
    else
        odkodowana[1] = '1';

    odkodowana[2] = kod[5];
    odkodowana[3] = kod[6];
}


unsigned char fromBinary(const char *s) {
  return (unsigned char)strtol(s, NULL, 2);
}

void send_hamming_code_to_file(int sym, FILE *f_out) {

    dec_to_bin(sym,binary); /* w zmiennej binary trzyamy stringa poroju 10001101 którego musimy podzielić na pół i zakodować */
    // printf("liczba binarna z oryginalnego pliku = %s\n", binary);

    char* first_4bits = (char*)malloc(4*sizeof(char)+1);
    char* last_4bits = (char*)malloc(4*sizeof(char)+1);

    for (size_t i = 0; i < 4; i++) {
        first_4bits[i] = binary[i];
        last_4bits[i] = binary[i+4];
    }

    unsigned char dec_num;


    hamming(first_4bits, code);
    //printf("first_4bits = %s\t", first_4bits);
    dec_num = fromBinary(code);
    //printf("first_4bits code = %s\n", code);
    fwrite(&dec_num, sizeof(unsigned char), 1, f_out);

    hamming(last_4bits,code);
    //printf("first_4bits = %s\n", last_4bits);
    dec_num = fromBinary(code);
    //printf("last_4bits code = %s\n", code);

    fwrite(&dec_num, sizeof(unsigned char), 1, f_out);
    
    free(first_4bits);
    free(last_4bits);
}
 

// 1. pobrać liczbę z pliku (8 bitów)
// 2. zamienic na stringa w postaci binarnej
// 3. 
int main(int argc, char* argv[argc+1]) {

    FILE *f_in = freopen(argv[1], "rb", stdin);
    FILE *f_out = fopen(argv[2], "wb");

    int sym;
    while ((sym = getchar()) != EOF) {
        send_hamming_code_to_file(sym, f_out);
    }
    
    for (int i = 1; i < 16; i++) {
        hamming(numbers[i], code);
        // printf("kod dla %s to %s\n",numbers[i], code);

        dec_to_bin(i,binary);
        // printf("%d w binarnym to %s\n", i, binary); 
        puts("");
    }

    fclose(f_in);
    fclose(f_out);

    return EXIT_SUCCESS;
}
