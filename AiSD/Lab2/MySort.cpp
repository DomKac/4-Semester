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

void insertionSort_over50(int tab[], int left, int right)
{
    int key;
    int j;
    for (int i = left + 1; i <= right; ++i)
    {
        key = tab[i];
        j = i - 1;
        while (j >= left && key < tab[j])
        {
            licznik_porownan++;
            licznik_przestawien++; // niepewne
            tab[j + 1] = tab[j];
            j--;
        }
        if (j >= left)
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

int partition_over50(int A[], int p, int q)
{
    int x = A[p]; // pivot
    int i = p;

    for (int j = p + 1; j <= q; j++)
    {
        licznik_porownan++;
        if (A[j] <= x)
        {
            i++;
            licznik_przestawien++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i], A[p]);
    licznik_przestawien++;
    return i;
}

void mySort(int arr[], int low, int high, int change)
{
    while (low < high)
    {

        // If the size of the array is less
        // than threshold apply insertion sort
        // and stop recursion

        if (high - low + 1 <= change)
        {
            insertionSort_over50(arr, low, high);
            break;
        }

        else

        {
            int pivot = partition_over50(arr, low, high);

            // Optimised quicksort which works on
            // the smaller arrays first

            // If the left side of the pivot
            // is less than right, sort left part
            // and move to the right part of the array

            if (pivot - low < high - pivot)
            {
                mySort(arr, low, pivot - 1, change);
                low = pivot + 1;
            }
            else
            {

                // If the right side of pivot is less
                // than left, sort right side and
                // move to the left side

                mySort(arr, pivot + 1, high, change);
                high = pivot - 1;
            }
        }
    }
}
int main(int argc, char *argv[])
{
    int changer = 4; // USTALAMY PUNKT W KTORYM OPLACA SIE ZMIENIAC
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
        mySort(tab, 0, n - 1, changer);
        wypisz_tablice(n, tab);
        cout << endl;
        cout << "Licznik przestawien: " << licznik_przestawien << endl;
        cout << "Licznik porownan: " << licznik_porownan << endl;
    }
    else
    {
        mySort(tab, 0, n - 1, changer);
        cout << n << " ";
        cout << licznik_przestawien << " ";
        cout << licznik_porownan << endl;
    }

    return 0;
}
