//
// Created by domin on 24.03.2022.
//
#include <iostream>

using namespace std;

int licznik_przestawien = 0;
int licznik_porownan = 0;

void wypisz_tablice(int n, int tab[])
{

    cout << " {";
    for (int i = 0; i < n - 1; ++i)
    {
        cout << tab[i] << ", ";
    }
    cout << tab[n - 1] << "}" << endl;
}

void merge_over50(int tab[], int l, int m, int r)
{

    int i = l;
    int j = m + 1;
    int k = l;

    int tempTab[r];

    while (i <= m && j <= r)
    {
        licznik_porownan++;
        if (tab[i] <= tab[j])
        {
            tempTab[k] = tab[i];
            i++;
            k++;
        }
        else
        {
            licznik_przestawien++;
            tempTab[k] = tab[j];
            j++;
            k++;
        }
    }

    while (i <= m)
    {
        licznik_przestawien++; // nie wiadomo
        tempTab[k] = tab[i];
        i++;
        k++;
    }
    while (j <= r)
    {
        licznik_przestawien++; // nie wiadomo
        tempTab[k] = tab[j];
        j++;
        k++;
    }

    for (int p = l; p <= r; ++p)
    {
        tab[p] = tempTab[p];
    }
}

void merge_less50(int tab[], int l, int m, int r, int n)
{

    int i = l;
    int j = m + 1;
    int k = l;

    int tempTab[r];

    while (i <= m && j <= r)
    {
        licznik_porownan++;
        if (tab[i] <= tab[j])
        {
            tempTab[k] = tab[i];
            i++;
            k++;
        }
        else
        {
            licznik_przestawien++;
            tempTab[k] = tab[j];
            j++;
            k++;
        }
    }

    while (i <= m)
    {
        licznik_przestawien++; // nie wiadomo
        tempTab[k] = tab[i];
        i++;
        k++;
    }
    while (j <= r)
    {
        licznik_przestawien++; // nie wiadomo
        tempTab[k] = tab[j];
        j++;
        k++;
    }

    for (int p = l; p <= r; ++p)
    {
        tab[p] = tempTab[p];
    }
    wypisz_tablice(n, tab);
}

void mergeSort_over50(int tab[], int l, int r)
{

    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort_over50(tab, l, m);
        mergeSort_over50(tab, m + 1, r);
        merge_over50(tab, l, m, r);
    }
}

void mergeSort_less50(int tab[], int l, int r, int n)
{

    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort_less50(tab, l, m, n);
        mergeSort_less50(tab, m + 1, r, n);
        merge_less50(tab, l, m, r, n);
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

    if (n < 50)
    {
        wypisz_tablice(n, tab);
        mergeSort_less50(tab, 0, n - 1, n);
        wypisz_tablice(n, tab);

        cout << endl;
        cout << "Licznik przestawien: " << licznik_przestawien << endl;
        cout << "Licznik porownan: " << licznik_porownan << endl;
    }
    else
    {
        mergeSort_over50(tab, 0, n - 1);
        cout << n << " ";
        cout << licznik_przestawien << " ";
        cout << licznik_porownan << endl;
    }
 
    return 0;
}