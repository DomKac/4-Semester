#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

bool countConstruct(string target, string wordBank[], size_t n, map<string,size_t> memo) {

    if (memo.find(target) != memo.end()) return memo[target];
    if (target == "") return 1;

    size_t counter = 0;

    for (size_t i = 0; i < n; i++) {
        if (target.find(wordBank[i]) == 0){ // jeżeli target zaczyna się od słowa z tablicy wordbank
            size_t numWaysForRest = countConstruct(target.substr(wordBank[i].length()), wordBank, n, memo);
            counter += numWaysForRest;
        }
    }
    memo[target] = counter;
    return counter;
}

int countConstruct2(string target, string wordBank[], size_t n) {

    int* A = (int* )calloc((target.length()+1), (sizeof(int)));
    for (size_t i = 1; i <= target.length(); i++) {
        A[i] = 0;
    }
    A[0] = 1; // puste słowo zawsze możemy ułożyć na jeden sposób
    for (size_t i = 0; i <= target.length(); i++) {
        cout << A[i] << "\t";
    }
    cout << endl;
    for (size_t i = 0; i <= target.length(); i++) {
        for (size_t j = 0; j < n; j++) {  
            if ((target.length() - i >= wordBank[j].length()) && (target.substr(i, wordBank[j].length()) == wordBank[j]))
            {
                A[i+wordBank[j].length()] += A[i];
            }
            
        }
        
    }
    int odp = A[target.length()];
    for (size_t i = 0; i <= target.length(); i++) {
        cout << A[i] << "\t";
    }
    cout << endl;
    free(A);
    return odp;
}

int main(void) {

    string wordBank[] = {"purp", "p", "le", "ur", "purpl" };
    string target = "purple";
    cout << target.length() << endl;
    cout << countConstruct2(target, wordBank, 5) << endl;

    return EXIT_SUCCESS;
}
