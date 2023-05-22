#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
    long n = strtol(argv[1], nullptr, 10);
    string output = "";

    output = output + argv[1];

    for (int i = 1; i <= n; ++i)
    {
        output = output + " " + to_string(i);
    }

    cout << output;
    return 0;
}
