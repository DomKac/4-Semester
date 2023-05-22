#include <iostream>
#include <list>
#include <chrono>
#include <random>

using namespace std;

struct element
{
    int value;
    element *next;
    element();
};

element::element()
{
    next = nullptr;
};

struct fifo
{
    element *pierwszy_element; // wskaźnik na początek listy
    element *ostatni_element;  // wskaźnik na koniec listy
    int dlugosc;
    void dodajElement(int value);
    void usunElement();
    fifo();
};

void fifo::dodajElement(int value)
{

    auto *nowy = new element; // tworzy nowy element listy
    nowy->value = value;      // wypełniamy dane elementu
    dlugosc++;

    if (pierwszy_element == nullptr)
    { // sprawdzamy czy to pierwszy element listy
        pierwszy_element = ostatni_element = nowy;
    }
    else // w przeciwnym wypadku wędrujemy na koniec listy
    {
        ostatni_element->next = nowy; // ostatni element wskazuje na nasz nowy
        ostatni_element = nowy;
    }
}

void fifo::usunElement()
{

    element *temp = pierwszy_element;
    if (dlugosc > 0)
    {
        pierwszy_element = pierwszy_element->next;
        if (!pierwszy_element)
        {
            pierwszy_element = nullptr;
        }
        delete temp;
    }
    else
    {
        cout << "Brak elementow w kolejce!" << endl;
    }
    dlugosc--;
}

fifo::fifo()
{
    pierwszy_element = nullptr;
    ostatni_element = nullptr;
    dlugosc = 0;
}

int main()
{

    auto *l1 = new fifo;

    for (int i = 0; i < 100; i++)
    {
        l1->dodajElement(i);
        cout << l1->ostatni_element->value << ", ";
    }

    cout << endl
         << endl;

    for (int i = 0; i < 100; ++i)
    {
        cout << l1->pierwszy_element->value << ", ";
        l1->usunElement();
    }

    cout << endl;

    return 0;
}