#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

// unordered_map<int, string> table;

// void add_ascii_to_glossary(){
//     for (int i = 0; i <= 255; i++) {
// 		string ch = "";
// 		ch += char(i);
// 		table[i] = ch;
// 	}
// }

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

// function to convert decimal to binary
string dec_to_bin(int n)
{
    string binary = "";

    int binaryNum[32];

    int i = 0;
    while (n > 0)
    {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int z = 0; z < 8 - i; z++)
    {
        binary = binary + "0";
    }

    for (int j = i - 1; j >= 0; j--)
        binary = binary + to_string(binaryNum[j]);

    return binary;
}

int decode_from_fibonacci(string input){

    int x, y, z;
    x = 1;
    y = 2;
    z = 3;
    int n = 0; // odszyfrowana liczba w systemie dziesietnym

    if(input == "11")
        return 1;
    
    if(input == "011")
        return 2;
    
    if(input[0] == '1')
        n = n + 1;

    if(input[1] == '1')
        n = n + 2;
    
    int i = 2;
    while(input[i] != '1' || input[i+1] != '1'){

        z = x + y;
        x = y;
        y = z;
        
        if(input[i] == '1')
        {
            n = n + z;
        }
        i++;
    }
    z = x + y; // nie dodaliśmy ostatniej liczby fibonacciego przed wyjsciem z petli
    n = n + z;

    return n; 
}

void decoding(vector<int> op, ofstream &out)
{
	cout << "\nDecoding\n";
	unordered_map<int, string> table;
	for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		table[i] = ch;
	}
	int old = op[0], n;
	string s = table[old];
	string c = "";
	c += s[0];
	//cout << s;
    out << s;
	int count = 256;
	for (int i = 0; i < op.size() - 1; i++) {
		n = op[i + 1];
		if (table.find(n) == table.end()) {
			s = table[old];
			s = s + c;
		}
		else {
			s = table[n];
		}
		//cout << s;
        out << s;
		c = "";
		c += s[0];
		table[count] = table[old] + c;
		count++;
		old = n;
	}
}

int main(int argc, char **argv)
{
    int choice;
    cout << "Wybierz kodowanie uniwersalne ktorego uzyles do kodowania: " << endl;
    cout << "1 - Elias Gamma" << endl;
    cout << "2 - Elias Delta" << endl;
    cout << "3 - Elias Omega" << endl;
    cout << "4 - Fibonacci" << endl << endl;
    cout << "Podaj indeks wybranego kodowania (np. '3')" << endl;
    cin >> choice;
    
    FILE *f = freopen(argv[1], "rb", stdin);

    int sym; // 8 bitowy znak pobierany z oryginalnego pliku
    string bufor = "";
    string number = "";
    int n;
    vector<int> output_code;

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

    if(choice == 3){
        n = 1;
        while ((sym = getchar()) != EOF)
        {
            sym_po_sym[pre_sym][sym]++;
            symbole[sym]++;
            ile++;
            pre_sym = sym;
            
            bufor = bufor + dec_to_bin(sym);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ OMEGA
            while(n+1 <= bufor.length() && bufor[0] != '0'){
                number = bufor.substr(0,n+1);
                bufor = bufor.substr(n+1);
                n = bin_to_dec(number); 
            }
            if(bufor[0] == '0'){
                n--; // zmniejszamy n o 1, ponieważ w kompresorze zwiekszalismy przed wyslaniem
                output_code.push_back(n);
                n = 1;
                bufor = bufor.substr(1); // odcinamy początkowy bit 0
            }
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        }
    }
    else if(choice == 1){ // dekodowanie gamma
        int counter = 0;
        while ((sym = getchar()) != EOF)
        {
            sym_po_sym[pre_sym][sym]++;
            symbole[sym]++;
            ile++;
            pre_sym = sym;
            
            bufor = bufor + dec_to_bin(sym);
            while(counter < bufor.length() && bufor[counter] != '1'){
                counter++;
            }
            if(bufor[counter] == '1'){
                
                bufor = bufor.substr(counter);
                while((counter + 1) > bufor.length()){
                    sym = getchar();
                    bufor = bufor + dec_to_bin(sym);
                    sym_po_sym[pre_sym][sym]++;
                    symbole[sym]++;
                    ile++;
                    pre_sym = sym;
                }
                number = bufor.substr(0,counter+1);
                bufor = bufor.substr(counter+1);
                n = bin_to_dec(number); 
                n--; // zmniejszamy n o 1, ponieważ w kompresorze zwiekszalismy przed wyslaniem
                output_code.push_back(n);
                
                counter = 0;
            }
        }
    }
    else if(choice == 2){ // dekodowanie delta
        int counter = 0;
        int n_bits;
        while ((sym = getchar()) != EOF)
        {
            sym_po_sym[pre_sym][sym]++;
            symbole[sym]++;
            ile++;
            pre_sym = sym;
            
            bufor = bufor + dec_to_bin(sym);
            while(counter < bufor.length() && bufor[counter] != '1'){
                counter++;
            }
            if(bufor[counter] == '1'){
                
                bufor = bufor.substr(counter);
                while((counter + 1) > bufor.length()){
                    sym = getchar();
                    bufor = bufor + dec_to_bin(sym);

                    sym_po_sym[pre_sym][sym]++;
                    symbole[sym]++;
                    ile++;
                    pre_sym = sym;
                }
                number = bufor.substr(0,counter+1);
                bufor = bufor.substr(counter+1);
                n_bits = bin_to_dec(number) - 1; 
                while(n_bits > bufor.length()){
                    sym = getchar();
                    bufor = bufor + dec_to_bin(sym);

                    sym_po_sym[pre_sym][sym]++;
                    symbole[sym]++;
                    ile++;
                    pre_sym = sym;
                }
                number = '1' + bufor.substr(0,n_bits);
                bufor = bufor.substr(n_bits);
                n = bin_to_dec(number);
                
                n--; // zmniejszamy n o 1, ponieważ w kompresorze zwiekszalismy przed wyslaniem
                output_code.push_back(n);
                
                counter = 0;
            }
        }  
    }
    else if(choice == 4){ // dekodowanie fibonacciego
        // 10001000|011... 1 + 8 + 89 = 98 
        int i = 1;
        while ((sym = getchar()) != EOF)
        {
            sym_po_sym[pre_sym][sym]++;
            symbole[sym]++;
            ile++;
            pre_sym = sym;
            
            bufor = bufor + dec_to_bin(sym);
            // Możliwe ze lepiej byłoby pobierać od razu 16 bitów do bufora  
            while(i < bufor.length() && (bufor[i] != '1' || bufor[i - 1] != '1')){
                i++;            
            }
            
            if(bufor[i] == '1' && bufor[i - 1] == '1'){
                number = bufor.substr(0,i+1);
                bufor = bufor.substr(i+1);
                n = decode_from_fibonacci(number);
                n--;
                output_code.push_back(n);
                i = 1;
            }
        }
    }
    
    fclose(f);
    ofstream out("output.txt");
    decoding(output_code, out);
    out.close();

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
