#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <assert.h>
#include <vector>
#include "TGA.h"

using namespace std;


long double metryka_taxi(Pixel pixel, Centroid centroid)
{
    return abs((pixel.R - centroid.R)) +
           abs((pixel.G - centroid.G)) + 
           abs((pixel.B - centroid.B));
}

static unsigned char ID_Lenght;
static unsigned char Color_map_Type;
static unsigned char Image_Type;
static unsigned short First_Entry_Index, Color_map_Lenght;
static unsigned char Color_map_Entry_Size;
static unsigned short X_origin_of_Image, Y_origin_of_Image, Image_Width, Image_Height;
static unsigned char Pixel_Depth, Image_Descriptor;

void get_header(FILE* f)
{
    unsigned char sym;
    // used where field size is more than 1 byte
    unsigned char byte1; 
    unsigned char byte2; 

    // FIELD 1 (1 byte)
    ID_Lenght = getchar(); // size of Field 6, image ID field (0 - 255 bytes)
    // FIELD 2 (1 byte)
    Color_map_Type = getchar(); // contains value 0 or 1
    // 0 - indicates that no color-map data is included with this image.
    // 1 - indicates that a color-map is included with this image.

    // FIELD 3 (1 byte)
    Image_Type = getchar(); // contains value {0,1,2,3,9,10,11}
    // 0 - no image data included
    // 1 - uncompressed, Color-mapped image
    // 2 - uncompressed, True-color image
    // 3 - uncompressed, Black-and-white image
    // 9 - run-lenght encoded, Color-mapped image
    // 10 -run-lenght encoded, True-color image
    // 11 -run-lenght encoded, Black-and-white image

    // FIELD 4 (5 bytes) - Color Map Specification (ALWAYS INCLUDED!)
        // Field 4.1 (2 bytes)
        byte1 = getchar(); 
        byte2 = getchar();
        First_Entry_Index = byte1 + byte2*256;
        // Field 4.2 (2 bytes)
        byte1 = getchar();
        byte2 = getchar();
        Color_map_Lenght = byte1 + byte2*256;
        // Field 4.3 (1 byte)
        Color_map_Entry_Size = getchar();

    // FIELD 5 (10 bytes) - Image Specification
        // Field 5.1 (2 bytes)
        byte1 = getchar();
        byte2 = getchar();
        X_origin_of_Image = byte1 + byte2*256;
        // Field 5.2 (2 bytes)
        byte1 = getchar();
        byte2 = getchar();
        Y_origin_of_Image = byte1 + byte2*256;
        // Field 5.3 (2 bytes)
        byte1 = getchar();
        byte2 = getchar();
        Image_Width = byte1 + byte2*256;    // KEY VARIABLE!!!
        // Field 5.4 (2 bytes)
        byte1 = getchar();
        byte2 = getchar();
        Image_Height = byte1 + byte2*256;   // KEY VARIABLE!!!
        // Field 5.5 (1 byte)
        Pixel_Depth = getchar();
        // Field 5.6 (1 byte)
        Image_Descriptor = getchar();

    // FIELD 6 ('ID_Lenght' bytes) - Image ID
    if(ID_Lenght > 0){
        for (size_t i = 0; i < ID_Lenght; i++)
        {
            sym = getchar();
        }
    }

    // FIELD 7 (variable) - Color Map Data 
    // Ze względu na założenia zadania nie musimy się tym martwić.

    // Do tej pory pobraliśmy cały nagłówkek, przed nami mapa bitowa.

    cout << "ID_Lenght = " << (short)ID_Lenght << endl;
    cout << "Color_map_Type = " << Color_map_Type << endl;
    cout << "Image_Type = " << Image_Type << endl;
    cout << "First_Entry_Index = " << First_Entry_Index << endl;
    cout << "Color_map_Lenght = " << Color_map_Lenght << endl;
    cout << "Color_map_Entry_Size = " << Color_map_Entry_Size << endl;
    cout << "X_origin_of_Image = " << X_origin_of_Image << endl;
    cout << "Y_origin_of_Image = " << Y_origin_of_Image << endl;
    cout << "Image_Width = " << Image_Width << endl;
    cout << "Image_Height = " << Image_Height << endl;
    cout << "Pixel_Depth = " << Pixel_Depth << endl;
    cout << "Image_Descriptor = " << Image_Descriptor << endl;

    uint8_t F5_6 = Image_Descriptor;
    uint8_t bit_5_4 = 48; // 00110000
    uint8_t odp = F5_6 & bit_5_4;

    cout << "Order in which pixel data is transferred from the file to the screen: " << endl;
    if(odp == 0){
        cout << "bottom left" << endl;
    }
    else if(odp == 16){
        cout << "bottom right" << endl;
    }
    else if(odp == 32){
        cout << "top left" << endl;
    }
    else if(odp == 48){
        cout << "top right" << endl;
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

void get_footer(FILE* f, FILE* f_out)
{
    char sym;
    while ((sym = getchar()) != EOF)
    {
        fwrite(&sym, sizeof(char), 1, f_out);
    }
}

void add_pixels_to_nearest_centroid(Centroid centroids[], size_t counter, Pixel pixel[], size_t n_of_p)
{
    long double min_distance = 1000000.0;
    long double distance;
    size_t min_dist_centroid_index;
    size_t sum_R_centroid[counter];
    size_t sum_G_centroid[counter];
    size_t sum_B_centroid[counter];

    for (size_t j = 0; j < counter; j++)
    {
        centroids[j].pixel_tab.clear();
        centroids[j].pixel_tab_size = 0;
        sum_R_centroid[j] = 0;
        sum_G_centroid[j] = 0;
        sum_B_centroid[j] = 0;
    }
    
    for (size_t i = 0; i < n_of_p; i++)
    {
        for (size_t j = 0; j < counter; j++)
        {
            distance = metryka_taxi(pixel[i],centroids[j]);
            //cout << distance << "= metryka centroidu nr: " << j << endl;
            if (distance < min_distance)
            {
                min_dist_centroid_index = j;
                min_distance = distance;
            }
        }
        sum_R_centroid[min_dist_centroid_index] += pixel[i].R;
        sum_G_centroid[min_dist_centroid_index] += pixel[i].G;
        sum_B_centroid[min_dist_centroid_index] += pixel[i].B;

        pixel[i].centroid_index = min_dist_centroid_index;
        
        centroids[min_dist_centroid_index].pixel_tab.push_back(pixel[i]);
        centroids[min_dist_centroid_index].pixel_tab_size++;   

        min_distance = 1000000.0;
    }
    
    size_t max_size = 0;
    size_t max_index;

    for (size_t j = 0; j < counter; j++)
    {
        centroids[j].R = (sum_R_centroid[j] / (long double)centroids[j].pixel_tab_size);
        centroids[j].G = (sum_G_centroid[j] / (long double)centroids[j].pixel_tab_size);
        centroids[j].B = (sum_B_centroid[j] / (long double)centroids[j].pixel_tab_size);

        if (centroids[j].pixel_tab_size > max_size)
        {
            max_index = j;
            max_size = centroids[j].pixel_tab_size;
        }
        
        cout << "(F)Centroid numer = " << j << ": R = " <<centroids[j].R << ", G = " << centroids[j].G <<  ", B = " << centroids[j].B << endl;
    }

    for (size_t j = 0; j < counter; j++)
    {
        if(centroids[j].pixel_tab_size == 0)
        {
            srand(time(NULL));
            size_t r_ind = rand() % max_size;
            centroids[j].R = centroids[max_index].pixel_tab.at(r_ind).R;
            centroids[j].G = centroids[max_index].pixel_tab.at(r_ind).G;
            centroids[j].B = centroids[max_index].pixel_tab.at(r_ind).B;
        }
    }
    
    
}


int main(int argc, char **argv)
{
    
    FILE *f = freopen(argv[1], "rb", stdin);
    FILE *f_out = fopen(argv[2], "wb");
    get_header(f);
    write_header(f_out);
    size_t number_of_pixels = Image_Height * Image_Width;

    Pixel pixel[number_of_pixels];

    unsigned char r,g,b;
    size_t sum_r = 0, sum_g = 0, sum_b = 0;

    for (size_t i = 0; i < number_of_pixels; i++)
    {
        b = getchar();
        g = getchar();
        r = getchar();
        pixel[i] = {.R = r, .G = g, .B = b};
        sum_r += (size_t)r;
        sum_g += (size_t)g;
        sum_b += (size_t)b;
        // fwrite(&(pixel[i].B), sizeof(unsigned char), 1, f_out);
        // fwrite(&(pixel[i].G), sizeof(unsigned char), 1, f_out);
        // fwrite(&(pixel[i].R), sizeof(unsigned char), 1, f_out);
    }
    
    // b g r | b g r | b g r | ... 

    
    Centroid centroid = {.R = (sum_r/(long double)number_of_pixels),
                      .G = (sum_g/(long double)number_of_pixels),
                      .B = (sum_b/(long double)number_of_pixels)};

    cout << "Centoid values: R = " << centroid.R << ", G = " << centroid.G << ", B = " << centroid.B << endl;


    long double taxi_metrics_sum = 0;
    
    for (size_t i = 0; i < number_of_pixels; i++)
    {
        taxi_metrics_sum += metryka_taxi(pixel[i], centroid);
    }
    
    long double avg_disorder = taxi_metrics_sum/(double)number_of_pixels;
    cout << "avg_disorder = " << avg_disorder << endl;

    // działa 

    size_t counter = 1;
    size_t colors = pow(2, stoi(argv[3]));
    cout << colors << endl;
    Centroid centroids[colors];
    Centroid centroids_help[colors];
    centroids_help[0] = {.R = centroid.R, .G = centroid.G, .B = centroid.B};
    long double epsylon = 0.001;
    
    while (colors > counter)
    {
         srand(time(NULL));
        int rand_epsylons[3] = {-5, 0 , 5};
        int r_e_R = rand_epsylons[rand()%3];
        int r_e_G = rand_epsylons[rand()%3];
        int r_e_B = rand_epsylons[rand()%3];

        for (size_t i = 0; i < counter; i++)
        {
            centroids[2*i] = {.R = (centroids_help[i].R - epsylon + r_e_R),
                              .G = (centroids_help[i].G - epsylon + r_e_G),
                              .B = (centroids_help[i].B - epsylon + r_e_B)};
            centroids[(2*i)+1] = {.R = (centroids_help[i].R + epsylon),
                                  .G = (centroids_help[i].G + epsylon),
                                  .B = (centroids_help[i].B + epsylon)};
            

            cout << "Centroid numer = " << 2*i << ": R = " <<centroids[2*i].R << ", G = " << centroids[2*i].G <<  ", B = " << centroids[2*i].B << endl;
            cout << "Centroid numer = " << 2*i + 1 << ": R = " <<centroids[2*i + 1].R << ", G = " << centroids[2*i + 1].G <<  ", B = " << centroids[2*i + 1].B << endl;
                      
        }
        for (size_t i = 0; i < counter; i++)
        {
            centroids_help[2*i] =  {.R = (centroids[2*i].R),
                                    .G = (centroids[2*i].G),
                                    .B = (centroids[2*i].B)};
            centroids_help[(2*i)+1] = { .R = (centroids[(2*i)+1].R),
                                        .G = (centroids[(2*i)+1].G),
                                        .B = (centroids[(2*i)+1].B)};
        }
    

        counter*=2;
        cout << "counter = " << counter << endl;
        add_pixels_to_nearest_centroid(centroids_help, counter, pixel, number_of_pixels);
        long double e = 0.0;
        // for (size_t j = 0; j < counter; j++)
        // {
        //     for (size_t i = 0; i < centroids_help[j].pixel_tab_size; i++)
        //     {
        //      e+=metryka_taxi(centroids_help[j].pixel_tab.at(i),centroids_help[j]);   
        //     }
        // }
        // if(1+epsylon > e/(double)number_of_pixels)
        // {
        //     cout << "Blad kwantyzacji!!!" << endl;
        //     break;
        // }

        for (size_t i = 0; i < counter; i++)
        {
            cout << "Ilosc pikseli w centroidzie "<<  i << " = " << centroids_help[i].pixel_tab_size<< endl;
        }

    }
    unsigned char R_floor, G_floor, B_floor;

    for (size_t i = 0; i < number_of_pixels; i++)
    {
        R_floor = (unsigned char)floor(centroids_help[pixel[i].centroid_index].R);
        G_floor = (unsigned char)floor(centroids_help[pixel[i].centroid_index].G);
        B_floor = (unsigned char)floor(centroids_help[pixel[i].centroid_index].B);
        
        fwrite(&(R_floor), sizeof(unsigned char), 1, f_out);
        // fwrite(&(B_floor), sizeof(unsigned char), 1, f_out);
        fwrite(&(G_floor), sizeof(unsigned char), 1, f_out);
                fwrite(&(R_floor), sizeof(unsigned char), 1, f_out);
                

    }

    get_footer(f, f_out);
    fclose(f);
    fclose(f_out);
    return 0;
}
