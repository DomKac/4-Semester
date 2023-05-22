#include <iostream>
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
int select_Select(int* nums, int left, int right, int k, int size, int divide_size);
void select_swap(int* nums, int index1, int index2);
int select_partition(int* list, int left, int right, int pivotIndex, int n);
int select_partition_small(int* nums, int left, int right);

void select_swap(int* nums, int index1, int index2){
    int temp = nums[index1];
    nums[index1] = nums[index2];
    nums[index2] = temp;
    przestawienia += 3; // 
}

int select_partition(int* list, int left, int right, int pivotIndex, int n){
    int pivotValue = list[pivotIndex];
    select_swap(list, pivotIndex, right); // move pivot to an end
    int storeIndex = left;
    // move all elements smaller than the pivot to the left of the pivot;
    for (int i = left; i <= right-1; i++){
        porownania+=2;
        if (list[i] < pivotValue){
            select_swap(list, storeIndex, i);
            storeIndex++;
        }
    }
    // Move all elements equal to the pivot right after the smaller elements
    int storeIndexEq = storeIndex;
    for (int i = storeIndex; i <= right-1; i++){
        porownania+=2;
        if(list[i] == pivotValue){
            select_swap(list, storeIndexEq, i);
            storeIndexEq++;
        }
    }
    select_swap(list, right, storeIndexEq); // Move pivot to its final place
    // Return location ofpivot considering the desired locaiton n
    porownania++;
    if (n < storeIndex) return storeIndex;
    porownania++;
    if (n <= storeIndexEq) return n;
    return storeIndexEq;  
}

int select_partition_small(int* nums, int left, int right){
    int i = left+1;
    porownania++;
    while (i <= right){
        int j = i;
        porownania+=2;
        while ( j > left && nums[j-1] > nums[j]){
            select_swap(nums, j-1, j);
            j--;
            porownania+=2;
        }
        i++;
        porownania++;
    }
    return (left+right)/2;
}

int select_pivot(int* nums, int left, int right, int size, int divide_size){
    // for 5 or less elements just get median
    porownania++;
    if (right - left < divide_size) return select_partition_small(nums, left, right);
    // otherwise move the medians of five-element subgroups to the first n/5 positions
    for ( int i = left; i <= right; i+= divide_size){
        porownania++;
        // get the median of the i'th five element subgroup
        int subRight = i+divide_size-1;
        porownania++;
        if (subRight > right) subRight = right;

        int median5 = select_partition_small(nums, i, subRight);
        select_swap(nums, median5, left + (i-left) / divide_size);
    }
    int mid = (right - left) / (divide_size*2) + left + 1;
    return select_Select(nums, left, left + (right-left)/divide_size, mid, size, divide_size);
}

int select_Select(int* nums, int left, int right, int k, int size, int divide_size){
    porownania++;
    while (1){
        porownania++;
        if (left == right) return left;

        int pivot_index = select_pivot(nums, left, right, size, divide_size);
        pivot_index = select_partition(nums, left, right, pivot_index, k);
        if (size < 50){
            wypisz_tablice(nums, size);
        }

        porownania++;
        if (k==pivot_index){
            return k; 
        } else if (k < pivot_index){
            porownania++;
            right = pivot_index - 1;
        } else {
            porownania++;
            left = pivot_index + 1;
        }
    }
}

int select_select(int* nums, int n, int k, int size, int divide_size){
    return select_Select(nums, 0, n-1, k-1, size, divide_size);
}

void swap(int* a, int* b)
{
    int temp = *a; 
    *a = *b;
    *b = temp;
    przestawienia += 3; // swap to zawsze trzy są dla mnie
}
 
void DualPivotQuickSort(int* arr, int low, int high, int n)
{
    if (low < high) {
        porownania++; 
        int lp, rp;
        rp = partition(arr, low, high, &lp);
        DualPivotQuickSort(arr, low, lp - 1,n);
        DualPivotQuickSort(arr, lp + 1, rp - 1,n);
        DualPivotQuickSort(arr, rp + 1, high,n);
        if (n < 50){
            wypisz_tablice(arr, n);
        }
    }
}
 
int partition(int* arr, int low, int high, int* lp)
{
    // p is the left pivot, and q is the right pivot.
    int pivot_index1 = select_pivot(arr, low, high, 100, 5);
    swap(&arr[low], &arr[pivot_index1]);
    int pivot_index2 = select_pivot(arr, low+1, high, 100, 5);
    swap(&arr[high], &arr[pivot_index2]);

    if (arr[low] > arr[high]){
        porownania++; // jest porownanko
        swap(&arr[low], &arr[high]);
    }
    
    int j = low + 1;
    int g = high - 1, k = low + 1, p = arr[low], q = arr[high];
    while (k <= g) {
        porownania++;
        // if elements are less than the left pivot
        if (arr[k] < p) {
            porownania++;
            swap(&arr[k], &arr[j]);
            j++;
        }
 
        // if elements are greater than or equal
        // to the right pivot
        else if (arr[k] >= q) {
            porownania++; 
            while (arr[g] > q && k < g){
                porownania++; 
                g--;
            }
            swap(&arr[k], &arr[g]);
            g--;
            if (arr[k] < p) {
                porownania++; 
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
    std::cin >> n;
    int tab[n];

    for(int i = 0; i < n; i++){
        std::cin >> tab[i];
    }
    if(n < 50){
        cout << "Wejsciowa tablica: " ;
        wypisz_tablice(tab, n);
        DualPivotQuickSort(tab, 0, n-1, n);
        cout << "Wyjsciowa tablica: " ;
        wypisz_tablice(tab, n);
    }
    else{
        const clock_t begin_time = clock();
        DualPivotQuickSort(tab, 0, n-1, n);
        const clock_t end_time = clock();
        float czas = float(end_time - begin_time) / CLOCKS_PER_SEC;
        cout << n << " " << przestawienia << " " << porownania << " " << czas*1000 << endl;
    } 
}