#include <iostream>
#include <fstream>

using namespace std;

// Funkcja generująca crc dla rozepchniętej wiadomości 
string generate_crc_pushed(const string encoded_mes, const size_t frame_size, const string crc_divider){

    string x = encoded_mes;

    int crc_lenght = crc_divider.length();
    x.append(crc_lenght-1, '0');

    for (size_t i = 0; i < frame_size - 1; i++)
    {
        if (x[i] == '1')
        {
            for (size_t j = 0; j < crc_lenght; j++)
            {
                if (x[i+j] == crc_divider[j])
                    x[i+j] = '0';
                else
                    x[i+j] = '1';            
            }
        }
    }

    return x.substr(frame_size);
}
// Funkjca kodująca frame_size - bitową ramkę (znacznik|message|crc|znacznik)
string encode_message(const char message[], const size_t frame_size, const string znacznik, const string crc_divider){
    
    if(frame_size == 0)
        return "";
    // 01111110|01111110111111100|crc|01111110
    // string crc = generate_crc(message, frame_size, crc_divider);
    int counter_1 = 0;
    size_t size = frame_size;
    string encoded_mes = ""; 

    for (size_t i = 0; i < frame_size; i++)
    {
        encoded_mes = encoded_mes + message[i];
        
        if (message[i] == '0')
            counter_1 = 0;
        else
            counter_1++;

        if (counter_1 == 5){
            encoded_mes = encoded_mes + "0";
            size++;
        }  
    }
    string crc = generate_crc_pushed(encoded_mes, size, crc_divider); 
    
    return znacznik + encoded_mes + crc + znacznik;
}

void print_message(char message[], size_t frame_size){
    
    for (size_t i = 0; i < frame_size; i++)
        cout << message[i];
    cout << endl;
}


int main(void){

    ifstream myfile;
    myfile.open("Z.txt", fstream::in);
    ofstream W;
    W.open("W.txt");
    
    size_t frame_size;
    cout << "Podaj wielkosc ramki: ";
    cin >> frame_size; 

    string znacznik = "01111110";
    char message[frame_size];
    string coded_message = "";
    int actual_size = 0;
    size_t i = 0;
    string ready_frame;
    while(!myfile.eof()){
        
        for (i = 0; i < frame_size; i++)
        {  
            myfile >> noskipws >> message[i];
            if (myfile.eof())
                break;
        }
        cout << i << endl;
        ready_frame = encode_message(message,i,znacznik,"1011");
        cout << "ready_frame: " << ready_frame << endl;
        W << ready_frame;
        print_message(message, i);
    }
    myfile.close();
    W.close();

    return 0;
}