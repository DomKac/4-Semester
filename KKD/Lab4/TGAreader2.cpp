#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdint>

using namespace std;

int modulo(int x, int y){
    int z = x%y;
    if (z >= 0){
        return z;
    }
    else{
        return y + z;
    }
}


int predyktor_1(int X, int W){
    return modulo(X-W, 256);
}
int predyktor_2(int X, int N){
    return modulo(X-N, 256);
}
int predyktor_3(int X, int NW){
    return modulo(X-NW, 256);
}

int predyktor_4(int X, int W, int N, int NW){
    return modulo(X - (N + W - NW), 256);
}
int predyktor_5(int X, int W, int N, int NW){
    return modulo(X - (N + ((W - NW)/2)), 256);
}
int predyktor_6(int X, int W, int N, int NW){
    return modulo(X - (W + ((N - NW)/2)), 256);
}

int predyktor_7(int X, int W, int N){
    return modulo(X - ((N + W)/2), 256);
}

long double smallest_entropy(long double e0, long double e1, long double e2, long double e3, long double e4, long double e5, long double e6, long double e7, long double e8){

    long double current_smallest;
    current_smallest = min(e0,e1);
    current_smallest = min(current_smallest,e2);
    current_smallest = min(current_smallest,e3);
    current_smallest = min(current_smallest,e4);
    current_smallest = min(current_smallest,e5);
    current_smallest = min(current_smallest,e6);
    current_smallest = min(current_smallest,e7);
    current_smallest = min(current_smallest,e8);
    return current_smallest;

}

int predyktor_8(int X, int W, int N, int NW){
    
    if(NW >= max(W,N))
        return modulo(X - (min(W,N)), 256);
    else if(NW <= min(W,N))
        return modulo(X - (max(W,N)), 256);
    
    return modulo(X - (W + N - NW), 256);
}

void best_predyktor(long double e0, long double e1, long double e2, long double e3, long double e4, long double e5, long double e6, long double e7, long double e8){

    
    long double best_entropy = smallest_entropy(e0,e1,e2,e3,e4,e5,e6,e7,e8);
    printf("Smallest Entropy = %.20Lf \nObtained from ", best_entropy);

    if(best_entropy == e0)
        cout << "original" << endl;
    else if (best_entropy == e1)
        cout << "Predyktor 1" << endl;
    else if (best_entropy == e2)
        cout << "Predyktor 2" << endl;
    else if (best_entropy == e3)
        cout << "Predyktor 3" << endl;
    else if (best_entropy == e4)
        cout << "Predyktor 4" << endl;
    else if (best_entropy == e5)
        cout << "Predyktor 5" << endl;
    else if (best_entropy == e6)
        cout << "Predyktor 6" << endl;    
    else if (best_entropy == e7)
        cout << "Predyktor 7" << endl;
    else if (best_entropy == e8)
        cout << "Predyktor 8" << endl;

    cout << endl;
}

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
    
    int R_original[Image_Height+1][Image_Width+1];
    int G_original[Image_Height+1][Image_Width+1];
    int B_original[Image_Height+1][Image_Width+1];
    int BGR_original[Image_Height+1][3*(Image_Width+1)];

    // Predykat 0 - X = X
    long double R_arr[256] = {0.0};     // liczba wystapien danego parametru R
    long double G_arr[256] = {0.0};     // liczba wystapien danego parametru G
    long double B_arr[256] = {0.0};     // liczba wystapien danego parametru B
    long double RGB_arr[256] = {0.0};   // liczba wystapień danej wartości (0 - 255)

    int r,g,b,bgr_index;

    for (int h = Image_Height; h > 0; h--)
    {
        R_original[h][0] = 0;
        G_original[h][0] = 0;
        B_original[h][0] = 0;
        BGR_original[h][0] = 0;
        BGR_original[h][1] = 0;
        BGR_original[h][2] = 0;
        bgr_index = 3;
        
        for (size_t w = 1; w <= Image_Width; w++)
        {
            b = getchar();
            B_original[h][w] = b; 
            BGR_original[h][bgr_index] = b;
            bgr_index++;
            B_arr[b]++;
            RGB_arr[b]++;

            g = getchar();
            G_original[h][w] = g; 
            BGR_original[h][bgr_index] = g;
            bgr_index++;
            G_arr[g]++;
            RGB_arr[g]++;

            r = getchar();
            R_original[h][w] = r; 
            BGR_original[h][bgr_index] = r;
            bgr_index++;
            R_arr[r]++;
            RGB_arr[r]++;
        }
    }
    bgr_index = 0;
    for (size_t w = 0; w <= Image_Width; w++)
    {
        R_original[0][w] = 0;
        G_original[0][w] = 0;
        B_original[0][w] = 0;
        BGR_original[0][bgr_index] = 0;
        bgr_index++;
        BGR_original[0][bgr_index] = 0;
        bgr_index++;
        BGR_original[0][bgr_index] = 0;
        bgr_index++;
    }
    
    int N_R, N_G, N_B;
    int W_R, W_G, W_B;
    int NW_R, NW_G, NW_B;
    int X_R, X_G, X_B;
    


    long double   R_arr_1[256] = {0.0};  
    long double   G_arr_1[256] = {0.0};  
    long double   B_arr_1[256] = {0.0};  
    long double RGB_arr_1[256] = {0.0};

    long double   R_arr_2[256] = {0.0};  
    long double   G_arr_2[256] = {0.0};  
    long double   B_arr_2[256] = {0.0};  
    long double RGB_arr_2[256] = {0.0};

    long double   R_arr_3[256] = {0.0};  
    long double   G_arr_3[256] = {0.0};  
    long double   B_arr_3[256] = {0.0};  
    long double RGB_arr_3[256] = {0.0};

    long double   R_arr_4[256] = {0.0};  
    long double   G_arr_4[256] = {0.0};  
    long double   B_arr_4[256] = {0.0};  
    long double RGB_arr_4[256] = {0.0};
    
    long double   R_arr_5[256] = {0.0};  
    long double   G_arr_5[256] = {0.0};  
    long double   B_arr_5[256] = {0.0};  
    long double RGB_arr_5[256] = {0.0};
    
    long double   R_arr_6[256] = {0.0};  
    long double   G_arr_6[256] = {0.0};  
    long double   B_arr_6[256] = {0.0};  
    long double RGB_arr_6[256] = {0.0};
    
    long double   R_arr_7[256] = {0.0};  
    long double   G_arr_7[256] = {0.0};  
    long double   B_arr_7[256] = {0.0};  
    long double RGB_arr_7[256] = {0.0};
    
    long double   R_arr_8[256] = {0.0};  
    long double   G_arr_8[256] = {0.0};  
    long double   B_arr_8[256] = {0.0};  
    long double RGB_arr_8[256] = {0.0};

    // b g r | b g r | b g r | ... 

    for (size_t h = 1; h <= Image_Height; h++)
    {
        for (size_t w = 1; w <= Image_Width; w++)
        {
            X_R = R_original[h][w];
            X_G = G_original[h][w];
            X_B = B_original[h][w];
            
            W_R = R_original[h][w-1];
            W_G = G_original[h][w-1];
            W_B = B_original[h][w-1];

            N_R = R_original[h-1][w];
            N_G = G_original[h-1][w];
            N_B = B_original[h-1][w];

            NW_R = R_original[h-1][w-1];
            NW_G = G_original[h-1][w-1];
            NW_B = B_original[h-1][w-1];


            // Predyktory
              R_arr_1[predyktor_1(X_R, W_R)]++;
              G_arr_1[predyktor_1(X_G, W_G)]++;
              B_arr_1[predyktor_1(X_B, W_B)]++;
            RGB_arr_1[predyktor_1(X_R, W_R)]++;
            RGB_arr_1[predyktor_1(X_G, W_G)]++;
            RGB_arr_1[predyktor_1(X_B, W_B)]++;

              R_arr_2[predyktor_2(X_R, N_R)]++;
              G_arr_2[predyktor_2(X_G, N_G)]++;
              B_arr_2[predyktor_2(X_B, N_B)]++;
            RGB_arr_2[predyktor_2(X_R, N_R)]++;
            RGB_arr_2[predyktor_2(X_G, N_G)]++;
            RGB_arr_2[predyktor_2(X_B, N_B)]++;

              R_arr_3[predyktor_3(X_R, NW_R)]++;
              G_arr_3[predyktor_3(X_G, NW_G)]++;
              B_arr_3[predyktor_3(X_B, NW_B)]++;
            RGB_arr_3[predyktor_3(X_R, NW_R)]++;
            RGB_arr_3[predyktor_3(X_G, NW_G)]++;
            RGB_arr_3[predyktor_3(X_B, NW_B)]++;

              R_arr_4[predyktor_4(X_R, W_R, N_R, NW_R)]++;
              G_arr_4[predyktor_4(X_G, W_G, N_G, NW_G)]++;
              B_arr_4[predyktor_4(X_B, W_B, N_B, NW_B)]++;
            RGB_arr_4[predyktor_4(X_R, W_R, N_R, NW_R)]++;
            RGB_arr_4[predyktor_4(X_G, W_G, N_G, NW_G)]++;
            RGB_arr_4[predyktor_4(X_B, W_B, N_B, NW_B)]++;

              R_arr_5[predyktor_5(X_R, W_R, N_R, NW_R)]++;
              G_arr_5[predyktor_5(X_G, W_G, N_G, NW_G)]++;
              B_arr_5[predyktor_5(X_B, W_B, N_B, NW_B)]++;
            RGB_arr_5[predyktor_5(X_R, W_R, N_R, NW_R)]++;
            RGB_arr_5[predyktor_5(X_G, W_G, N_G, NW_G)]++;
            RGB_arr_5[predyktor_5(X_B, W_B, N_B, NW_B)]++;

              R_arr_6[predyktor_6(X_R, W_R, N_R, NW_R)]++;
              G_arr_6[predyktor_6(X_G, W_G, N_G, NW_G)]++;
              B_arr_6[predyktor_6(X_B, W_B, N_B, NW_B)]++;
            RGB_arr_6[predyktor_6(X_R, W_R, N_R, NW_R)]++;
            RGB_arr_6[predyktor_6(X_G, W_G, N_G, NW_G)]++;
            RGB_arr_6[predyktor_6(X_B, W_B, N_B, NW_B)]++;

              R_arr_7[predyktor_7(X_R, W_R, N_R)]++;
              G_arr_7[predyktor_7(X_G, W_G, N_G)]++;
              B_arr_7[predyktor_7(X_B, W_B, N_B)]++;
            RGB_arr_7[predyktor_7(X_R, W_R, N_R)]++;
            RGB_arr_7[predyktor_7(X_G, W_G, N_G)]++;
            RGB_arr_7[predyktor_7(X_B, W_B, N_B)]++;

              R_arr_8[predyktor_8(X_R, W_R, N_R, NW_R)]++;
              G_arr_8[predyktor_8(X_G, W_G, N_G, NW_G)]++;
              B_arr_8[predyktor_8(X_B, W_B, N_B, NW_B)]++;
            RGB_arr_8[predyktor_8(X_R, W_R, N_R, NW_R)]++;
            RGB_arr_8[predyktor_8(X_G, W_G, N_G, NW_G)]++;
            RGB_arr_8[predyktor_8(X_B, W_B, N_B, NW_B)]++;
            // Koniec Predyktorów
        }
    }
    

    long double pixels = Image_Height * Image_Width;
    long double bit_mapa_bytes = 3 * pixels;
    
    long double   entropy_R = 0.0;
    long double   entropy_G = 0.0;
    long double   entropy_B = 0.0;
    long double entropy_RGB = 0.0;

    long double   entropy_R_1 = 0.0;
    long double   entropy_G_1 = 0.0;
    long double   entropy_B_1 = 0.0;
    long double entropy_RGB_1 = 0.0;

    long double   entropy_R_2 = 0.0;
    long double   entropy_G_2 = 0.0;
    long double   entropy_B_2 = 0.0;
    long double entropy_RGB_2 = 0.0;
    
    long double   entropy_R_3 = 0.0;
    long double   entropy_G_3 = 0.0;
    long double   entropy_B_3 = 0.0;
    long double entropy_RGB_3 = 0.0;
    
    long double   entropy_R_4 = 0.0;
    long double   entropy_G_4 = 0.0;
    long double   entropy_B_4 = 0.0;
    long double entropy_RGB_4 = 0.0;
    
    long double   entropy_R_5 = 0.0;
    long double   entropy_G_5 = 0.0;
    long double   entropy_B_5 = 0.0;
    long double entropy_RGB_5 = 0.0;
    
    long double   entropy_R_6 = 0.0;
    long double   entropy_G_6 = 0.0;
    long double   entropy_B_6 = 0.0;
    long double entropy_RGB_6 = 0.0;
    
    long double   entropy_R_7 = 0.0;
    long double   entropy_G_7 = 0.0;
    long double   entropy_B_7 = 0.0;
    long double entropy_RGB_7 = 0.0;
    
    long double   entropy_R_8 = 0.0;
    long double   entropy_G_8 = 0.0;
    long double   entropy_B_8 = 0.0;
    long double entropy_RGB_8 = 0.0;
    
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
        if (G_arr_1[i] != 0)
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
        // Predykat 2
        if (R_arr_2[i] != 0)
        {
            entropy_R_2 = entropy_R_2 + (R_arr_2[i] * (log2(R_arr_2[i]) - log2(pixels)));
        }
        if (G_arr_2[i] != 0)
        {
            entropy_G_2 = entropy_G_2 + (G_arr_2[i] * (log2(G_arr_2[i]) - log2(pixels)));
        }
        if (B_arr_2[i] != 0)
        {
            entropy_B_2 = entropy_B_2 + (B_arr_2[i] * (log2(B_arr_2[i]) - log2(pixels)));
        }
        if (RGB_arr_2[i] != 0)
        {
            entropy_RGB_2 = entropy_RGB_2 + (RGB_arr_2[i] * (log2(RGB_arr_2[i]) - log2(bit_mapa_bytes)));
        }
        // Predykat 3
        if (R_arr_3[i] != 0)
        {
            entropy_R_3 = entropy_R_3 + (R_arr_3[i] * (log2(R_arr_3[i]) - log2(pixels)));
        }
        if (G_arr_3[i] != 0)
        {
            entropy_G_3 = entropy_G_3 + (G_arr_3[i] * (log2(G_arr_3[i]) - log2(pixels)));
        }
        if (B_arr_3[i] != 0)
        {
            entropy_B_3 = entropy_B_3 + (B_arr_3[i] * (log2(B_arr_3[i]) - log2(pixels)));
        }
        if (RGB_arr_3[i] != 0)
        {
            entropy_RGB_3 = entropy_RGB_3 + (RGB_arr_3[i] * (log2(RGB_arr_3[i]) - log2(bit_mapa_bytes)));
        }
        // Predykat 4
        if (R_arr_4[i] != 0)
        {
            entropy_R_4 = entropy_R_4 + (R_arr_4[i] * (log2(R_arr_4[i]) - log2(pixels)));
        }
        if (G_arr_4[i] != 0)
        {
            entropy_G_4 = entropy_G_4 + (G_arr_4[i] * (log2(G_arr_4[i]) - log2(pixels)));
        }
        if (B_arr_4[i] != 0)
        {
            entropy_B_4 = entropy_B_4 + (B_arr_4[i] * (log2(B_arr_4[i]) - log2(pixels)));
        }
        if (RGB_arr_4[i] != 0)
        {
            entropy_RGB_4 = entropy_RGB_4 + (RGB_arr_4[i] * (log2(RGB_arr_4[i]) - log2(bit_mapa_bytes)));
        }
        // Predykat 5
        if (R_arr_5[i] != 0)
        {
            entropy_R_5 = entropy_R_5 + (R_arr_5[i] * (log2(R_arr_5[i]) - log2(pixels)));
        }
        if (G_arr_5[i] != 0)
        {
            entropy_G_5 = entropy_G_5 + (G_arr_5[i] * (log2(G_arr_5[i]) - log2(pixels)));
        }
        if (B_arr_5[i] != 0)
        {
            entropy_B_5 = entropy_B_5 + (B_arr_5[i] * (log2(B_arr_5[i]) - log2(pixels)));
        }
        if (RGB_arr_5[i] != 0)
        {
            entropy_RGB_5 = entropy_RGB_5 + (RGB_arr_5[i] * (log2(RGB_arr_5[i]) - log2(bit_mapa_bytes)));
        }
        // Predykat 6
        if (R_arr_6[i] != 0)
        {
            entropy_R_6 = entropy_R_6 + (R_arr_6[i] * (log2(R_arr_6[i]) - log2(pixels)));
        }
        if (G_arr_6[i] != 0)
        {
            entropy_G_6 = entropy_G_6 + (G_arr_6[i] * (log2(G_arr_6[i]) - log2(pixels)));
        }
        if (B_arr_6[i] != 0)
        {
            entropy_B_6 = entropy_B_6 + (B_arr_6[i] * (log2(B_arr_6[i]) - log2(pixels)));
        }
        if (RGB_arr_6[i] != 0)
        {
            entropy_RGB_6 = entropy_RGB_6 + (RGB_arr_6[i] * (log2(RGB_arr_6[i]) - log2(bit_mapa_bytes)));
        }
        // Predykat 7
        if (R_arr_7[i] != 0)
        {
            entropy_R_7 = entropy_R_7 + (R_arr_7[i] * (log2(R_arr_7[i]) - log2(pixels)));
        }
        if (G_arr_7[i] != 0)
        {
            entropy_G_7 = entropy_G_7 + (G_arr_7[i] * (log2(G_arr_7[i]) - log2(pixels)));
        }
        if (B_arr_7[i] != 0)
        {
            entropy_B_7 = entropy_B_7 + (B_arr_7[i] * (log2(B_arr_7[i]) - log2(pixels)));
        }
        if (RGB_arr_7[i] != 0)
        {
            entropy_RGB_7 = entropy_RGB_7 + (RGB_arr_7[i] * (log2(RGB_arr_7[i]) - log2(bit_mapa_bytes)));
        }
        // Predykat 8
        if (R_arr_8[i] != 0)
        {
            entropy_R_8 = entropy_R_8 + (R_arr_8[i] * (log2(R_arr_8[i]) - log2(pixels)));
        }
        if (G_arr_8[i] != 0)
        {
            entropy_G_8 = entropy_G_8 + (G_arr_8[i] * (log2(G_arr_8[i]) - log2(pixels)));
        }
        if (B_arr_8[i] != 0)
        {
            entropy_B_8 = entropy_B_8 + (B_arr_8[i] * (log2(B_arr_8[i]) - log2(pixels)));
        }
        if (RGB_arr_8[i] != 0)
        {
            entropy_RGB_8 = entropy_RGB_8 + (RGB_arr_8[i] * (log2(RGB_arr_8[i]) - log2(bit_mapa_bytes)));
        }
    }

    entropy_R = (-1) * (entropy_R / pixels);
    entropy_G = (-1) * (entropy_G / pixels);
    entropy_B = (-1) * (entropy_B / pixels);
    entropy_RGB = (-1) * (entropy_RGB / bit_mapa_bytes);

      entropy_R_1 = (-1) *   (entropy_R_1 / pixels);
      entropy_G_1 = (-1) *   (entropy_G_1 / pixels);
      entropy_B_1 = (-1) *   (entropy_B_1 / pixels);
    entropy_RGB_1 = (-1) * (entropy_RGB_1 / bit_mapa_bytes);
      entropy_R_2 = (-1) *   (entropy_R_2 / pixels);
      entropy_G_2 = (-1) *   (entropy_G_2 / pixels);
      entropy_B_2 = (-1) *   (entropy_B_2 / pixels);
    entropy_RGB_2 = (-1) * (entropy_RGB_2 / bit_mapa_bytes);
      entropy_R_3 = (-1) *   (entropy_R_3 / pixels);
      entropy_G_3 = (-1) *   (entropy_G_3 / pixels);
      entropy_B_3 = (-1) *   (entropy_B_3 / pixels);
    entropy_RGB_3 = (-1) * (entropy_RGB_3 / bit_mapa_bytes);
      entropy_R_4 = (-1) *   (entropy_R_4 / pixels);
      entropy_G_4 = (-1) *   (entropy_G_4 / pixels);
      entropy_B_4 = (-1) *   (entropy_B_4 / pixels);
    entropy_RGB_4 = (-1) * (entropy_RGB_4 / bit_mapa_bytes);
      entropy_R_5 = (-1) *   (entropy_R_5 / pixels);
      entropy_G_5 = (-1) *   (entropy_G_5 / pixels);
      entropy_B_5 = (-1) *   (entropy_B_5 / pixels);
    entropy_RGB_5 = (-1) * (entropy_RGB_5 / bit_mapa_bytes);
      entropy_R_6 = (-1) *   (entropy_R_6 / pixels);
      entropy_G_6 = (-1) *   (entropy_G_6 / pixels);
      entropy_B_6 = (-1) *   (entropy_B_6 / pixels);
    entropy_RGB_6 = (-1) * (entropy_RGB_6 / bit_mapa_bytes);
      entropy_R_7 = (-1) *   (entropy_R_7 / pixels);
      entropy_G_7 = (-1) *   (entropy_G_7 / pixels);
      entropy_B_7 = (-1) *   (entropy_B_7 / pixels);
    entropy_RGB_7 = (-1) * (entropy_RGB_7 / bit_mapa_bytes);
      entropy_R_8 = (-1) *   (entropy_R_8 / pixels);
      entropy_G_8 = (-1) *   (entropy_G_8 / pixels);
      entropy_B_8 = (-1) *   (entropy_B_8 / pixels);
    entropy_RGB_8 = (-1) * (entropy_RGB_8 / bit_mapa_bytes);

    cout << endl;
    printf("entropy_R = %.20Lf \n", entropy_R);
    printf("entropy_G = %.20Lf \n", entropy_G);
    printf("entropy_B = %.20Lf \n", entropy_B);
    printf("entropy_RGB = %.20Lf \n", entropy_RGB);
    cout << endl;
    printf(  "entropy_R_1 = %.20Lf \n",   entropy_R_1);
    printf(  "entropy_G_1 = %.20Lf \n",   entropy_G_1);
    printf(  "entropy_B_1 = %.20Lf \n",   entropy_B_1);
    printf("entropy_RGB_1 = %.20Lf \n", entropy_RGB_1);
    cout << endl;
    printf(  "entropy_R_2 = %.20Lf \n",   entropy_R_2);
    printf(  "entropy_G_2 = %.20Lf \n",   entropy_G_2);
    printf(  "entropy_B_2 = %.20Lf \n",   entropy_B_2);
    printf("entropy_RGB_2 = %.20Lf \n", entropy_RGB_2);
    cout << endl;
    printf(  "entropy_R_3 = %.20Lf \n",   entropy_R_3);
    printf(  "entropy_G_3 = %.20Lf \n",   entropy_G_3);
    printf(  "entropy_B_3 = %.20Lf \n",   entropy_B_3);
    printf("entropy_RGB_3 = %.20Lf \n", entropy_RGB_3);
    cout << endl;
    printf(  "entropy_R_4 = %.20Lf \n",   entropy_R_4);
    printf(  "entropy_G_4 = %.20Lf \n",   entropy_G_4);
    printf(  "entropy_B_4 = %.20Lf \n",   entropy_B_4);
    printf("entropy_RGB_4 = %.20Lf \n", entropy_RGB_4);
    cout << endl;
    printf(  "entropy_R_5 = %.20Lf \n",   entropy_R_5);
    printf(  "entropy_G_5 = %.20Lf \n",   entropy_G_5);
    printf(  "entropy_B_5 = %.20Lf \n",   entropy_B_5);
    printf("entropy_RGB_5 = %.20Lf \n", entropy_RGB_5);
    cout << endl;
    printf(  "entropy_R_6 = %.20Lf \n",   entropy_R_6);
    printf(  "entropy_G_6 = %.20Lf \n",   entropy_G_6);
    printf(  "entropy_B_6 = %.20Lf \n",   entropy_B_6);
    printf("entropy_RGB_6 = %.20Lf \n", entropy_RGB_6);
    cout << endl;
    printf(  "entropy_R_7 = %.20Lf \n",   entropy_R_7);
    printf(  "entropy_G_7 = %.20Lf \n",   entropy_G_7);
    printf(  "entropy_B_7 = %.20Lf \n",   entropy_B_7);
    printf("entropy_RGB_7 = %.20Lf \n", entropy_RGB_7);
    cout << endl;
    printf(  "entropy_R_8 = %.20Lf \n",   entropy_R_8);
    printf(  "entropy_G_8 = %.20Lf \n",   entropy_G_8);
    printf(  "entropy_B_8 = %.20Lf \n",   entropy_B_8);
    printf("entropy_RGB_8 = %.20Lf \n", entropy_RGB_8);

    cout << endl;
    
    cout << "RGB" << endl;
    best_predyktor(entropy_RGB, entropy_RGB_1,entropy_RGB_2,entropy_RGB_3,entropy_RGB_4,entropy_RGB_5,entropy_RGB_6,entropy_RGB_7,entropy_RGB_8);

    cout << "R" << endl;
    best_predyktor(entropy_R, entropy_R_1,entropy_R_2,entropy_R_3,entropy_R_4,entropy_R_5,entropy_R_6,entropy_R_7,entropy_R_8);

    cout << "G" << endl;
    best_predyktor(entropy_G, entropy_G_1,entropy_G_2,entropy_G_3,entropy_G_4,entropy_G_5,entropy_G_6,entropy_G_7,entropy_G_8);

    cout << "B" << endl;
    best_predyktor(entropy_B, entropy_B_1,entropy_B_2,entropy_B_3,entropy_B_4,entropy_B_5,entropy_B_6,entropy_B_7,entropy_B_8);

    return 0;
}