#include <iostream>
#include <list>
#include <chrono>
#include <random>

using namespace std;

struct element
{
    int value;
    element *previous;
    element *next;
    element();
};

element::element()
{
    previous = nullptr;
    next = nullptr;
};

struct lista
{
    element *pierwszy_element; // wskaźnik na początek listy
    int dlugosc;               // ilosc elementów w liście
    void dodajElement(int value);
    void usunElement(int numer); // usuwamy element po numerze w liście
    void wyswietl_liste();
    element zwrocElement(int numer);
    lista();
};

void lista::dodajElement(int value)
{

    auto *nowy = new element; // tworzy nowy element listy
    nowy->value = value;      // wypełniamy dane elementu
    dlugosc++;                // zwiekszamy rozmiar listy

    if (pierwszy_element == nullptr)
    { // sprawdzamy czy to pierwszy element listy

        pierwszy_element = nowy; // jeżeli tak to nowy element jest teraz początkiem listy
        pierwszy_element->previous = pierwszy_element;
        pierwszy_element->next = pierwszy_element;
    }
    else // w przeciwnym wypadku wędrujemy na koniec listy
    {
        element *temp = pierwszy_element;

        while (temp->next != pierwszy_element)
        {
            temp = temp->next; // znajdujemy wskaźnik na ostatni element
        }

        temp->next = nowy;             // ostatni element wskazuje na nasz nowy
        nowy->previous = temp;         // poprzednik nowego jest obecnym
        nowy->next = pierwszy_element; // nastepnik nowego jest pierwszym
        pierwszy_element->previous = nowy;
    }
}

void lista::usunElement(int numer)
{

    element *temp = pierwszy_element;

    if (numer == 0)
    {
        pierwszy_element->previous->next = pierwszy_element->next;
        pierwszy_element->next->previous = pierwszy_element->previous;
        pierwszy_element = pierwszy_element->next;
    }
    else if (numer >= 1 && numer < dlugosc - 1)
    {
        for (int i = 0; i < numer; ++i)
        {
            temp = temp->next;
        }
        temp->previous->next = temp->next;
    }
    else if (numer == dlugosc - 1)
    {
        temp = pierwszy_element->previous;
        pierwszy_element->previous = temp->previous;
        temp->previous->next = pierwszy_element;
    }
    delete (temp);
    dlugosc--;
}

void lista::wyswietl_liste()
{

    element *temp = pierwszy_element; // wskaznik na pierszy element listy

    if (pierwszy_element != nullptr)
    {
        cout << "{ ";
        // przewijamy wskazniki na nastepne elementy
        do
        {
            cout << temp->value << ", ";
            temp = temp->next;
        } while (temp != pierwszy_element);

        cout << "}" << endl;
    }
}

lista::lista()
{
    pierwszy_element = nullptr;
    dlugosc = 0;
}

element lista::zwrocElement(int numer)
{

    element *temp = pierwszy_element;

    if ((dlugosc - numer) > (dlugosc / 2))
    {
        for (int i = 0; i < numer; ++i)
        {
            temp = temp->next;
        }
    }
    else
    {
        for (int i = 0; i < dlugosc - numer; ++i)
        {
            temp = temp->previous;
        }
    }

    return *temp;
}

lista merge(lista *l1, lista *l2)
{

    auto *nowaLista = new lista;
    element *temp = l1->pierwszy_element;

    do
    {
        nowaLista->dodajElement(temp->value);
        temp = temp->next;

    } while (temp != l1->pierwszy_element);

    temp = l2->pierwszy_element;

    do
    {
        nowaLista->dodajElement(temp->value);
        temp = temp->next;
    } while (temp != l2->pierwszy_element);

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
    cout << endl;
    cout << "Polaczone listy:  " << endl;
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
