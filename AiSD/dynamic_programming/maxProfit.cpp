#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        size_t n = prices.size();   
        int* A = (int*)calloc(n, sizeof(int));
        int max = -1; // maksymalny zarobek
        int cheapest_day = INT32_MAX; // najtańsze cena
        A[0] = 0;
        for (size_t i = 1; i < n; i++) {
            if (prices[i] < prices[i-1]) {
                if (cheapest_day > prices[i]) {
                    cheapest_day = prices[i];
                    A[i] = 0;
                }
                else {
                    A[i] = A[i-1];
                }
            }
            else {
                A[i] = prices[i] - cheapest_day;
                max = A[i];
            }
            
        }
        free(A);
        return max;

    }
};


class Solution2 {
public:
    int maxProfit(vector<int>& prices) {
        size_t n = prices.size();   
        int max = -1; // maksymalny zarobek
        int cheapest_day = prices[0]; // najtańsze cena
        for (size_t i = 1; i < n; i++) {
            if (prices[i] < prices[i-1]) {
                cheapest_day = min(cheapest_day, prices[i]);
            }
            else {
                max = prices[i] - cheapest_day;
            }
            
        }

        return max;

    }
};
