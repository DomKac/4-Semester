#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "TGA.h"

void make_kwantyzator_r(size_t n, char kwant[]) {
    int k = 256/n;
    kwant[(n/2)] = k/2;
    for (size_t i = (n/2)+1; i < n; i++) {
        kwant[i] = kwant[i-1]+k;
    }
    for (size_t i = 0; i < n/2; i++) {
        kwant[i] = -(kwant[n-1-i]);
    }   
}



void substract_RGB(size_t h, size_t w, Pixel_f roznica[h][w], Pixel_f odjemna[h][w], Pixel_f odjemnik[h][w], size_t i, size_t j, size_t i_p, size_t j_p) {
    
    roznica[i][j].R = (odjemna[i][j].R - odjemnik[i_p][j_p].R)/2.0;
    roznica[i][j].G = (odjemna[i][j].G - odjemnik[i_p][j_p].G)/2.0;
    roznica[i][j].B = (odjemna[i][j].B - odjemnik[i_p][j_p].B)/2.0; // test
    
}
// (x(n-2) + x(n-1))/2 - (x(n-1) + x(n))/2 = ( x(n-2) - x(n) ) / 2 -> zakres chara!

Pixel_c diff_after_q(const char kwant[], const size_t n, const Pixel_f dif) {

    Pixel_c pix;
    char r,g,b;
    size_t nearest_R = 513;
    size_t nearest_G = 513;
    size_t nearest_B = 513;
    size_t dist_R = 513;
    size_t dist_G = 513;
    size_t dist_B = 513;
    for (size_t i = 0; i < n; i++)
    {
        dist_R = fabs(dif.R - kwant[i]);
        dist_G = fabs(dif.G - kwant[i]);
        dist_B = fabs(dif.B - kwant[i]);
        if (dist_R < nearest_R){
            nearest_R = dist_R;
            pix.R = kwant[i];
        }
        if (dist_G < nearest_G){
            nearest_G = dist_G;
            pix.G = kwant[i];
        }
        if (dist_B < nearest_R){
            nearest_B = dist_B;
            pix.B = kwant[i];
        }
    }
    return pix;
}

void kodowanie_roznicowe(size_t h, size_t w, Pixel_f avg[h][w], const char kwant[], size_t n, Pixel_c skwantyzowane[h][w]) {
    Pixel_f diff[h][w];
    diff[0][0] = avg[0][0];
    skwantyzowane[0][0].R = (char)(avg[0][0].R);
    skwantyzowane[0][0].G = (char)(avg[0][0].G);
    skwantyzowane[0][0].B = (char)(avg[0][0].B);
    size_t i = 0, j = 0;
    
    while (!(i == (h-1) && j == (w-1)))
    {
        if (j < w-1 && (i == 0 || i == h-1)) { /* idziemy w prawo */
            ++j;
            substract_RGB(h,w,diff,avg,avg,i,j,i,j-1); // -255 0 = 255 255 0
            skwantyzowane[i][j] = diff_after_q(kwant,n,diff[i][j]);
        }            
        while (j > 0 && i < h-1) { /* Idziemy na lewo w dół */
            --j;  
            ++i;
            substract_RGB(h,w,diff,avg,avg,i,j,i-1,j+1);
            skwantyzowane[i][j] = diff_after_q(kwant,n,diff[i][j]);
        }
        if (i == h-1 && j < w-1) { /* idziemy w prawo */
            ++j;
            substract_RGB(h,w,diff,avg,avg,i,j,i,j-1);
            skwantyzowane[i][j] = diff_after_q(kwant,n,diff[i][j]);
        }  
        if (i < h-1 && (j == 0 || j == w-1)) { /* jeśli nie jesteśmy dolnej krawedzi idziemy w dół */ 
            ++i;
            substract_RGB(h,w,diff,avg,avg,i,j,i-1,j);
            skwantyzowane[i][j] = diff_after_q(kwant,n,diff[i][j]);
        } 
        while (i > 0 && j < w-1) {
            ++j;
            --i;
            substract_RGB(h,w,diff,avg,avg,i,j,i+1,j-1);
            skwantyzowane[i][j] = diff_after_q(kwant,n,diff[i][j]);
        }
        if (j == w-1 && i < h-1) {
            ++i;
            substract_RGB(h,w,diff,avg,avg,i,j,i-1,j);
            skwantyzowane[i][j] = diff_after_q(kwant,n,diff[i][j]);
        }      
    }
}

void decode_roznicowe(size_t h, size_t w, Pixel decoded[h][w], Pixel_c skwantyzowane[h][w]) {
    
    size_t i = 0, j = 0;
    decoded[i][j].R = (unsigned char)skwantyzowane[i][j].R;
    decoded[i][j].G = (unsigned char)skwantyzowane[i][j].G;
    decoded[i][j].B = (unsigned char)skwantyzowane[i][j].B;
    
    while (!(i == (h-1) && j == (w-1)))
    {
        if (j < w-1 && (i == 0 || i == h-1)) { /* idziemy w prawo */
            ++j;
            decoded[i][j].R = skwantyzowane[i][j].R + skwantyzowane[i][j-1].R;
            decoded[i][j].G = skwantyzowane[i][j].G + skwantyzowane[i][j-1].G;
            decoded[i][j].B = skwantyzowane[i][j].B + skwantyzowane[i][j-1].B;            
        }            
        while (j > 0 && i < h-1) { /* Idziemy na lewo w dół */
            --j;  
            ++i;
            decoded[i][j].R = skwantyzowane[i][j].R + skwantyzowane[i-1][j+1].R;
            decoded[i][j].G = skwantyzowane[i][j].G + skwantyzowane[i-1][j+1].G;
            decoded[i][j].B = skwantyzowane[i][j].B + skwantyzowane[i-1][j+1].B; 
        }
        if (i == h-1 && j < w-1) { /* idziemy w prawo */
            ++j;
            decoded[i][j].R = skwantyzowane[i][j].R + skwantyzowane[i][j-1].R;
            decoded[i][j].G = skwantyzowane[i][j].G + skwantyzowane[i][j-1].G;
            decoded[i][j].B = skwantyzowane[i][j].B + skwantyzowane[i][j-1].B; 
        }  
        if (i < h-1 && (j == 0 || j == w-1)) { /* jeśli nie jesteśmy dolnej krawedzi idziemy w dół */ 
            ++i;
            decoded[i][j].R = skwantyzowane[i][j].R + skwantyzowane[i-1][j].R;
            decoded[i][j].G = skwantyzowane[i][j].G + skwantyzowane[i-1][j].G;
            decoded[i][j].B = skwantyzowane[i][j].B + skwantyzowane[i-1][j].B; 
        } 
        while (i > 0 && j < w-1) {
            ++j;
            --i;
            decoded[i][j].R = skwantyzowane[i][j].R + skwantyzowane[i+1][j-1].R;
            decoded[i][j].G = skwantyzowane[i][j].G + skwantyzowane[i+1][j-1].G;
            decoded[i][j].B = skwantyzowane[i][j].B + skwantyzowane[i+1][j-1].B; 
        }
        if (j == w-1 && i < h-1) {
            ++i;
            decoded[i][j].R = skwantyzowane[i][j].R + skwantyzowane[i-1][j].R;
            decoded[i][j].G = skwantyzowane[i][j].G + skwantyzowane[i-1][j].G;
            decoded[i][j].B = skwantyzowane[i][j].B + skwantyzowane[i-1][j].B; 
        }      
    }
}

void fill_avg_dev(size_t x, size_t y, Pixel_f avg[x][y], Pixel_f dev[x][y], size_t i, size_t j, Pixel curr, Pixel prev) {

    avg[i][j].R = (curr.R + prev.R)/2.0;
    avg[i][j].G = (curr.G + prev.G)/2.0;
    avg[i][j].B = (curr.B + prev.B)/2.0;

    dev[i][j].R = (curr.R - prev.R)/2.0;
    dev[i][j].G = (curr.G - prev.G)/2.0;
    dev[i][j].B = (curr.B - prev.B)/2.0;
}

void jpeg(size_t x, size_t y, Pixel pixel[x][y], Pixel_f avg[x][y], Pixel_f dev[x][y]) {

    size_t i = 0, j = 0;

    avg[i][j].R = (double)pixel[i][j].R;
    avg[i][j].G = (double)pixel[i][j].G;
    avg[i][j].B = (double)pixel[i][j].B;
    dev[i][j].R = (double)pixel[i][j].R;
    dev[i][j].G = (double)pixel[i][j].G;
    dev[i][j].B = (double)pixel[i][j].B;

    while (!(i == (x-1) && j == (y-1)))
    {
        if (j < y-1 && (i == 0 || i == x-1)) { /* idziemy w prawo */
            ++j;
            fill_avg_dev(x,y,avg,dev,i,j,pixel[i][j],pixel[i][j-1]);               
        }            
        while (j > 0 && i < x-1) { /* Idziemy na lewo w dół */
            --j;  
            ++i;
            fill_avg_dev(x,y,avg,dev,i,j,pixel[i][j],pixel[i-1][j+1]);  
        }
        if (i == x-1 && j < y-1) { /* idziemy w prawo */
            ++j;
            fill_avg_dev(x,y,avg,dev,i,j,pixel[i][j],pixel[i][j-1]); 
        }  
        if (i < x-1 && (j == 0 || j == y-1)) { /* jeśli nie jesteśmy dolnej krawedzi idziemy w dół */ 
            ++i;
            fill_avg_dev(x,y,avg,dev,i,j,pixel[i][j],pixel[i-1][j]); 
        } 
        while (i > 0 && j < y-1) {
            ++j;
            --i;
            fill_avg_dev(x,y,avg,dev,i,j,pixel[i][j],pixel[i+1][j-1]); 
        }
        if (j == y-1 && i < x-1) {
            ++i;
            fill_avg_dev(x,y,avg,dev,i,j,pixel[i][j],pixel[i-1][j]); 
        }      
    }
}

static unsigned char ID_Lenght;
static unsigned char Color_map_Type;
static unsigned char Image_Type;
static unsigned short First_Entry_Index, Color_map_Lenght;
static unsigned char Color_map_Entry_Size;
static unsigned short X_origin_of_Image, Y_origin_of_Image, Image_Width, Image_Height;
static unsigned char Pixel_Depth, Image_Descriptor;

void get_header()
{
    unsigned char sym;
    // used where field size is more than 1 byte
    unsigned char byte1; 
    unsigned char byte2; 

    // FIELD 1 (1 byte)
    ID_Lenght = (unsigned char)getchar(); // size of Field 6, image ID field (0 - 255 bytes)
    // FIELD 2 (1 byte)
    Color_map_Type = (unsigned char)getchar(); // contains value 0 or 1
    // 0 - indicates that no color-map data is included with this image.
    // 1 - indicates that a color-map is included with this image.

    // FIELD 3 (1 byte)
    Image_Type = (unsigned char)getchar(); // contains value {0,1,2,3,9,10,11}
    // 0 - no image data included
    // 1 - uncompressed, Color-mapped image
    // 2 - uncompressed, True-color image
    // 3 - uncompressed, Black-and-white image
    // 9 - run-lenght encoded, Color-mapped image
    // 10 -run-lenght encoded, True-color image
    // 11 -run-lenght encoded, Black-and-white image

    // FIELD 4 (5 bytes) - Color Map Specification (ALWAYS INCLUDED!)
        // Field 4.1 (2 bytes)
        byte1 = (unsigned char)getchar(); 
        byte2 = (unsigned char)getchar();
        First_Entry_Index = byte1 + byte2*256;
        // Field 4.2 (2 bytes)
        byte1 = (unsigned char)getchar();
        byte2 = (unsigned char)getchar();
        Color_map_Lenght = byte1 + byte2*256;
        // Field 4.3 (1 byte)
        Color_map_Entry_Size = (unsigned char)getchar();

    // FIELD 5 (10 bytes) - Image Specification
        // Field 5.1 (2 bytes)
        byte1 = (unsigned char)getchar();
        byte2 = (unsigned char)getchar();
        X_origin_of_Image = byte1 + byte2*256;
        // Field 5.2 (2 bytes)
        byte1 = (unsigned char)getchar();
        byte2 = (unsigned char)getchar();
        Y_origin_of_Image = byte1 + byte2*256;
        // Field 5.3 (2 bytes)
        byte1 = (unsigned char)getchar();
        byte2 = (unsigned char)getchar();
        Image_Width = byte1 + byte2*256;    // KEY VARIABLE!!!
        // Field 5.4 (2 bytes)
        byte1 = (unsigned char)getchar();
        byte2 = (unsigned char)getchar();
        Image_Height = byte1 + byte2*256;   // KEY VARIABLE!!!
        // Field 5.5 (1 byte)
        Pixel_Depth = (unsigned char)getchar();
        // Field 5.6 (1 byte)
        Image_Descriptor = (unsigned char)getchar();

    // FIELD 6 ('ID_Lenght' bytes) - Image ID
    if(ID_Lenght > 0){
        for (size_t i = 0; i < ID_Lenght; i++)
        {
            sym = (unsigned char)getchar();
        }
    }

    // FIELD 7 (variable) - Color Map Data 
    // Ze względu na założenia zadania nie musimy się tym martwić.

    // Do tej pory pobraliśmy cały nagłówkek, przed nami mapa bitowa.

    printf("ID_Lenght = %hu\n"            , (short)ID_Lenght    );
    printf("Color_map_Type = %hhu\n"      , Color_map_Type      );
    printf("Image_Type = %hhu\n"          , Image_Type          );
    printf("First_Entry_Index = %hu\n"    , First_Entry_Index   );
    printf("Color_map_Lenght = %hu\n"     , Color_map_Lenght    );
    printf("Color_map_Entry_Size = %hhu\n", Color_map_Entry_Size);
    printf("X_origin_of_Image = %hu\n"    , X_origin_of_Image   );
    printf("Y_origin_of_Image = %hu\n"    , Y_origin_of_Image   );
    printf("Image_Width = %hu\n"          , Image_Width         );
    printf("Image_Height = %hu\n"         , Image_Height        ); 
    printf("Pixel_Depth = %hhu\n"         , Pixel_Depth         );
    printf("Image_Descriptor = %hhu\n"    , Image_Descriptor    );

    uint8_t F5_6 = Image_Descriptor;
    uint8_t bit_5_4 = 48; // 00110000
    uint8_t odp = F5_6 & bit_5_4;

    puts("Order in which pixel data is transferred from the file to the screen: ");
    if(odp == 0){
        puts("bottom left");
    }
    else if(odp == 16){
        puts("bottom right");
    }
    else if(odp == 32){
        puts("top left");
    }
    else if(odp == 48){
        puts("top right");
    }
}

void write_header(FILE* f_out)
{
    fwrite(&ID_Lenght           , sizeof(unsigned char), 1, f_out);
    fwrite(&Color_map_Type      , sizeof(unsigned char), 1, f_out);
    fwrite(&Image_Type          , sizeof(unsigned char), 1, f_out);
    fwrite(&First_Entry_Index   , sizeof(unsigned short), 1, f_out);
    fwrite(&Color_map_Lenght    , sizeof(unsigned short), 1, f_out);
    fwrite(&Color_map_Entry_Size, sizeof(unsigned char), 1, f_out);
    fwrite(&X_origin_of_Image   , sizeof(unsigned short), 1, f_out);
    fwrite(&Y_origin_of_Image   , sizeof(unsigned short), 1, f_out);
    fwrite(&Image_Width         , sizeof(unsigned short), 1, f_out);
    fwrite(&Image_Height        , sizeof(unsigned short), 1, f_out);
    fwrite(&Pixel_Depth         , sizeof(unsigned char), 1, f_out);
    fwrite(&Image_Descriptor    , sizeof(unsigned char), 1, f_out);
}

void get_footer(FILE* f_out)
{
    char sym; 
    while ((sym = (char)getchar()) != EOF)
    {
        fwrite(&sym, sizeof(char), 1, f_out);
    }
}



int main(int argc, char* argv[argc+1]) {

    FILE *f = freopen(argv[1], "rb", stdin);
    FILE *f_out = fopen(argv[2], "wb");
    get_header();
    write_header(f_out);
    size_t p = strtoul(argv[3],0,10);
    size_t bity_kwant = (size_t)(pow(2, p));
    char kwant[bity_kwant];
    make_kwantyzator_r(bity_kwant, kwant);

    /* size_t number_of_pixels = Image_Height * Image_Width; */

    Pixel pixel[Image_Height][Image_Width];
    unsigned char r,g,b;
    
    for (size_t i = 0; i < Image_Height; i++){
        for (size_t j = 0; j < Image_Width; j++){ 
            b = (unsigned char)getchar();
            g = (unsigned char)getchar();
            r = (unsigned char)getchar();
            pixel[i][j].R = r;
            pixel[i][j].G = g;
            pixel[i][j].B = b;

        }
    }

    Pixel_f avg[Image_Height][Image_Width];
    Pixel_f dev[Image_Height][Image_Width];
    jpeg(Image_Height, Image_Width, pixel, avg, dev);
    Pixel_c skwantyzowane[Image_Height][Image_Width];
    kodowanie_roznicowe(Image_Height, Image_Width,avg,kwant,bity_kwant,skwantyzowane);
    Pixel decoded[Image_Height][Image_Width];
    decode_roznicowe(Image_Height,Image_Width, decoded,skwantyzowane);


    for (size_t i = 0; i < Image_Height; i++){
        for (size_t j = 0; j < Image_Width; j++){
        
            // r = (unsigned char)(round(avg[i][j].R));
            // g = (unsigned char)(round(avg[i][j].G)); 
            // b = (unsigned char)(round(avg[i][j].B));

            fwrite(&(skwantyzowane[i][j]), sizeof(unsigned char), 1, f_out);
            fwrite(&(skwantyzowane[i][j]), sizeof(unsigned char), 1, f_out);
            fwrite(&(skwantyzowane[i][j]), sizeof(unsigned char), 1, f_out);
        }
    }


    get_footer(f_out);
    fclose(f);
    fclose(f_out);
    return EXIT_SUCCESS;
}


// 1. Mamy filtr dolnoprzepustowy 
