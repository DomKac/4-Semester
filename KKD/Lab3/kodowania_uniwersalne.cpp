#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

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

// Będzie można lekko zmodyfikować przy odczytywaniu z pliku

int decode_from_fibonacci(string input){

    int x, y, z;
    x = 1;
    y = 2;

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

int decode_from_omega(string input){

    int n = 1;
    string number = "";

    while(input[0] != '0'){
            number = input.substr(0,n+1);
            input = input.substr(n+1);
            n = bin_to_dec(number);
            //cout << "Number = " << number << "\t n = " << n << endl;
            //this_thread::sleep_for(chrono::seconds(1));  
    }
    return n;
}


int main()
{
    int n;
    cout << "Podaj n: ";
    cin >> n;
    string bin = dec_to_bin(n);
    string fib = code_in_fibonacci(n);
    string gamma = code_in_gamma(n);
    string delta = code_in_delta(n);
    string omega = code_in_omega(n);
    cout << n << " w kodowaniu binarnym to:     " << bin << endl;
    cout << n << " w kodowaniu Fibonacciego to: " << fib << endl;
    cout << n << " w kodowaniu Eliasa gamma to: " << gamma << endl;
    cout << n << " w kodowaniu Eliasa delta to: " << delta << endl;
    cout << n << " w kodowaniu Eliasa omega to: " << omega << endl;
    cout << endl;
    cout << "Kod Fibonacciego " << fib << " kryje liczbe: " << decode_from_fibonacci(fib) << endl;
    //cout<< bin_to_dec(dec_to_bin(n)) << endl;
    cout << "Kod Eliasa omega " << omega << " kryje liczbe: " << decode_from_omega(omega) << endl;
    
    return 0;
}