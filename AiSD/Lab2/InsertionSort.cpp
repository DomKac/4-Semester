#include <iostream>

using namespace std;

int licznik_przestawien;
int licznik_porownan;

void wypisz_tablice(int n, int tab[])
{

    cout << " {";
    for (int i = 0; i < n - 1; ++i)
    {
        cout << tab[i] << ", ";
    }
    cout << tab[n - 1] << "}" << endl;
}

void insertionSort_over50(int n, int tab[])
{

    int key;
    int j;
    licznik_porownan = 0;
    licznik_przestawien = 0;

    for (int i = 1; i < n; ++i)
    {

        key = tab[i];
        j = i - 1;

        while (j >= 0 && key < tab[j])
        {
            licznik_porownan++;
            licznik_przestawien++; // niepewne
            tab[j + 1] = tab[j];
            j--;
        }

        if (j >= 0)
        {
            licznik_porownan++;
        }
        if (j + 1 != i)
        {
            licznik_przestawien++;
        }
        tab[j + 1] = key;
    }
}

void insertionSort_less50(int n, int tab[])
{

    int key;
    int j;
    licznik_porownan = 0;
    licznik_przestawien = 0;
    wypisz_tablice(n, tab);

    for (int i = 1; i < n; ++i)
    {

        key = tab[i];
        j = i - 1;

        while (j >= 0 && key < tab[j])
        {
            licznik_porownan++;
            licznik_przestawien++; // niepewne
            tab[j + 1] = tab[j];
            j--;
        }

        if (j >= 0)
        {
            licznik_porownan++;
        }
        if (j + 1 != i)
        {
            licznik_przestawien++;
        }
        tab[j + 1] = key;
        wypisz_tablice(n, tab);
    }
}

int main(int argc, char *argv[])
{

    int n;
    int x;
    cin >> n;
    int tab[n];

    for (int p = 0; p < n; p++)
    {
        cin >> x;
        tab[p] = x;
    }

    if (n >= 50)
    {
        insertionSort_over50(n, tab);
        cout << n << " ";
        cout << licznik_przestawien << " ";
        cout << licznik_porownan << endl;
    }
    else
    {
        /*
        insertionSort_less50(n, tab);
        cout << endl;
        cout << "Licznik przestawien: " << licznik_przestawien << endl;
        cout << "Licznik porownan: " << licznik_porownan << endl;
        */
        insertionSort_less50(n, tab);
        cout << n << " ";
        cout << licznik_przestawien << " ";
        cout << licznik_porownan << endl;
    }

    return 0;
}