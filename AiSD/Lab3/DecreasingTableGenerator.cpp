#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
    // int d = atoi(argv[1]);
    long n = strtol(argv[1], nullptr, 10);
    string output = "";

    output = output + argv[1];

    for (int i = n; i > 0; --i)
    {
        output = output + " " + to_string(i);
    }

    cout << output;
    return 0;
}
