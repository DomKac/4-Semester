#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int knapsack(int value[], int weight[], size_t n, int W, size_t i);
int knapsack(int value[], int weight[], size_t n, int W, size_t i) {

    if(W == 0 || i == n) return 0;
    if (W < 0)
    {
        return INT32_MIN;
    }
    
    int maks = 0;
    int sum = 0;
    printf("(Przed 2 knapsackiem) i = %zu\t W = %d\t maks = %d\n", i, W, maks);
    maks = knapsack(value, weight, n, W, i+1);
    printf("(Przed 1 knapsackiem) i = %zu\t W = %d\t maks = %d\n", i, W, maks);
    maks = knapsack(value, weight, n, W - weight[i], i+1);
    sum += value[i]; 

    maks = max(maks, sum);
    printf("(Przed returnem maksa) i = %zu\t W = %d\t maks = %d\n", i, W, maks);

    return maks;
}

int knapsack2(int values[], int weights[], size_t n, int W) {
    // given N, maxWeight, weights and values
    long d[n + 1][W + 1];
    
    for (long i = 0; i < n; i++)
    {
    	for (long w = 0; w <= W; w++)
    	{                    
    		if (weights[i] <= w)
    		{
    			// Exclude or include
    			d[i + 1][w] = max(d[i][w], d[i][w - weights[i]] + values[i]);
    		}
    
    		else
    		{
    			// Exclude
    			d[i + 1][w] = d[i][ w];
    		}                    
    	}
    }

    return d[n][W];
}

int main(void) {

    int value[6] = {20,5,10,40,15,25};
    int weight[6] = {1,2,3,8,7,4};

        int odp = knapsack2(value, weight, 6, 10);

    cout << odp << endl;

    return EXIT_SUCCESS;
}
