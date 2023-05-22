#include <iostream>
#include <random>
#include <stdlib.h>     /* srand, rand */

using namespace std;

int przestawienia = 0;
int porownania = 0;

void wypisz_tablice(int n, int tab[])
{
    cout << " {";
    for (int i = 0; i < n - 1; ++i)
    {
        cout << tab[i] << ", ";
		if((i+1)%5 == 0) cout<<"|";
    }
    cout << tab[n - 1] << "}" << endl;
}

int partition(int A[], int p, int q)
{
    srand(time(NULL));
    int r = rand()%(q-p) + p; 
    int x = A[r]; // pivot
    int i = p;

    for (int j = p + 1; j <= q; j++)
    {
        porownania++;
        if (A[j] <= x)
        {
            i++;
            przestawienia++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i], A[p]);
    przestawienia++;
    return i;
}

int RandomSelect(int A[], int p, int q, int i){
    porownania++;
    if(p == q){
        return A[p];
    }
    int r = partition(A,p,q); // r - indeks pivota po wykonaniu RandPartition
    int k = r - p + 1; // statystyka pozycyjna pivota w A[p,...,q]

    porownania++;
    if(k == i)
        return A[r];

    porownania++;
    if(i < k)
        return RandomSelect(A, p, r-1, i);
    else
        return RandomSelect(A, r+1, q, i-k);
}

void merge_over50(int tab[], int l, int m, int r)
{

    int i = l;
    int j = m + 1;
    int k = l;

    int tempTab[r];

    while (i <= m && j <= r)
    {
        if (tab[i] <= tab[j])
        {
            tempTab[k] = tab[i];
            i++;
            k++;
        }
        else
        {
            tempTab[k] = tab[j];
            j++;
            k++;
        }
    }

    while (i <= m)
    {
        tempTab[k] = tab[i];
        i++;
        k++;
    }
    while (j <= r)
    {
        tempTab[k] = tab[j];
        j++;
        k++;
    }

    for (int p = l; p <= r; ++p)
    {
        tab[p] = tempTab[p];
    }
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

int main(int argc, char *argv[])
{
    int n;  // wielkosc tablicy 
    int x;  // kolejne elementy tablicy
    cin >> n;
    int tab[n];
    int k = stoi(argv[1]); //  

    for (int p = 0; p < n; p++)
    {
        cin >> x;
        tab[p] = x;
    }

    if(n<=50){
        cout<< "Tablica wejsciowa: " << endl;
        wypisz_tablice(n, tab);
        int odp = RandomSelect(tab, 0, n-1, k);
        cout << k << " najmniejszy element tablicy to: " << odp << endl;
        cout << "Tablica po wykonaniu selecta: " << endl;
        wypisz_tablice(n ,tab);
        cout << "Tablica po przesortowaniu: " << endl;
        mergeSort_over50(tab,0,n-1);
        wypisz_tablice(n,tab);
        cout << "Licznik przestawien: " << przestawienia << endl;
        cout << "Licznik porownan: " << porownania << endl;
    }
    else{
        int odp = RandomSelect(tab, 0, n-1, k);
        cout << n << " ";
        cout << przestawienia << " ";
        cout << porownania << endl;
    }

    return 0;
}
