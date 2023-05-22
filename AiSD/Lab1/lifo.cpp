#include <iostream>
#include <list>
#include <chrono>
#include <random>

using namespace std;

struct element
{
    int value;
    element *next;
    element *previous;
    element();
};

element::element()
{
    next = nullptr;
    previous = nullptr;
};

struct lifo
{
    element *pierwszy_element; // wskaźnik na początek listy
    element *ostatni_element;  // wskaźnik na koniec listy
    int dlugosc;
    void dodajElement(int value);
    void usunElement();
    lifo();
};

void lifo::dodajElement(int value)
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
        nowy->previous = ostatni_element;
        ostatni_element = nowy;
    }
}

void lifo::usunElement()
{

    element *temp = ostatni_element;
    if (dlugosc > 0)
    {
        ostatni_element = ostatni_element->previous;
        if (!ostatni_element)
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

lifo::lifo()
{
    pierwszy_element = nullptr;
    ostatni_element = nullptr;
    dlugosc = 0;
}

int main()
{

    auto *l1 = new lifo;

    for (int i = 0; i < 100; i++)
    {
        l1->dodajElement(i);
        cout << l1->ostatni_element->value << ", ";
    }

    cout << endl
         << endl;

    for (int i = 0; i < 100; ++i)
    {
        cout << l1->ostatni_element->value << ", ";
        l1->usunElement();
    }

    return 0;
}
