#include <iostream>

using namespace std;

int licznik_przestawien;
int licznik_porownan;

int part1, part2;

void wypisz_tablice(int n, int tab[])
{

    cout << " {";
    for (int i = 0; i < n - 1; ++i)
    {
        cout << tab[i] << ", ";
    }
    cout << tab[n - 1] << "}" << endl;
}

void partition_less50(int A[], int left, int right, int n)
{
    int x = A[left];  // pivot 1
    int y = A[right]; // pivot 2

    int i = left + 1;
    int k = right - 1;
    int j = i;
    int d = 0;

    if (x > y)
    {
        licznik_przestawien++;
        licznik_porownan++;
        swap(A[left], A[right]);
        x = A[left];
        y = A[right];
    }
    wypisz_tablice(n, A);
    cout << "pivot1: " << x << " | pivot2: " << y << endl;

    while (j <= k)
    {
        if (d >= 0)
        {
            licznik_porownan++;
            if (A[j] < x)
            {
                licznik_przestawien++;
                swap(A[i], A[j]);
                i++;
                j++;
                d++;
                wypisz_tablice(n, A);
            }
            else
            {
                licznik_porownan++;
                if (A[j] < y)
                {
                    j++;
                }
                else
                {
                    licznik_przestawien++;
                    swap(A[j], A[k]);
                    k--;
                    d--;
                    wypisz_tablice(n, A);
                }
            }
        }
        else
        {
            licznik_porownan++;
            if (A[k] > y)
            {
                k--;
                d--;
            }
            else
            {
                licznik_porownan++;
                if (A[k] < x)
                {
                    licznik_przestawien = licznik_przestawien + 3;
                    int tmp = A[k];
                    A[k] = A[j];
                    A[j] = A[i];
                    A[i] = tmp;
                    i++;
                    d++;
                    wypisz_tablice(n, A);
                }
                else
                {
                    licznik_przestawien++;
                    swap(A[j], A[k]);
                    wypisz_tablice(n, A);
                }
                j++;
            }
        }
    }

    licznik_przestawien = licznik_przestawien + 2;
    swap(A[left], A[i - 1]);
    swap(A[right], A[k + 1]);
    part1 = i - 1;
    part2 = k + 1;
    wypisz_tablice(n, A);
}

void partition_over50(int A[], int left, int right)
{
    int x = A[left];  // pivot 1
    int y = A[right]; // pivot 2

    int i = left + 1;
    int k = right - 1;
    int j = i;
    int d = 0;

    if (x > y)
    {
        licznik_przestawien++;
        licznik_porownan++;
        swap(A[left], A[right]);
        x = A[left];
        y = A[right];
    }

    while (j <= k)
    {
        if (d >= 0)
        {
            licznik_porownan++;
            if (A[j] < x)
            {
                licznik_przestawien++;
                swap(A[i], A[j]);
                i++;
                j++;
                d++;
            }
            else
            {
                licznik_porownan++;
                if (A[j] < y)
                {
                    j++;
                }
                else
                {
                    licznik_przestawien++;
                    swap(A[j], A[k]);
                    k--;
                    d--;
                }
            }
        }
        else
        {
            licznik_porownan++;
            if (A[k] > y)
            {
                k--;
                d--;
            }
            else
            {
                licznik_porownan++;
                if (A[k] < x)
                {
                    licznik_przestawien = licznik_przestawien + 3;
                    int tmp = A[k];
                    A[k] = A[j];
                    A[j] = A[i];
                    A[i] = tmp;
                    i++;
                    d++;
                }
                else
                {
                    licznik_przestawien++;
                    swap(A[j], A[k]);
                }
                j++;
            }
        }
    }

    licznik_przestawien = licznik_przestawien + 2;
    swap(A[left], A[i - 1]);
    swap(A[right], A[k + 1]);
    part1 = i - 1;
    part2 = k + 1;
}

void dualPivotQuickSort_less50(int arr[], int start, int end, int n)
{
    // base case
    if (start >= end)
        return;

    // partitioning the array
    partition_less50(arr, start, end, n);

    // Sorting the left part
    dualPivotQuickSort_less50(arr, start, part1 - 1, n);

    // Sorting the middle part
    dualPivotQuickSort_less50(arr, part1 + 1, part2 - 1, n);

    // Sorting the right part
    dualPivotQuickSort_less50(arr, part2 + 1, end, n);
}

void dualPivotQuickSort_over50(int arr[], int start, int end)
{
    // base case
    if (start >= end)
        return;

    // partitioning the array
    partition_over50(arr, start, end);

    // Sorting the left part
    dualPivotQuickSort_over50(arr, start, part1 - 1);

    // Sorting the middle part
    dualPivotQuickSort_over50(arr, part1 + 1, part2 - 1);

    // Sorting the right part
    dualPivotQuickSort_over50(arr, part2 + 1, end);
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
        dualPivotQuickSort_less50(tab, 0, n - 1, n);
        wypisz_tablice(n, tab);
        cout << endl;
        cout << "Licznik przestawien: " << licznik_przestawien << endl;
        cout << "Licznik porownan: " << licznik_porownan << endl;
    }
    else
    {
        dualPivotQuickSort_over50(tab, 0, n - 1);
        cout << n << " ";
        cout << licznik_przestawien << " ";
        cout << licznik_porownan << endl;
    }

    return 0;
}