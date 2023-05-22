#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

int main()
{
    int n;
    int x;
    cin >> n;
    int tab[n];

    for (int p = 0; p < n; p++){
        cin >> x;
        tab[p] = x;
    }

    cout << "Output programu inputtest: " << endl;
    cout << "n = " << n << endl;
    cout << "[ ";

    for (int k = 0; k < n; k++)
    {
        cout << tab[k] << " ";
    }

    cout << "]" << endl;

    return 0;
}