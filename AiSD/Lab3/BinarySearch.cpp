// C++ implementation of worst case linear time algorithm
// to find k'th smallest element
#include<iostream>
#include<algorithm>
#include<climits>

using namespace std;

long int porownania = 0;
long int przestawienia = 0;

void wypisz_tablice(int tab[], int n)
{
    cout << " {";
    for (int i = 0; i < n - 1; ++i)
    {
        cout << tab[i] << ", ";
		if((i+1)%5 == 0) cout<<"|";
    }
    cout << tab[n - 1] << "}" << endl;
}
/**
 * @brief 
 * 
 * @param tab = tablica w ktorej szukamy elementu v 
 * @param l = index pierwszego elementu tablicy
 * @param r = index ostatnigo elementu tablicy
 * @param v = element ktorego szukamy
 * @return int 1 jesli element v jest w tab[], w przciwnym razie 0
 */
int binarySearch(int tab[], int l, int r, int v){

        int n = r-l+1;
        
        if(v == tab[l+(n/2)]){
            porownania++;
            return 1;
        }
        else if(l>=r){
            return 0;
        }
        else if(v < tab[l+n/2]){
            porownania+=2;
            return binarySearch(tab, l, l + n/2 - 1, v);
        }
        else{
            porownania+=2;
            return binarySearch(tab, l + n/2 + 1, r, v);
        }

// [1,3,5,|7|,13,15,19] n = 7 -> tab[n/2] = 7 niech v = 19
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

// Driver program to test above methods
int main(int argc, char *argv[])
{
	int n;  // wielkosc tablicy 
    int x;  // kolejne elementy tablicy
    cin >> n;
    int tab[n];

    for(int p = 0; p < n; p++)
    {
        cin >> x;
        tab[p] = x;
    }

    if(n<=50){
        int v = stoi(argv[1]);
        //int trash = stoi(argv[2]); 
        mergeSort_over50(tab,0,n-1);
        wypisz_tablice(tab,n);
        cout << "Czy tab zawiera " << v << "?" << endl;
        cout << "Odp: " << binarySearch(tab,0,n-1,v) << endl;
    }
    else{
        int l_limit = stoi(argv[1]);
        int r_limit = stoi(argv[2]);
        mergeSort_over50(tab,0,n-1);

        if(l_limit == 0 && r_limit == 0){
            const clock_t begin_time = clock();
            // mamy pewność ze element znajdzie sie w tablicy
            int test = binarySearch(tab,0,n-1, 3*n); // po uruchomieniu programu z argumentami 0 0 bierzemy element spoza tablicy
            const clock_t end_time = clock();
            float czas = float(end_time - begin_time) / CLOCKS_PER_SEC;
            cout << n << " " << porownania << " " << czas*1000 << endl;
        }
        else{
            srand(time(NULL));
            int random_indeks = rand()%(r_limit - l_limit) + l_limit;
            cout << "random index = " << random_indeks << endl;
            const clock_t begin_time = clock();
            // mamy pewność ze element znajdzie sie w tablicy
            int test = binarySearch(tab,0,n-1,tab[random_indeks]);
            const clock_t end_time = clock();
            float czas = float(end_time - begin_time) / CLOCKS_PER_SEC;
            cout << n << " " << porownania << " " << czas*1000 << endl; 
        }
    }
    
	return 0;
}
