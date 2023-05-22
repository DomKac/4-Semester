#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>

using namespace std;

int main(int argc, char *argv[])
{

    long n = strtol(argv[1], nullptr, 10);
    int limit = (2 * n) - 1;

    // seed
    random_device rd;
    seed_seq sd{rd(), rd(), rd(), rd(), rd()};
    auto g = mt19937(sd);

    // distribution
    auto u = uniform_int_distribution<int>(0, limit);

    string output = "";
    output = output + argv[1];

    for (int i = 0; i < n; ++i)
    {
        output = output + " " + to_string(u(g));
    }
    cout << output;
    return 0;
}