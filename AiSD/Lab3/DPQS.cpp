#include<iostream>
#include<algorithm>
#include<climits>

using namespace std;

long int porownania = 0;
long int przestawienia = 0;

void wypisz_tablice(int tab[], int n)
{
    std::cout << " {";
    for (int i = 0; i < n - 1; ++i)
    {
        cout << tab[i] << ", ";
		if((i+1)%5 == 0) cout<<"|";
    }
    cout << tab[n - 1] << "}" << endl;
}

int partition(int* arr, int low, int high, int* lp);

void swap(int* a, int* b)
{
    int temp = *a; 
    *a = *b;
    *b = temp;
    przestawienia += 3; // swap to zawsze trzy są dla mnie
}
 
void DualPivotQuickSort(int* arr, int low, int high)
{
    porownania++;
    if (low < high) {
        // lp means left pivot, and rp means right pivot.
        int lp, rp;
        rp = partition(arr, low, high, &lp);
        DualPivotQuickSort(arr, low, lp - 1);
        DualPivotQuickSort(arr, lp + 1, rp - 1);
        DualPivotQuickSort(arr, rp + 1, high);
    }
}
 
int partition(int* arr, int low, int high, int* lp)
{
    porownania++;
    if (arr[low] > arr[high]){
         // jest porownanko
        swap(&arr[low], &arr[high]);
    }
    // p is the left pivot, and q is the right pivot.
    int j = low + 1;
    int g = high - 1, k = low + 1, p = arr[low], q = arr[high];
    while (k <= g) {
        porownania++; // jest porownanko
        // if elements are less than the left pivot
        porownania++;
        if (arr[k] < p) {
            swap(&arr[k], &arr[j]);
            j++;
        }
 
        // if elements are greater than or equal
        // to the right pivot
        else if (arr[k] >= q) {
            porownania+=3; // jest porownanko
            while (arr[g] > q && k < g){
                porownania+=2; // jest porownanko
                g--;
            }
            swap(&arr[k], &arr[g]);
            g--;
            if (arr[k] < p) {
                porownania++; // jest porownanko
                swap(&arr[k], &arr[j]);
                j++;
            }
        }
        k++;
    }
    j--;
    g++;
 
    // bring pivots to their appropriate positions.
    swap(&arr[low], &arr[j]);
    swap(&arr[high], &arr[g]);
 
    // returning the indices of the pivots.
    *lp = j; // because we cannot return two elements
    // from a function.
 
    return g;
}

int main(){
    int n;
    cin >> n;
    int tab[n];

    for(int i = 0; i < n; i++){
        cin >> tab[i];
    }
    if(n < 50){
        cout << "Wejsciowa tablica: " ;
        wypisz_tablice(tab, n);
        DualPivotQuickSort(tab, 0, n-1);
        cout << "Wyjsciowa tablica: ";
        wypisz_tablice(tab, n);
    }
    else{
        const clock_t begin_time = clock();
        DualPivotQuickSort(tab, 0, n-1);
        const clock_t end_time = clock();
        float czas = float(end_time - begin_time) / CLOCKS_PER_SEC;
        cout << n << " " << przestawienia << " " << porownania << " " << czas*1000 << endl;
    } 
}