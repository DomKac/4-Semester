#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

// Time: O(n)
// Memory: O(1)

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        size_t n = prices.size();   
        int maximum = 0; // maksymalny zarobek
        int current_cheapest_price = prices[0]; // najtańsze cena
        int best_transaction_1 = 0;
        int best_transaction_2 = 0;

        // 7 , 1 , 5 ,3 , 6, 4

        for (size_t i = 1; i < n; i++) {
            if (prices[i] < prices[i-1]) {
                current_cheapest_price = prices[i];
                if (maximum > best_transaction_1){
                    best_transaction_2 = best_transaction_1;
                    best_transaction_1 = maximum;
                }
                else {
                    best_transaction_2 = max(best_transaction_2, maximum);
                }                
                maximum = 0;
            }
            else {
                maximum = prices[i] - current_cheapest_price;   // 4    
            }
        }
        
        if (maximum > best_transaction_1){
            best_transaction_2 = best_transaction_1;
            best_transaction_1 = maximum;
        }
        else {
            best_transaction_2 = max(best_transaction_2, maximum);
        }        

        return best_transaction_1 + best_transaction_2;

    }
};

