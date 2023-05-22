#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

// O(n): time
// O(n): memory
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int A[nums.size()];
        A[0] = nums[0];
        int max = nums[0];
        for (size_t i = 1; i < nums.size(); i++)
        {
            if (A[i-1] + nums[i] < nums[i])
            {
                A[i] = nums[i];
            }
            else{
                A[i] = A[i-1] + nums[i];
            }
            if (A[i] > max)
            {
                max = A[i];
            }
        }  
        return max;
    }
};
