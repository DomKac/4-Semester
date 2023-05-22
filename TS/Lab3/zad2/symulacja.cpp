#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>


using namespace std;

string kabel[20] = {" "};
size_t dl_kabla = 20;
size_t A_time=0;


void print_kabel(){

    
    for (size_t i = 0; i < dl_kabla; i++)
    {
        cout << "-----";       
    }
    cout << endl;
    cout << "|";
    for (size_t i = 0; i < dl_kabla; i++)
    {
        cout << kabel[i] << "    |";       
    }
    cout << endl;
    for (size_t i = 0; i < dl_kabla; i++)
    {
        cout << "-----";       
    }
    cout << endl;    
}

void clear_kabel(){
    for (size_t i = 0; i < dl_kabla; i++)
        kabel[i] = " ";
}


void send_signal(char ruter_name, int position, int prob_to_send_mes){
    srand(time(NULL));
    int signal_lenght = 3;
    int pom = 0;

    for (size_t i = position+A_time; i < dl_kabla && i >=0 && pom < signal_lenght; i++)
    {
        kabel[i] = ruter_name;
        pom++;
    }
    pom = 0;
    for (size_t i = position-A_time; i < dl_kabla && i >=0 && pom < signal_lenght; i--)
    {
        kabel[i] = ruter_name;
        pom++;
    }
    // for (size_t i = position; i >= 0 && position-i < A_time; i--)
    // {
    //     if(i+signal_lenght <= dl_kabla)
    //         kabel[i+signal_lenght] = " ";
    //     kabel[i] = ruter_name;
    // }
    

}

void clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    cout << "\x1B[2J\x1B[H";
}


int main(void){

    print_kabel();

    for (size_t i = 0; i < 100; i++)
    {
        clear();
        send_signal('A',0,100);
        send_signal('B',19,100);
        A_time++; 
        print_kabel();
        clear_kabel();
        usleep(1000000);
    }
    

    return 0;
}