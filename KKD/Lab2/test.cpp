#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

// function to convert decimal to binary

int intToAscii(int number)
{
    return '0' + number;
}
string decToBinary(int n)
{
    string binary = "";

    int binaryNum[32];

    int i = 0;
    while (n > 0)
    {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int z = 0; z < 8 - i; z++)
    {
        binary = binary + "0";
    }

    for (int j = i - 1; j >= 0; j--)
        binary = binary + to_string(binaryNum[j]);

    return binary;
}

void rozpierdolBity(unsigned char my_char)
{
    int what_bit_i_am_testing = 0;

    while (what_bit_i_am_testing < 8)
    {
        if (my_char & 0x01) // prawda kiedy bit = 1
        {
            printf("1");
        }
        else
        {
            printf("0");
        }

        what_bit_i_am_testing++;
        my_char = my_char >> 1;
    }
}

int binToDec(string bin) // "01110011"
{
    // dec = 0 +
    int dec = 0;

    for (size_t i = 0; i < bin.length(); i++)
    {
        if (bin[i] == '1')
        {
            dec = dec + pow(2, (bin.length() - i - 1));
        }
    }

    return dec;
}

int main()
{

    string car = "Dominik_Kaczmarek";
    string result = car.substr(8);
    cout << result << endl;
    cout << car;

    string str1 = "Apples are red";
    string str2 = str1.substr(11, 3);
    string str3 = str1.substr(0, 6);

    cout << "Substring starting at position 11 and length 3 is: " << str2 << endl;
    cout << "Substring starting at position 0 and length 6 is: " << str3 << endl;

    FILE *myfile;
    myfile = fopen("/home/dominik/Studia/KKD/Lab2/a.txt", "w");

    int n = 100;
    fwrite(&n, 2, 1, myfile);

    fclose(myfile);
    FILE *f = freopen("a.txt", "rb", stdin);
    int x = getchar();
    x |= getchar() << 8;
    cout << x << endl;

    fclose(f);


    return 0;
}
