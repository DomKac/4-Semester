#include <iostream>
#include <fstream>

using namespace std;

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

string get_n_bits(ifstream &file, size_t n){

    string str = "";
    char bit;
    if(file.eof())
        return "";
    for (size_t i = 0; i < n; i++)
    {
        file >> noskipws >> bit;
        str = str + bit;
        if(file.eof())
            break;
    }
    return str;
}

string decode_message(string message, const string crc_divider){

    
    size_t mes_len = message.length()-(crc_divider.length()-1);

    int counter_1 = 0;
    string dec_mes = ""; 

    for (size_t i = 0; i < mes_len; i++)
    {
        dec_mes = dec_mes + message[i];
        
        if (message[i] == '0')
            counter_1 = 0;
        else
            counter_1++;

        if (counter_1 == 5){
            i++;
            counter_1 = 0;
        }  
    }

    return dec_mes;
}

int main(void){

    ifstream W;
    W.open("W.txt");
    ofstream Z;
    Z.open("Z_decoded.txt");

    string znacznik = "01111110";
    size_t znacznik_len = znacznik.length();
    string crc_divider = "1011";
    string message="";
    string ending_flag;
    string starting_flag;
    size_t mes_len;
    char bit;
    bool starting_flag_ok;
    bool ending_flag_ok;

    starting_flag = get_n_bits(W ,znacznik_len);
    if (znacznik == starting_flag)
        starting_flag_ok = true;
    else
         starting_flag_ok = false;
    
    while(!W.eof()){
        //check_znacznik(znacznik,starting_flag);
        for (size_t i = 0; i < znacznik_len; i++)
        {
            if(W.eof())
                break;
            W >> noskipws >> bit;
            message = message + bit;
        }
        
        if(message == znacznik){
            message=get_n_bits(W,znacznik_len);
        }

        mes_len = message.length();
        
        while(znacznik != message.substr(mes_len-8))
        {
            if(W.eof())
                break;
            W >> noskipws >> bit;
            message = message + bit;
            mes_len++;
        }

        ending_flag = message.substr(mes_len-znacznik_len);
        message = message.substr(0, mes_len-znacznik_len); // 
        
        if (check_crc(message, crc_divider))
        {
            if (starting_flag_ok)
            {  
                Z << decode_message(message, crc_divider);
                starting_flag = get_n_bits(W ,znacznik_len);
                if (znacznik == starting_flag)
                    starting_flag_ok = true;
                else
                    starting_flag_ok = false;
            }
            else{
                starting_flag = get_n_bits(W ,znacznik_len);
                if (znacznik == starting_flag)
                    starting_flag_ok = true;
                else
                    starting_flag_ok = false;
            }
            
        }
        else
        {
            starting_flag = ending_flag;
            starting_flag_ok = true;
        }
        message = "";
    }

    Z.close();
    W.close();
    
    return 0;
}