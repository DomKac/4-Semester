#include "CRC.h" // Only need to include this header file!
                 // No libraries need to be included. No project settings need to be messed with.
				 
#include <iomanip>  // Includes ::std::hex
#include <iostream> // Includes ::std::cout
#include <cstdint>  // Includes ::std::uint32_t

using namespace std;

string generate_crc_pushed(const string encoded_mes, const size_t frame_size, const string crc_divider){

    string x = encoded_mes;

    int crc_lenght = crc_divider.length();
    x.append(crc_lenght-1, '0');

    cout << x << " = x" << endl;

    for (size_t i = 0; i < frame_size - 1; i++)
    {
        for (size_t k = 0; k < i; k++)
        {
            cout << " ";
        }
        cout << crc_divider << endl;
        if (x[i] == '1')
        {
            for (size_t j = 0; j < crc_lenght; j++)
            {
                if (x[i+j] == crc_divider[j])
                    x[i+j] = '0';
                else
                    x[i+j] = '1';            
            }
            cout << x << " = x in for" << endl;
        }
    }
    cout << "ending x = " << x << endl;
    
    return x.substr(frame_size);
}


bool check_crc(string message, string crc_divider){
    //crc divider = 1011
    //message ma postać 1001101101|101
    //mes_len = 13
    //crc_len = 4
    //crc divider = "1011"
    

    size_t crc_len = crc_divider.length();
    size_t mes_len = message.length();
    if (mes_len < crc_len){
        cout << "Frame NOT correct" << endl;
        return false;
    }

    cout << message << " = x" << endl;
    for (size_t i = 0; i < mes_len - (crc_len - 1) - 1; i++)
    {
        for (size_t k = 0; k < i; k++)
        {
            cout << " ";
        }
        cout << crc_divider << endl;
        if (message[i] == '1')
        {
            for (size_t j = 0; j < crc_len; j++)
            {
                if (message[i+j] == crc_divider[j])
                    message[i+j] = '0';
                else
                    message[i+j] = '1';            
            }
            cout << message << " = x in for" << endl;
        }
    }
    cout << "ending x = " << message << endl;
    string correct = "";
    correct.append(crc_len-1, '0');
    if (message.substr(mes_len-(crc_len-1)) == correct)
    {
        cout << "Frame correct" << endl;
        return true; 
    }
    else{
        cout << "Frame NOT correct" << endl;
        return false;
    }
}

int main(int argc, char ** argv)
{
	string dupa = "1234567890";
    size_t dupa_len = dupa.length();
    dupa = dupa.substr(dupa_len-8);
    string encoded_mes = "1101001110111";
    string crc = generate_crc_pushed(encoded_mes,13,"1011");
    string frame = encoded_mes + crc;
    cout << "frame ready ~~~~~~~~~~~~~~~~~~" << endl;
    cout << check_crc(frame, "1011")<< endl;
    cout << dupa;
    return 0;

}
// 1101001110111 000
// 1101001110111 010
// 1101001110111 010