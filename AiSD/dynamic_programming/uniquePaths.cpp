#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory.h>

using namespace std;



class BruteForceSolution {
public:
    int uniquePaths(int m, int n) {
    
        return uniquePathsrecursion(m,n,0,0);

    }

    int uniquePathsrecursion(int m, int n, int i, int j) {
        
        if (i == m - 1 && j == n - 1) return 1;

        int counter = 0;

        if (i<m-1) counter += uniquePathsrecursion(m,n,i+1,j);

        if (j<n-1) counter += uniquePathsrecursion(m,n,i,j+1);

        return counter;
    }
    
    
};

// DP Solution

class Solution {
public:
    int uniquePaths(int m, int n) {
        
        int** A = (int**)calloc(m, sizeof(int*));
        for (size_t i = 0; i < m; i++) {
            *A = (int*)calloc(n, sizeof(int));
        }
        // fill(&A[0][0], &A[0][0] + sizeof(A), -1); // uzupełeniamy całą tablice wartością (-1);
        // memset(&A[0][0], -1, sizeof(A));
        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                A[i][j] = -1;
            }
            
        }
        
        int odp = uniquePathsrecursion(m,n,0,0, A);
        free(A);
        return odp;

    }

    int uniquePathsrecursion(int m, int n, int i, int j, int** memo) {
        
        if (memo[i][j] != -1) return memo[i][j];

        if (i == m - 1 && j == n - 1) return 1;

        int counter = 0;

        if (i<m-1) counter += uniquePathsrecursion(m,n,i+1,j, memo);

        if (j<n-1) counter += uniquePathsrecursion(m,n,i,j+1, memo);


        memo[i][j] = counter;
        return counter;
    }
    
    
};
