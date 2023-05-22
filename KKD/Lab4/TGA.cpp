#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>
#include <bits/stdc++.h>
#include <chrono>
#include <algorithm>

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

int pred8(int NW, int N, int W){
    if (NW >= max(N, W)){
        return max(W, N);
    }
    else if (NW <= min(W, N)){
        return min(W, N);
    }
    else{
        return modulo((W + N - NW),256);
    }
}



int main(int argc, char **argv){

    long double bluetropy = 0.0; 
    long double greentropy = 0.0; 
    long double redtropy = 0.0;  
    long double alltropy = 0.0;

    long double p8_bluetropy = 0.0; 
    long double p8_greentropy = 0.0; 
    long double p8_redtropy = 0.0;  
    long double p8_alltropy = 0.0;

    // getting information from binary file--------------------------------------------------
    int sym; // to get 1 byte
    int sym_1; // first byte if we have to get two bytes
    int sym_2; // second byte if we have to get two bytes
    // number on two bytes is like we do :
    // sym_1 = getchar();
    // sym_2 = getchar();
    // sym = sym_1 * 256 + sym_2;
    //----------------------------------------------------------------------------------------
    
    //specific information from header--------------------------------------------------------
    int F1; // number of bits in F6  || size: 1 byte
    int F2; // define if F7 exist. It is 0 or 1 || size: 1 byte
    int F3; // || size: 1 byte
    int F4_1; // starting entry in color map || size: 2 bytes
    int F4_2; // color map length - number of entries || size: 2 bytes
    int F4_3; // color map entry size - bits per entry || size: 1 byte || ex: 15, 16, 24, 32
    // F4_3 * F4_2 define size of F7
    int F5_1; // spawn X || size: 2 bytes
    int F5_2; // spawn Y || size: 2 bytes
    int F5_3; // image width || size: 2 bytes
    int F5_4; // image height || size: 2 bytes
    int F5_5; // pixel depth - how many bits per pixel. f.e. 24 || size: 1 byte
    uint8_t F5_6; // descriptor - bit 4: left-right, bit 5: top-bottom || size: 1 byte
    int order; // this is 4th and 5th bit of F5_6
    uint8_t help_operator = 48;
    // till now we have 18 bits written and that is all of header
    // in our list we assume, that F6 and F7 not exist

    int F6; // image ID. || size: F1 bytes. if 0, F6 not exist
    int F7; // color map data. F2 must be 1. || size: F4_2 * F4_3 / 8 (NOT SURE YET)

    
    FILE *f = freopen(argv[1], "rb", stdin);  // input

    // next we read our image
    if(f){

        F1 = getchar();
        F2 = getchar();
        F3 = getchar();

        sym_1 = getchar();
        sym_2 = getchar();
        F4_1 = sym_1  + sym_2 * 256;

        sym_1 = getchar();
        sym_2 = getchar();
        F4_2 = sym_1  + sym_2 * 256;

        F4_3 = getchar();

        sym_1 = getchar();
        sym_2 = getchar();
        F5_1 = sym_1  + sym_2 * 256;

        sym_1 = getchar();
        sym_2 = getchar();
        F5_2 = sym_1  + sym_2 * 256;

        sym_1 = getchar();
        sym_2 = getchar();
        F5_3 = sym_1  + sym_2 * 256;

        sym_1 = getchar();
        sym_2 = getchar();
        F5_4 = sym_1  + sym_2 * 256;

        F5_5 = getchar();
        F5_6 = getchar();

        order = F5_6 & help_operator;
        //  __ __ ____   &  00 11 0000

        


    }

    // print info from header:
    cout<<"F1: "<<F1<<endl;
    cout<<"F2: "<<F2<<endl;
    cout<<"F3: "<<F3<<endl;
    cout<<"F4_1: "<<F4_1<<endl;
    cout<<"F4_2: "<<F4_2<<endl;
    cout<<"F4_3: "<<F4_3<<endl;
    cout<<"F5_1 - X spawn: "<<F5_1<<endl;
    cout<<"F5_2 - Y spawn: "<<F5_2<<endl;
    cout<<"F5_3 - image width: "<<F5_3<<endl;
    cout<<"F5_4 - image height: "<<F5_4<<endl;
    cout<<"F5_5 - pixel depth: "<<F5_5<<endl;
    cout<<"F5_6 - descriptor: "<<F5_6<<endl;
    cout<<"order: ";
    switch(order){
        case 0:
            cout<<order<<" (left-bottom)"<<endl;
            break;
        case 16:
            cout<<order<<" (right-bottom)"<<endl;
            break;
        case 32:
            cout<<order<<" (left-top)"<<endl;  
            break;
        case 48:
            cout<<order<<" (right-top)"<<endl;      
            break;
        default:
            cout<<order<<" fault"<<endl;
            break;    
        

    }

    // reading IMAGE DATA SECTION (F8)----------------
    // our order is left-bottom

    int color_blocks = F5_5 / 3; // in this ex it is 3
    int red, green, blue;
    int N_b, NW_b, W_b, N_g, NW_g, W_g, N_r, NW_r, W_r;
    int width = F5_3;
    int height = F5_4;
    int x;
    long double pixels = width * height;
    long double all_bytes = pixels * 3;

    long double tab_b[256] = { 0.0 };
    long double tab_g[256] = { 0.0 };
    long double tab_r[256] = { 0.0 };
    long double tab_all[256] = { 0.0 };

    long double p8_tab_b[256] = { 0.0 };
    long double p8_tab_g[256] = { 0.0 };
    long double p8_tab_r[256] = { 0.0 };
    long double p8_tab_all[256] = { 0.0 };

    int row_blue_north[width + 1];
    row_blue_north[0] = 0;

    int row_green_north[width + 1];
    row_green_north[0] = 0;
    
    int row_red_north[width + 1];
    row_red_north[0] = 0;

    
    int row_blue_curr[width + 1];
    row_blue_curr[0] = 0;
    
    int row_green_curr[width + 1];
    row_green_curr[0] = 0;

    int row_red_curr[width + 1];
    row_red_curr[0] = 0;

    for (int i = 1; i <= width; i++ ){
            sym = getchar();
            row_blue_curr[i] = sym;
            tab_b[sym]++;
            tab_all[sym]++;

            sym = getchar();
            row_green_curr[i] = sym;
            tab_g[sym]++;
            tab_all[sym]++;

            sym = getchar();
            row_red_curr[i] = sym;
            tab_r[sym]++;
            tab_all[sym]++;
        }


    for(int j = 2; j <= height; j++){

        for (int i = 1; i <= width; i++ ){
            // -------------------------------blue
            sym = getchar();
            row_blue_north[i] = sym;
            tab_b[sym]++;
            tab_all[sym]++;

            NW_b = row_blue_north[i-1];
            N_b = row_blue_north[i];
            W_b = row_blue_curr[i-1];

            x = pred8(NW_b, N_b, W_b);
            p8_tab_b[modulo((sym - x),256)]++;
            p8_tab_all[modulo((sym - x),256)]++;

            copy(row_blue_north, row_blue_north + width + 1, row_blue_curr);
            // -------------------------------green
            sym = getchar();
            row_green_north[i] = sym; 
            tab_g[sym]++;
            tab_all[sym]++;

            NW_g = row_green_north[i-1];
            N_g = row_green_north[i];
            W_g = row_green_curr[i-1];

            x = pred8(NW_g, N_g, W_g);
            p8_tab_g[modulo((sym - x),256)]++;
            p8_tab_all[modulo((sym - x),256)]++;
            copy(row_green_north, row_green_north + width + 1, row_green_curr);
            // -------------------------------red
            sym = getchar();
            row_red_north[i] = sym;
            tab_r[sym]++;
            tab_all[sym]++;

            NW_r = row_red_north[i-1];
            N_r = row_red_north[i];
            W_r = row_red_curr[i-1];

            x = pred8(NW_r, N_r, W_r);
            p8_tab_r[modulo((sym - x),256)]++;
            p8_tab_all[modulo((sym - x),256)]++;
            copy(row_red_north, row_red_north + width + 1, row_red_curr);
        }
        
    }

    for (int i = 1; i <= width; i++ ){
        W_b = row_blue_curr[i-1];
        x = pred8(0, 0, W_b);
        p8_tab_b[modulo((row_blue_curr[i] - x),256)]++;
        p8_tab_all[modulo((row_blue_curr[i] - x),256)]++;

        W_g = row_green_curr[i-1];
        x = pred8(0, 0, W_g);
        p8_tab_g[modulo((row_green_curr[i] - x),256)]++;
        p8_tab_all[modulo((row_green_curr[i] - x),256)]++;

        W_r = row_red_curr[i-1];
        x = pred8(0, 0, W_r);
        p8_tab_r[modulo((row_red_curr[i]- x),256)]++;
        p8_tab_all[modulo((row_red_curr[i] - x),256)]++;
    }



    for (int i = 0; i < 256; i++){
        if(tab_all[i] != 0) {
            alltropy = alltropy + ((tab_all[i]) * ((log2(tab_all[i])) - log2(all_bytes))); //prob * i(A)
        }

        if(tab_b[i] != 0) {
            bluetropy = bluetropy + ((tab_b[i]) * ((log2(tab_b[i])) - log2(pixels))); //prob * i(A)
        }

        if(tab_g[i] != 0) {
            greentropy = greentropy + ((tab_g[i]) * ((log2(tab_g[i])) - log2(pixels))); //prob * i(A)
        }

        if(tab_r[i] != 0) {
            redtropy = redtropy + ((tab_r[i]) * ((log2(tab_r[i])) - log2(pixels))); //prob * i(A)
        }
        //-----------------pred8
        if(p8_tab_all[i] != 0) {
            p8_alltropy = p8_alltropy + ((p8_tab_all[i]) * ((log2(p8_tab_all[i])) - log2(all_bytes))); //prob * i(A)
        }

        if(p8_tab_b[i] != 0) {
            p8_bluetropy = p8_bluetropy + ((p8_tab_b[i]) * ((log2(p8_tab_b[i])) - log2(pixels))); //prob * i(A)
        }

        if(p8_tab_g[i] != 0) {
            p8_greentropy = p8_greentropy + ((p8_tab_g[i]) * ((log2(p8_tab_g[i])) - log2(pixels))); //prob * i(A)
        }

        if(p8_tab_r[i] != 0) {
            p8_redtropy = p8_redtropy + ((p8_tab_r[i]) * ((log2(p8_tab_r[i])) - log2(pixels))); //prob * i(A)
        }
    }    

    alltropy = (alltropy * (-1) / all_bytes);
    bluetropy = (bluetropy * (-1) / pixels);
    greentropy = (greentropy * (-1) / pixels);
    redtropy = (redtropy * (-1) / pixels);

    p8_alltropy = (p8_alltropy * (-1) / all_bytes);
    p8_bluetropy = (p8_bluetropy * (-1) / pixels);
    p8_greentropy = (p8_greentropy * (-1) / pixels);
    p8_redtropy = (p8_redtropy * (-1) / pixels);

    printf("alltropy: %.20Lf", alltropy);
    cout<<endl;
    printf("bluetropy: %.20Lf", bluetropy);
    cout<<endl;
    printf("greentropy: %.20Lf", greentropy);
    cout<<endl;
    printf("redtropy: %.20Lf", redtropy);
    cout<<endl;

    printf("p8_alltropy: %.20Lf", p8_alltropy);
    cout<<endl;
    printf("p8_bluetropy: %.20Lf", p8_bluetropy);
    cout<<endl;
    printf("p8_greentropy: %.20Lf", p8_greentropy);
    cout<<endl;
    printf("p8_redtropy: %.20Lf", p8_redtropy);
    cout<<endl;



    return 0;

}