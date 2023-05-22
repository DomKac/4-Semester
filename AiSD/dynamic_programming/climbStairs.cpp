#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

// Brute Force
// O(2^n): time
// O(n): memory
class Solution {
public:
    int climbStairs(int n) {
        if (n == 0) return 1;
        
         size_t counter = 0;

         if (n>1) counter += climbStairs(n-2);

         counter += climbStairs(n-1);


        return counter;    
    }
};

#include <algorithm>
#include <vector>

using namespace std;
// Dynamic programming
// O(2^n): time
// O(n): memory
class Solution2 {
public:
    int climbStairs(int n) {
        
        int* memo = (int*)calloc(n+1, sizeof(int));
        fill_n(memo, n+1, -1);
        int odp = climbStairs2(n, memo);
        free(memo);
        return odp;
    }
    
    int climbStairs2(int n, int memo[]) {
        
        if (memo[n] != -1) return memo[n];
        if (n == 0) return 1;
        
        size_t counter = 0;

        if (n>1) counter += climbStairs2(n-2, memo);
        
        counter += climbStairs2(n-1, memo);

        memo[n] = counter;
        return counter;    
    }
};
