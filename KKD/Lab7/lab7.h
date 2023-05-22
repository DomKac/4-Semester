#ifndef LAB7_H
#define LAB7_H

#include <stdlib.h>
#include <stdio.h>


void dec_to_bin(int n, char* binary);
void decode(const char* kod, char* odkodowana);
void hamming(const char* info, char* kod);
unsigned char fromBinary(const char *s);
void decode_correct(char* kod, char* odkodowana);
void send_hamming_code_to_file(int sym, FILE *f_out);
void split_check_both(int original, int decoded);


#endif
