#include <iostream>

using namespace std;

int przestawienia;
int porownania;

void wypisz_tablice(int n, int tab[])
{

    cout << " {";
    for (int i = 0; i < n - 1; ++i)
    {
        cout << tab[i] << ", ";
    }
    cout << tab[n - 1] << "}" << endl;
}

int partition_less50(int A[], int p, int q, int n)
{
    int x = A[p]; // pivot
    int i = p;

    for (int j = p + 1; j <= q; j++)
    {
        porownania++;
        if (A[j] <= x)
        {
            i++;
            if (A[i] != A[j])
            {
                przestawienia++;
                swap(A[i], A[j]);
            }
            wypisz_tablice(n, A);
        }
    }
    if (i != p)
    {
        swap(A[i], A[p]);
        przestawienia++;
    }
    return i;
}

int partition_over50(int A[], int p, int q)
{
    int x = A[p]; // pivot
    int i = p;

    for (int j = p + 1; j <= q; j++)
    {
        porownania++;
        if (A[j] <= x)
        {
            i++;
            // if (A[i] != A[j])
            //{
            przestawienia++;
            swap(A[i], A[j]);
            //}
        }
    }
    // if (i != p)
    //{
    swap(A[i], A[p]);
    przestawienia++;
    //}
    return i;
}

void quickSort_less50(int tab[], int start, int end, int n)
{
    // base case
    if (start >= end)
        return;

    // partitioning the array
    int p = partition_less50(tab, start, end, n);

    // Sorting the left part
    quickSort_less50(tab, start, p - 1, n);

    // Sorting the right part
    quickSort_less50(tab, p + 1, end, n);
}

void quickSort_over50(int arr[], int start, int end)
{
    // base case
    if (start >= end)
        return;

    // partitioning the array
    int p = partition_over50(arr, start, end);

    // Sorting the left part
    quickSort_over50(arr, start, p - 1);

    // Sorting the right part
    quickSort_over50(arr, p + 1, end);
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
        quickSort_less50(tab, 0, n - 1, n);
        wypisz_tablice(n, tab);

        cout << endl;
        cout << "Licznik przestawien: " << przestawienia << endl;
        cout << "Licznik porownan: " << porownania << endl;
      

    }
    else
    {
        const clock_t begin_time = clock();
        quickSort_over50(tab, 0, n - 1);
        const clock_t end_time = clock();
        float czas = float(end_time - begin_time) / CLOCKS_PER_SEC;
        cout << n << " " << przestawienia << " " << porownania << " " << czas*1000 << endl;
    }

    return 0;
}
