#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab7.h"

static size_t double_err_counter = 0;
static char binary[8];

static const char H[4][8] = {{'0','0','1','0','1','1','1','0',},   //
                             {'0','1','0','1','1','1','0','0',},   // 
                             {'1','0','1','1','1','0','0','0',},   //
                             {'1','1','1','1','1','1','1','1',},}; // 


void decode_correct(char* kod, char* odkodowana) {
    //printf("kod na wejsciu: %s\n", kod);
    char korekta[4];
    size_t counter = 0;
    for (size_t w = 0; w < 4; w++) {
        counter = 0;
        for (size_t k = 0; k < 8; k++) {
            if ((kod[k] == '1' && H[w][k] == '1')) {
                counter++;
            }
        }
        if(counter % 2 == 1)
            korekta[w] = '1'; 
        else
            korekta[w] = '0';     
    }
    // for (size_t i = 0; i < 4; i++) {
    //     printf("korekta[%zu] = %c\n", i, korekta[i]);
    // }    
    char first_3bits[3];
    for (size_t i = 0; i < 3; i++) {
        first_3bits[i] = korekta[i];
    }
    size_t err = strtoul(first_3bits, NULL, 2);
    //printf("err = %zu\n", err);
    if (err != 0 && korekta[3] == '1') { /* Mamy jeden błąd ktory wystapił na miejscu o indeksie err */ 
        if(kod[err] == '0') {
            kod[err] = '1';
        }
        else{
            kod[err] = '0';
        }
    }
    else if (err != 0 && korekta[3] == '0') { /* dwa błedy */
        double_err_counter++;
        puts("wiecej niz jeden blad");
    }
    /* pozostałe przypadki kiedy nic nie naprawiamy to 1. prawidłowy kod; 2. dwa błędy, 3. zmieniony bit parzystości */

    
    odkodowana[0] = kod[0];
    if ((kod[0] == '1' && kod[1] == '1') || (kod[0] == '0' && kod[1] == '0'))
        odkodowana[1] = '0';
    else
        odkodowana[1] = '1';

    odkodowana[2] = kod[5];
    odkodowana[3] = kod[6];

    //printf("odkodowana wiadomosc: ");
    // for (size_t i = 0; i < 4; i++) {
    //     printf("%c",odkodowana[i]);
    // }
    // puts("\n");
    
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

void concatenate(char ready[], char* first, char* last);
void concatenate(char ready[], char* first, char* last) { 

    for (size_t i = 0; i < 4; i++) {
        ready[i] = first[i];
        ready[i+4] = last[i];
    }
}



unsigned char fromBinary(const char *s) {
  return (unsigned char)strtol(s, NULL, 2);
}

int main(int argc, char* argv[argc+1]) {

    FILE *f_in = freopen(argv[1], "rb", stdin);
    FILE *f_out = fopen(argv[2], "wb");
    
    int sym, sym2;

    char ready[8];
    char first_4bits[4];
    char last_4bits[4];

    unsigned char x;
    while ((sym = getchar()) != EOF) /* Pobieramy 1 zakodowane 4 bity */
    {
        sym2 = getchar(); /* Pobieramy 2 zakodowane 4 bity */
        dec_to_bin(sym,binary);
        decode_correct(binary,first_4bits);
        dec_to_bin(sym2,binary);
        decode_correct(binary,last_4bits);
        concatenate(ready, first_4bits, last_4bits);
        // printf("first_four_bits: %s\t", first_4bits);
        // printf("last_four_bits: %s\t", last_4bits);
        // printf("ready = %s\n", ready);
        x = fromBinary(ready);
        // printf("x = %hhu\n", x);
        fwrite(&x, sizeof(unsigned char), 1, f_out);
    }

    printf("2 lub wiecej bledow wystapilo %zu razy!\n", double_err_counter);

    fclose(f_in);
    fclose(f_out);

    return EXIT_SUCCESS;
}

