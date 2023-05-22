#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;


class Solution {
public:
    int numTrees(int n) {

        if (n == 0) return 1;

        int counter = 0;

        counter += numTrees(n-1);
        counter += numTrees(n-1);

        return counter;        

    }
};
