#include <iostream>
#include <random>

using namespace std;

int main()
{
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(25, 63); // define the range

    for(int n=0; n<40; ++n)
        cout << distr(gen) << ' '; // generate numbers
}