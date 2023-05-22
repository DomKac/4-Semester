#ifndef TGA_H
#define TGA_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

typedef struct Pixel
{
    unsigned char R;
    unsigned char G;
    unsigned char B;          
    char pad[5];            // padding 
   
} Pixel;

typedef struct Pixel_f
{
    double R;
    double G;
    double B;

} Pixel_f;

typedef struct Pixel_c
{
    char R;
    char G;
    char B;          
    char pad[5];            // padding 
   
} Pixel_c;



/* Prototypy funkcji */
void get_header(void);
void get_footer(FILE* f_out);
void write_header(FILE* f_out);
void jpeg(size_t x, size_t y, Pixel pixel[x][y], Pixel_f avg[x][y], Pixel_f dev[x][y]);
void fill_avg_dev(size_t x, size_t y, Pixel_f avg[x][y], Pixel_f dev[x][y], size_t i, size_t j, Pixel curr, Pixel prev);
void make_kwantyzator_r(size_t n, char kwant[]);
void substract_RGB(size_t h, size_t w, Pixel_f roznica[h][w], Pixel_f odjemna[h][w], Pixel_f odjemnik[h][w], size_t i, size_t j, size_t i_p, size_t j_p);

#endif

/* Kompilacja */
/* clang -Weverything -ggdb3 testy.c -o t */

/* Uruchomienie */
/* valgrind --leak-check=full ./t */  
