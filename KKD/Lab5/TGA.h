#ifndef TGA_H
#define TGA_H

#include <stddef.h>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <vector>

typedef struct Pixel
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    int centroid_index;     // indeks centroidu do którego należy          
    char pad[4];            // padding 
   
} Pixel;

typedef struct Centroid
{
    long double R;
    long double G;
    long double B;
    std::vector<Pixel> pixel_tab;
    size_t pixel_tab_size;

} Centroid;

/* Prototypy funkcji */
double modulo(double x);
void get_header(FILE* f);
void get_footer(FILE* f, FILE* f_out);

#endif
