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
    long double sym_po_sym[256][256] = {0.0}; // przechowuje info ile razy sym występował po danym symbolu

    unsigned int sym;
    unsigned int pre_sym = 0; //  "dla pierwszego znaku przyjmij, że przed nim jest znak o kodzie 0"

    long double ile = 0.0; // ilość wszystkich symboli

    long double entropia = 0.0;
    long double ppb;
    long double miara_info;

    long double entropia_warunkowa = 0.0;
    long double ppb_war;
    long double miara_info_war;
    long double suma_war = 0.0;

    while ((sym = getchar()) != EOF)
    {
        sym_po_sym[pre_sym][sym]++;
        symbole[sym]++;
        ile++;
        pre_sym = sym;
    }

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