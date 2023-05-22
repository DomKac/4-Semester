#include <iostream>
#include <cmath>
#include <cstdio>
// #include <aclui.h>

// Testowe pliki
// E:\Nauka_Programowania\Sem_4\KKD\Lab_1\pan-tadeusz-czyli-ostatni-zajazd-na-litwie.txt
// E:\Nauka_Programowania\Sem_4\KKD\Lab_1\test2.bin
// E:\Nauka_Programowania\Sem_4\KKD\Lab_1\test3.bin

using namespace std;

int main(int argc, char **argv)
{
    FILE *f = freopen(argv[1], "rb", stdin);

    long double symbole[256] = {0.0};         // w niej przechowywane będzie ilość występowania każego symbolu z tekstu

    unsigned int sym;

    long double ile = 0.0; // ilość wszystkich symboli
    long double entropia = 0.0;

    while ((sym = getchar()) != EOF)
    {
        symbole[sym]++;
        ile++;
    }

    for (int i = 0; i < 256; i++)
    {
        if (symbole[i] != 0)
        {
            entropia = entropia + (symbole[i] * (log2(symbole[i]) - log2(ile)));
        }
    }

    entropia = (-1) * (entropia / ile);

    printf("Entropia wynosi: %.20Lf \n", entropia);

    return 0;
}