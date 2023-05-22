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

struct lista
{
    element *pierwszy_element; // wskaźnik na początek listy
    void dodajElement(int value);
    void usunElement(int numer); // usuwamy element po numerze w liście
    void wyswietl_liste();
    int zwrocElement(int numer);
    lista();
};

void lista::dodajElement(int value)
{

    auto *nowy = new element; // tworzy nowy element listy
    nowy->value = value;      // wypełniamy dane elementu

    if (pierwszy_element == nullptr)
    { // sprawdzamy czy to pierwszy element listy

        pierwszy_element = nowy; // jeżeli tak to nowy element jest teraz początkiem listy
    }
    else // w przeciwnym wypadku wędrujemy na koniec listy
    {
        element *temp = pierwszy_element;

        while (temp->next)
        {
            temp = temp->next;
        }

        temp->next = nowy;    // ostatni element wskazuje na nasz nowy
        nowy->next = nullptr; // ostatni nie wskazuje na nic
    }
}

void lista::usunElement(int numer)
{

    // jeżeli to pierwszy element listy
    if (numer == 0)
    {
        element *temp = pierwszy_element;
        pierwszy_element = temp->next;
        delete (temp);
    }
    else if (numer >= 1)
    {

        int i = 0;

        element *temp = pierwszy_element;

        while (temp)
        {

            if (numer == i + 1)
            {
                break;
            }

            temp = temp->next;
            i++;
        }

        if (temp->next->next == nullptr)
        {
            delete temp->next;
            temp->next = nullptr;
        }
        else
        {
            element *usuwana = temp->next;
            temp->next = temp->next->next;
            delete usuwana;
        }
    }
}

void lista::wyswietl_liste()
{

    element *temp = pierwszy_element; // wskaznik na pierszy element listy

    cout << "{ ";

    // przewijamy wskazniki na nastepne elementy
    while (temp)
    {
        cout << temp->value << ", ";
        temp = temp->next;
    }

    cout << "}" << endl;
}

lista::lista()
{
    pierwszy_element = nullptr;
}

int lista::zwrocElement(int numer)
{

    element *temp = pierwszy_element;

    for (int i = 0; i < numer; ++i)
    {
        temp = temp->next;
    }

    return temp->value;
}

lista merge(lista *l1, lista *l2)
{

    auto *nowaLista = new lista;

    element *temp = l1->pierwszy_element;

    while (temp)
    {
        nowaLista->dodajElement(temp->value);
        temp = temp->next;
    }

    temp = l2->pierwszy_element;

    while (temp)
    {
        nowaLista->dodajElement(temp->value);
        temp = temp->next;
    }

    return *nowaLista;
}

int main()
{

    auto *l1 = new lista;
    auto *l2 = new lista;

    for (int i = 0; i < 10; i++)
    {
        l1->dodajElement(rand() % 100);
        l2->dodajElement(rand() % 100);
    }

    l1->wyswietl_liste();
    l2->wyswietl_liste();

    auto *l3 = new lista;
    *l3 = merge(l1, l2);

    l3->wyswietl_liste();

    // ---------------------- czasy ------------------------------
    auto *list = new lista;

    for (int i = 0; i < 1000; i++)
    {
        list->dodajElement(rand() % 1000);
    }

    double sredni_czas = 0;
    auto start = chrono::high_resolution_clock::now();
    auto stop = chrono::high_resolution_clock::now();
    auto czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    // test dla elementu o numerze 420
    for (int i = 0; i < 100; i++)
    {
        start = chrono::high_resolution_clock::now();
        list->zwrocElement(420);
        stop = chrono::high_resolution_clock::now();
        czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        sredni_czas = sredni_czas + czas.count();
    }

    cout << sredni_czas / 100 << endl;
    sredni_czas = 0;

    // test dla elementu o numerze 999
    for (int i = 0; i < 100; i++)
    {
        start = chrono::high_resolution_clock::now();
        list->zwrocElement(999);
        stop = chrono::high_resolution_clock::now();
        czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        sredni_czas = sredni_czas + czas.count();
    }

    cout << sredni_czas / 100 << endl;
    sredni_czas = 0;

    // test dla elementu o losowym numerze
    int random = rand() % 1000;

    for (int i = 0; i < 100; i++)
    {
        start = chrono::high_resolution_clock::now();
        list->zwrocElement(random);
        stop = chrono::high_resolution_clock::now();
        czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        sredni_czas = sredni_czas + czas.count();
    }

    cout << sredni_czas / 100 << endl;
    sredni_czas = 0;

    return 0;
}
