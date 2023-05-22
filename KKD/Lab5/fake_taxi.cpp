// b g r | b g r | b g r
// b g r | b g r | b g r 
// b g r | b g r | b g r 
// b g r | b g r | b g r 
// b g r | b g r | b g r 
// b g r | b g r | b g r 
// b g r | b g r | b g r 
// b g r | b g r | b g r 
// b g r | b g r | b g r 

#include <iostream>
#include <cmath>
using namespace std;

struct Pixel
{
    int r;
    int g;
    int b;
};

int modulo(int x, int y){
    int z = x%256;
    if (z >= 0){
        return z;
    }
    else{
        return y + z;
    }
}

int main(void)
{
 
    size_t a = 3;
    size_t b = 100;
    double c = (double)(b/a);

    cout << round(c) << ", " << c <<endl;
    cout << sizeof((uint8_t)round(c)) << endl;


return 0;
}
//
//
//
//
//
//
//