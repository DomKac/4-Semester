#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>
#include <bits/stdc++.h>

using namespace std;

unordered_map<string, int> table; // globalny słownik
// string glossary[1000000];

// dodajemy wszytskie 256 znaków do słownika
void add_ascii_to_glossary(){
    for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		table[ch] = i;
	}
}

int bin_to_dec(string bin)
{
    int dec = 0;
    for (size_t i = 0; i < bin.length(); i++)
    {
        if (bin[i] == '1')
        {
            dec = dec + pow(2, (bin.length() - i - 1));
        }
    }
    return dec;
}

string dec_to_bin(int n)
{
    string binary = "";

    if(n == 0)
        return "0";

    while (n > 0)
    {
        binary = to_string(n % 2) + binary;
        n = n / 2;
    }
    
    return binary;
}



// Można przyśpieszyć działanie fibonacciego
// Tablice dac jako zmienna globalną, odpalając funkcje raz wygenerujemy jakąs ilosc elementow ciagu ktore zapiszą się nam w tablicy, w przypadku kodowania pózniej większej liczby od największego dotychczas wygenerowanego elementu ciagu fibonacciego wygenerwoalibysmy potrzebne elementy.

string code_in_fibonacci(int n){

    int Fib[1000];
    Fib[0] = 1;
    Fib[1] = 2;

    if(n == 1){
        return "11";
    }
    else if(n == 2){
        return "011";
    }
    else{
        int i = 0;
        do{
            i++;
            Fib[i+1] = Fib[i] + Fib[i-1];
        } while(Fib[i+1] <= n);

        string code = "1";

        while(i >= 0){
            if(n >= Fib[i]){
                code = "1" + code;
                n = n - Fib[i];
            }
            else{
                code = "0" + code;
            }
            i--;
        }
        return code;
    }
}

string code_in_gamma(int n){

    string n_bin = dec_to_bin(n); // zapisujemy n binarnie
    string code = string((n_bin.length() - 1), '0') + n_bin;
    // jesli k to liczba bitow n to na poczatku wpisujemy k - 1 razy 0 i dopisujemy n w systemie binarnej

    return code;
}

string code_in_delta(int n){

    string n_bin = dec_to_bin(n); // zapisujemy n binarnie
    string prefix = code_in_gamma(n_bin.length()); // kodujemy gammą liczbę bitów n
    string n_cutet = n_bin.substr(1, (n_bin.length() - 1)); // postac binarna bez najabardziej znaczacego bita
    string code = prefix + n_cutet;

    return code;
}

string code_in_omega(int n){

    string code = "0";
    string n_bin = dec_to_bin(n);
    int len;
    while(n_bin.length() > 1){
        code = n_bin + code;
        len = n_bin.length();
        n_bin = dec_to_bin(len - 1);
    }

    return code;
}

int main(int argc, char **argv)
{
    int choice;
    cout << "Wybierz kodowanie uniwersalne: " << endl;
    cout << "1 - Elias Gamma" << endl;
    cout << "2 - Elias Delta" << endl;
    cout << "3 - Elias Omega" << endl;
    cout << "4 - Fibonacci" << endl << endl;
    cout << "Podaj indeks wybranego kodowania (np. '3')" << endl;
    cin >> choice;

    FILE *myfile;
    myfile = fopen("/home/dominik/Studia/KKD/Lab3/skompresowany_plik.bin", "wb");
    FILE *f = freopen(argv[1], "rb", stdin);    
    add_ascii_to_glossary(); // dodajemy ascii do slownika

    // ------------------------
    long double symbole[256] = {0.0};         // w niej przechowywane będzie ilość występowania każego symbolu z tekstu
    long double sym_po_sym[256][256] = {0.0}; // przechowuje info ile razy sym występował po danym symbolu

    unsigned int pre_sym = 0; //  "dla pierwszego znaku przyjmij, że przed nim jest znak o kodzie 0"

    long double ile = 0.0; // ilość wszystkich symboli

    long double entropia = 0.0;
    long double ppb;
    long double miara_info;

    long double entropia_warunkowa = 0.0;
    long double ppb_war;
    long double miara_info_war;
    long double suma_war = 0.0;
    // ------------------------

    int bytes_counter = 0;
    int sym_counter = 0;
    if (myfile)
    {   
        int sym; // 8 bitowy znak pobierany z oryginalnego pliku
        string p = "", c = "";
        int index = 256;
        string code;
        string text = "";
        string bits_to_send;
        int number;
        sym = getchar();
        p = char(sym); // p jest charem np. 'a' , sym jest kodem ascii p np. '97'
        // Kodowanie elias omega

        if(choice == 3){

            while ((sym = getchar()) != EOF){
                
                sym_po_sym[pre_sym][sym]++;
                symbole[sym]++;
                ile++;
                pre_sym = sym;
                
                sym_counter++;
                c = char(sym);
                if (table.find(p + c) != table.end()){
			        p = p + c;
		        }
                else{
                    //cout << p << "\t" << table[p] << "\t\t" << p + c << "\t" << index << endl;
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    code = code_in_omega(table[p]+1); // kodujemy nasz indeks w kodzie omega
                    text = text + code;
                    while (text.length() >= 8)
                    {
                        bits_to_send = text.substr(0, 8);
                        number = bin_to_dec(bits_to_send);
                        fwrite(&number, 1, 1, myfile);
                        text = text.substr(8);
                        bytes_counter++;
                    }
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    table[p + c] = index;
                    index++;
                    p = c;
                }
                c = "";
            }
            // musimy dopisać ostatni index do pliku
            //cout << p << "\t" << table[p] << endl;
            //code = code_in_omega(table[p]+1); // kodujemy nasz indeks + 1 (bo nie da sie zakodowac 0)
            text = text + code;
            while(text.length() >= 8)
            {
                bits_to_send = text.substr(0, 8);
                number = bin_to_dec(bits_to_send);
                fwrite(&number, 1, 1, myfile);
                text = text.substr(8);
                bytes_counter++;
            }
        }
        else if(choice == 1){

            while ((sym = getchar()) != EOF){
                
                sym_po_sym[pre_sym][sym]++;
                symbole[sym]++;
                ile++;
                pre_sym = sym;

                sym_counter++;
                c = char(sym);
                if (table.find(p + c) != table.end()){
			        p = p + c;
		        }
                else{
                    //cout << p << "\t" << table[p] << "\t\t" << p + c << "\t" << index << endl;
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    //code = code_in_gamma(table[p]+1); // kodujemy nasz indeks w kodzie GAMMA
                    //cout << code << "(" << table[p]+1 << ")_";
                    text = text + code;
                    while (text.length() >= 8)
                    {
                        bits_to_send = text.substr(0, 8);
                        number = bin_to_dec(bits_to_send);
                        fwrite(&number, 1, 1, myfile);
                        text = text.substr(8);
                        bytes_counter++;
                    }
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    table[p + c] = index;
                    index++;
                    p = c;
                }
                c = "";
            }
            // musimy dopisać ostatni index do pliku
            //cout << p << "\t" << table[p] << endl;
            code = code_in_gamma(table[p]+1); // kodujemy nasz indeks + 1 (bo nie da sie zakodowac 0)
            //cout << code << "(" << table[p]+1 << ")_";
            text = text + code;
            while(text.length() >= 8)
            {
                bits_to_send = text.substr(0, 8);
                number = bin_to_dec(bits_to_send);
                fwrite(&number, 1, 1, myfile);
                text = text.substr(8);
                bytes_counter++;
            }
        }
        else if(choice == 2){

            while ((sym = getchar()) != EOF){
                
                sym_po_sym[pre_sym][sym]++;
                symbole[sym]++;
                ile++;
                pre_sym = sym;

                sym_counter++;
                c = char(sym);
                if (table.find(p + c) != table.end()){
			        p = p + c;
		        }
                else{
                    // cout << p << "\t" << table[p] << "\t\t" << p + c << "\t" << index << endl;
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    code = code_in_delta(table[p]+1); // kodujemy nasz indeks w kodzie omega
                    text = text + code;
                    while (text.length() >= 8)
                    {
                        bits_to_send = text.substr(0, 8);
                        number = bin_to_dec(bits_to_send);
                        fwrite(&number, 1, 1, myfile);
                        text = text.substr(8);
                        bytes_counter++;
                    }
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    table[p + c] = index;
                    index++;
                    p = c;
                }
                c = "";
            }
            // musimy dopisać ostatni index do pliku
            //cout << p << "\t" << table[p] << endl;
            code = code_in_delta(table[p]+1); // kodujemy nasz indeks + 1 (bo nie da sie zakodowac 0)
            text = text + code;
            while(text.length() >= 8)
            {
                bits_to_send = text.substr(0, 8);
                number = bin_to_dec(bits_to_send);
                fwrite(&number, 1, 1, myfile);
                text = text.substr(8);
                bytes_counter++;
            }
        }
        else if(choice == 4){

            while ((sym = getchar()) != EOF){
               
                sym_po_sym[pre_sym][sym]++;
                symbole[sym]++;
                ile++;
                pre_sym = sym;
               
                sym_counter++;
                c = char(sym);
                if (table.find(p + c) != table.end()){
			        p = p + c;
		        }
                else{
                    //cout << p << "\t" << table[p] << "\t\t" << p + c << "\t" << index << endl;
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    code = code_in_fibonacci(table[p]+1); // kodujemy nasz indeks w kodzie omega
                    //cout << code;
                    text = text + code;
                    while (text.length() >= 8)
                    {
                        bits_to_send = text.substr(0, 8);
                        number = bin_to_dec(bits_to_send);
                        fwrite(&number, 1, 1, myfile);
                        text = text.substr(8);
                        bytes_counter++;
                    }
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    table[p + c] = index;
                    index++;
                    p = c;
                }
                c = "";
            }
            // musimy dopisać ostatni index do pliku
            //cout << p << "\t" << table[p] << endl;
            code = code_in_fibonacci(table[p]+1); // kodujemy nasz indeks + 1 (bo nie da sie zakodowac 0)
            //cout << code;
            text = text + code;
            while(text.length() >= 8)
            {
                bits_to_send = text.substr(0, 8);
                number = bin_to_dec(bits_to_send);
                fwrite(&number, 1, 1, myfile);
                text = text.substr(8);
                bytes_counter++;
            }
        }

        // Flush bits
        int ile_dopisac_0 = 8 - text.length();
        for (int i = 0; i < ile_dopisac_0; i++)
        {
            text = text + "0";
        }
        bits_to_send = text.substr(0, 8);
        number = bin_to_dec(bits_to_send);
        fwrite(&number, 1, 1, myfile);
        text = text.substr(8);
        bytes_counter++;
    }

    fclose(f);
    fclose(myfile);

    cout << "Wielkosc oryginalnego pliku: " << sym_counter + 1<<" bajtow" << endl;
    cout << "Wielkosc skompresowanego pliku: " << bytes_counter <<" bajtow" << endl;
    cout << "Stopien kompresji = " << (sym_counter +1) / bytes_counter << endl; 

    for (int i = 0; i < 256; i++)
    {

        // cout << "symbol o numerze: " << i << " wystepuje " << symbole[i] << " razy" << endl;
        // Liczenie zwykłej Entropii
        if (symbole[i] != 0)
        {

            // miara_info = (-1) * log2(ppb);
            // entropia = entropia + (ppb * miara_info);
            entropia = entropia + (symbole[i] * (log2(symbole[i]) - log2(ile)));
            // -------------------------

            for (int j = 0; j < 256; j++)
            {
                // Liczenie Entropii warunkowej
                if (sym_po_sym[i][j] != 0)
                {

                    // ppb_war = sym_po_sym[i][j] / symbole[i];
                    // miara_info_war = (-1) * log2(ppb_war);
                    // suma_war = suma_war + (ppb_war * miara_info_war);
                    suma_war = suma_war + (sym_po_sym[i][j] * (log2(symbole[i]) - log2(sym_po_sym[i][j])));

                    // cout << "Po symbolu o nr: " << i << " symbol o nr: " << j << " wystepuje " << sym_po_sym[i][j] << " razy" << endl;
                }
                // ---------------------------
            }
        }
        // cout<< "suma_war " << suma_war << " symbole[" << i << "] " << symbole[i] << endl;
        // suma_war = suma_war / symbole[i];

        // ppb = symbole[i] / ile;
        entropia_warunkowa = entropia_warunkowa + (suma_war / ile);
        suma_war = 0.0;
    }

    entropia = (-1) * (entropia / ile);

    printf("Entropia wynosi: %.20Lf \n", entropia);
    printf("Entropia warunkowa: %.20Lf \n", entropia_warunkowa);

    return 0;
}

// pan-tadeusz-czyli-ostatni-zajazd-na-litwie.txt