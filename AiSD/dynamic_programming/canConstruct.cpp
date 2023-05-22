#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

bool canConstruct(string target, string wordBank[], size_t n, map<string,bool> memo) {

    if (memo.find(target) != memo.end()){
        cout << "target " << target << endl;
        return memo[target];
    }
    if (target == "") return true;

    for (size_t i = 0; i < n; i++) {
        if (target.find(wordBank[i]) == 0){ // jeżeli target zaczyna się od słowa z tablicy wordbank
            string suffix = target.substr(wordBank[i].length());
            cout << "suffix " << suffix << endl;
            if(canConstruct(suffix, wordBank, n, memo) == true) {
                memo[target] = true;
                return true;
            }
        }
    }
    memo[target] = false;
    return true;
}

int main(void) {

    size_t n = 7;
    string wordBank[7] = {"bo","rd","ate", "t", "ska", "sk", "boar", };
    string target = "skateboard";
    map<string,bool> memo;
    cout << canConstruct(target, wordBank, n, memo) << endl;

    return EXIT_SUCCESS;
}
