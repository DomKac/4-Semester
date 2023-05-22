#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

// O(n): time
// O(n): memory

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        
        vector<vector<int>> v(numRows);

        
        for (size_t i = 0; i < numRows; i++)
        {
            v[i].resize(i + 1);
            v[i][0]= 1;
            for (size_t j = 1; j < i-1; j++)
            {
              v[i][j] = v[i-1][j-1] + v[i-1][j];
            }
            v[i][i] = 1;
        }
        
        return v;
    }
};
