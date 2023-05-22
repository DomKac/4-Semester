#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdint>

using namespace std;

int main(int argc, char **argv)
{
    
    FILE *f = freopen(argv[1], "rb", stdin);

    int sym;
    // used where field size is more than 1 byte
    int byte1; 
    int byte2; 

    // FIELD 1 (1 byte)
    int ID_Lenght = getchar(); // size of Field 6, image ID field (0 - 255 bytes)
    
    // FIELD 2 (1 byte)
    int Color_map_Type = getchar(); // contains value 0 or 1
    // 0 - indicates that no color-map data is included with this image.
    // 1 - indicates that a color-map is included with this image.

    // FIELD 3 (1 byte)
    int Image_Type = getchar(); // contains value {0,1,2,3,9,10,11}
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
        int First_Entry_Index = byte1 + byte2*256;
        // Field 4.2 (2 bytes)
        byte1 = getchar();
        byte2 = getchar();
        int Color_map_Lenght = byte1 + byte2*256;
        // Field 4.3 (1 byte)
        int Color_map_Entry_Size = getchar();

    // FIELD 5 (10 bytes) - Image Specification
        // Field 5.1 (2 bytes)
        byte1 = getchar();
        byte2 = getchar();
        int X_origin_of_Image = byte1 + byte2*256;
        // Field 5.2 (2 bytes)
        byte1 = getchar();
        byte2 = getchar();
        int Y_origin_of_Image = byte1 + byte2*256;
        // Field 5.3 (2 bytes)
        byte1 = getchar();
        byte2 = getchar();
        int Image_Width = byte1 + byte2*256;    // KEY VARIABLE!!!
        // Field 5.4 (2 bytes)
        byte1 = getchar();
        byte2 = getchar();
        int Image_Height = byte1 + byte2*256;   // KEY VARIABLE!!!
        // Field 5.5 (1 byte)
        int Pixel_Depth = getchar();
        // Field 5.6 (1 byte)
        int Image_Descriptor = getchar();

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

    cout << "ID_Lenght = " << ID_Lenght << endl;
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
    

    if (odp != 0)
        return 0;

    // int R[Image_Height][ID_Lenght];
    // int G[Image_Height][ID_Lenght];
    // int B[Image_Height][ID_Lenght];
    
    int R[Image_Width];
    int G[Image_Width];
    int B[Image_Width];
    
    int N_R;
    int N_G;
    int N_B;
    int W_R;
    int W_G;
    int W_B;
    int X_R;
    int X_G;
    int X_B;

    size_t w = 0;
    size_t h = 0;

    // Predykat 0 - X = X
    long double R_arr[256] = {0.0};     // liczba wystapien danego parametru R
    long double G_arr[256] = {0.0};     // liczba wystapien danego parametru G
    long double B_arr[256] = {0.0};     // liczba wystapien danego parametru B
    long double RGB_arr[256] = {0.0};   // liczba wystapień danej wartości (0 - 255)

    // Predykat 1 - X = W
    long double R_arr_1[256] = {0.0};  
    long double G_arr_1[256] = {0.0};  
    long double B_arr_1[256] = {0.0};  
    long double RGB_arr_1[256] = {0.0};

    int r,g,b;

    // Wpisujemy do tablicy najniższy wiersz
    for (size_t w = 0; w < Image_Width; w++)
    {
        b = getchar();
        g = getchar(); 
        r = getchar();
        
        B_arr[b]++;
        G_arr[g]++;
        R_arr[r]++;
        RGB_arr[b]++;
        RGB_arr[g]++;
        RGB_arr[r]++;

        R[w] = r;
        G[w] = g;
        B[w] = b;
    }

    for (int h = Image_Height-2; h >= 0; h--) // h > 0
    //for (size_t h = 1; h < Image_Height; h++)
    {
        w = 0;
        b = getchar();
        g = getchar(); 
        r = getchar();
        
        B_arr[b]++;
        G_arr[g]++;
        R_arr[r]++;
        RGB_arr[b]++;
        RGB_arr[g]++;
        RGB_arr[r]++;

        W_R = 0;
        W_G = 0;
        W_B = 0;

        N_R = r;
        N_G = g;
        N_B = b;

        //------PREDYKATY------
        // 1.
        X_R = W_R; X_G = W_G; X_B = W_B;
        B_arr_1[X_B]++;
        G_arr_1[X_G]++;
        R_arr_1[X_R]++;
        RGB_arr_1[X_B]++;
        RGB_arr_1[X_G]++;
        RGB_arr_1[X_R]++;


        //---------------------

        R[w] = r;
        G[w] = g;
        B[w] = b;
        for (size_t w = 1; w < Image_Width; w++)
        {
            b = getchar();
            g = getchar(); 
            r = getchar();

            B_arr[b]++;
            G_arr[g]++;
            R_arr[r]++;
            RGB_arr[b]++;
            RGB_arr[g]++;
            RGB_arr[r]++;

            W_R = R[w-1];
            W_G = G[w-1];
            W_B = B[w-1];

            N_R = r;
            N_G = g;
            N_B = b;

            //------PREDYKATY------
            // 1.
            X_R = W_R; X_G = W_G; X_B = W_B;
            B_arr_1[X_B]++;
            G_arr_1[X_G]++;
            R_arr_1[X_R]++;
            RGB_arr_1[X_B]++;
            RGB_arr_1[X_G]++;
            RGB_arr_1[X_R]++;


            //---------------------

            R[w] = r;
            G[w] = g;
            B[w] = b;
        }

    }

    long double pixels = Image_Height * Image_Width;
    long double bit_mapa_bytes = 3 * pixels;
    long double entropy_R = 0.0;
    long double entropy_G = 0.0;
    long double entropy_B = 0.0;
    long double entropy_RGB = 0.0;
    long double entropy_R_1 = 0.0;
    long double entropy_G_1 = 0.0;
    long double entropy_B_1 = 0.0;
    long double entropy_RGB_1 = 0.0;
    
    for (size_t i = 0; i < 256; i++)
    {
        // Predykat 0
        if (R_arr[i] != 0)
        {
            entropy_R = entropy_R + (R_arr[i] * (log2(R_arr[i]) - log2(pixels)));
        }
        if (G_arr[i] != 0)
        {
            entropy_G = entropy_G + (G_arr[i] * (log2(G_arr[i]) - log2(pixels)));
        }
        if (B_arr[i] != 0)
        {
            entropy_B = entropy_B + (B_arr[i] * (log2(B_arr[i]) - log2(pixels)));
        }
        if (RGB_arr[i] != 0)
        {
            entropy_RGB = entropy_RGB + (RGB_arr[i] * (log2(RGB_arr[i]) - log2(bit_mapa_bytes)));
        }
        // Predykat 1
        if (R_arr_1[i] != 0)
        {
            entropy_R_1 = entropy_R_1 + (R_arr_1[i] * (log2(R_arr_1[i]) - log2(pixels)));
        }
        if (G_arr[i] != 0)
        {
            entropy_G_1 = entropy_G_1 + (G_arr_1[i] * (log2(G_arr_1[i]) - log2(pixels)));
        }
        if (B_arr_1[i] != 0)
        {
            entropy_B_1 = entropy_B_1 + (B_arr_1[i] * (log2(B_arr_1[i]) - log2(pixels)));
        }
        if (RGB_arr_1[i] != 0)
        {
            entropy_RGB_1 = entropy_RGB_1 + (RGB_arr_1[i] * (log2(RGB_arr_1[i]) - log2(bit_mapa_bytes)));
        }
    }

    entropy_R = (-1) * (entropy_R / pixels);
    entropy_G = (-1) * (entropy_G / pixels);
    entropy_B = (-1) * (entropy_B / pixels);
    entropy_RGB = (-1) * (entropy_RGB / bit_mapa_bytes);

    entropy_R_1 = (-1) * (entropy_R_1 / pixels);
    entropy_G_1 = (-1) * (entropy_G_1 / pixels);
    entropy_B_1 = (-1) * (entropy_B_1 / pixels);
    entropy_RGB_1 = (-1) * (entropy_RGB_1 / bit_mapa_bytes);

    printf("entropy_R = %.20Lf \n", entropy_R);
    printf("entropy_G = %.20Lf \n", entropy_G);
    printf("entropy_B = %.20Lf \n", entropy_B);
    printf("entropy_RGB = %.20Lf \n", entropy_RGB);
    printf("entropy_R_1 = %.20Lf \n", entropy_R_1);
    printf("entropy_G_1 = %.20Lf \n", entropy_G_1);
    printf("entropy_B_1 = %.20Lf \n", entropy_B_1);
    printf("entropy_RGB_1 = %.20Lf \n", entropy_RGB_1);

    

    return 0;
}