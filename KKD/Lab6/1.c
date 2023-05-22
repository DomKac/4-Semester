#include <stdlib.h>
#include <stdint.h>
#include "TGA.h"

static unsigned char bit_mapa[6][5] = {  {  1,  2,  3,  4,  5,  },

                                        {  6,  7,  8,  9, 10,  },

                                        { 11, 12, 13, 14, 15, },

                                        { 16, 17, 18, 19, 20, },

                                        { 21, 22, 23, 24, 25, },

                                        { 26, 27, 28, 29, 30, }};



// void jpeg(size_t x, size_t y, unsigned char bitmapa[x][y]);

// void jpeg(size_t x, size_t y, unsigned char bitmapa[x][y]) {

//     size_t i = 0, j = 0;
//     unsigned char previous = bitmapa[i][j];
//     printf("%hhu ", bitmapa[i][j]);
//     while (!(i == (x-1) && j == (y-1)))
//     {
//             if (j < y-1 && (i == 0 || i == x-1)) { /* idziemy w prawo */
//                 ++j;
//                 puts("prawo");
//                 printf("%hhu[%hhu] ", bitmapa[i][j], previous);
//                 previous = bitmapa[i][j];
//             }            
//             while (j > 0 && i < x-1) { /* Idziemy na lewo w dół */
//                 --j;  
//                 ++i;
//                 puts("lewo-dol");
//                 printf("%hhu[%hhu] ", bitmapa[i][j], previous);
//                 previous = bitmapa[i][j];
//             }
//             if (i == x-1 && j < y-1) /* idziemy w prawo */
//             {
//                 ++j;
//                 puts("prawo");
//                 printf("%hhu[%hhu] ", bitmapa[i][j], previous);
//                 previous = bitmapa[i][j];
//             }  
//             if (i < x-1 && (j == 0 || j == y-1)) { /* jeśli nie jesteśmy dolnej krawedzi idziemy w dół */ 
//                 ++i;
//                 puts("dol");                
//                 printf("%hhu[%hhu] ", bitmapa[i][j], previous);
//                 previous = bitmapa[i][j];
//             } 
//             while (i > 0 && j < y-1) {
//                 ++j;
//                 --i;
//                 puts("prawo-gora");
//                 printf("%hhu[%hhu] ", bitmapa[i][j], previous);
//                 previous = bitmapa[i][j];
//             }
//             if (j == y-1 && i < x-1)
//             {
//                 ++i;
//                 puts("dol");                
//                 printf("%hhu[%hhu] ", bitmapa[i][j], previous);
//                 previous = bitmapa[i][j];
//             }
            
//     }
// }

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
    /* size_t number_of_pixels = Image_Height * Image_Width; */

    Pixel pixel[Image_Height][Image_Width];

    unsigned char r,g,b;
    for (size_t i = 0; i < Image_Height; i++)
    {
        for (size_t j = 0; j < Image_Width; j++)
        { 
            b = (unsigned char)getchar();
            g = (unsigned char)getchar();
            r = (unsigned char)getchar();
            pixel[i][j].R = r;
            pixel[i][j].G = g;
            pixel[i][j].B = b;
            fwrite(&(pixel[i][j].B), sizeof(unsigned char), 1, f_out);
            fwrite(&(pixel[i][j].G), sizeof(unsigned char), 1, f_out);
            fwrite(&(pixel[i][j].R), sizeof(unsigned char), 1, f_out);
        }
    }


    get_footer(f_out);
    fclose(f);
    fclose(f_out);
    return EXIT_SUCCESS;
}
