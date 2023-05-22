#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>

using namespace std;

// zmienne globalne
string symbolcode = ""; // zawiera w sobie kod sumbolu w formie stringa (np. "1001")
int current_bit = 0;    // przydaje sie przy wpisywaniu bajtow do pliku (możemy wysłać wyłącznie paczki 8 bitów)
unsigned char bit_buffer;

struct HTNode
{
    HTNode *next;
    HTNode *left;
    HTNode *right;
    int symbol;
    int count;
};

// Tworzy drzewo Huffmana z wcześniej wygenerowanej listy
void MakeTree(HTNode *&root)
{
    HTNode *p, *r, *v1, *v2;

    while (true)
    {
        v1 = root; // Pobieramy z listy dwa pierwsze węzły
        v2 = v1->next;

        if (!v2)
            break; // Jeśli tylko jeden element, zakończ

        root = v2->next; // Lista bez v1 i v2

        p = new HTNode; // Tworzymy nowy węzeł
        p->left = v1;   // Dołączamy do niego v1 i v2
        p->right = v2;  // i wyliczamy nową częstość
        p->count = v1->count + v2->count;

        // Węzeł wstawiamy z powrotem na listę tak, aby była uporządkowana

        if (!root || (p->count <= root->count))
        {
            p->next = root;
            root = p;
            continue;
        }

        r = root;

        while (r->next && (p->count > r->next->count))
            r = r->next;

        p->next = r->next;
        r->next = p;
    }
}

// Usuwanie drzewa
void DeleteTree(HTNode *v)
{
    if (v)
    {
        DeleteTree(v->left);  // usuwamy lewe poddrzewo
        DeleteTree(v->right); // usuwamy prawe poddrzewo
        delete v;             // usuwamy sam węzeł
    }
}

// Zakodowanie znaku
bool CodeSym(int c, HTNode *p, string b)
{
    if (!p->left)
    {
        if (c != p->symbol)
        {
            return false;
        }
        else
        {
            symbolcode = b;
            // cout << symbolcode;
            return true;
        }
    }
    else
    {
        return CodeSym(c, p->left, b + "0") || CodeSym(c, p->right, b + "1");
    }
}

void WriteBit(char b, FILE *myfile)
{
    int bit = int(b) - '0';
    if (bit)
        bit_buffer |= (1 << current_bit);

    current_bit++;
    if (current_bit == 8)
    {
        fwrite(&bit_buffer, 1, 1, myfile);
        current_bit = 0;
        bit_buffer = 0;
    }
}

void Flush_Bits(FILE *myfile)
{
    while (current_bit)
        WriteBit(0, myfile);
}

HTNode *Merge(HTNode *h1, HTNode *h2)
{
    auto *t1 = new HTNode;
    auto *t2 = new HTNode;
    auto *temp = new HTNode;

    // Return if the first list is empty.
    if (h1 == nullptr)
        return h2;

    // Return if the Second list is empty.
    if (h2 == nullptr)
        return h1;

    t1 = h1;

    // A loop to traverse the second list, to merge the nodes to h1 in sorted way.
    while (h2 != nullptr)
    {
        // Taking head node of second list as t2.
        t2 = h2;

        // Shifting second list head to the next.
        h2 = h2->next;
        t2->next = nullptr;

        // If the data value is lesser than the head of first list add that node at the beginning.
        if (h1->count > t2->count)
        {
            t2->next = h1;
            h1 = t2;
            t1 = h1;
            continue;
        }

    // Traverse the first list.
    flag:
        if (t1->next == nullptr)
        {
            t1->next = t2;
            t1 = t1->next;
        }
        // Traverse first list until t2->data more than node's data.
        else if ((t1->next)->count <= t2->count)
        {
            t1 = t1->next;
            goto flag;
        }
        else
        {
            // Insert the node as t2->data is lesser than the next node.
            temp = t1->next;
            t1->next = t2;
            t2->next = temp;
        }
    }

    // Return the head of new sorted list.
    return h1;
}

void MergeSort(HTNode *&head)
{
    auto *first = new HTNode;
    auto *second = new HTNode;
    auto *temp = new HTNode;
    first = head;
    temp = head;

    // Return if list have less than two nodes.
    if (first == nullptr || first->next == nullptr)
    {
        return;
    }
    else
    {
        // Break the list into two half as first and second as head of list.
        while (first->next != nullptr)
        {
            first = first->next;
            if (first->next != nullptr)
            {
                temp = temp->next;
                first = first->next;
            }
        }
        second = temp->next;
        temp->next = nullptr;
        first = head;
    }

    // Implementing divide and conquer approach.
    MergeSort(first);
    MergeSort(second);

    // Merge the two part of the list into a sorted one.
    head = Merge(first, second);
}

int main(int argc, char **argv)
{
    FILE *f = freopen(argv[1], "rb", stdin);
    int sym;

    HTNode *root;
    HTNode *p;
    root = nullptr; // Tworzymy pustą listę
    while ((sym = getchar()) != EOF)
    {
        p = root; // Szukamy na liście symbolu 'sym'
        while (p && (p->symbol != sym))
        {
            p = p->next;
        }
        if (p == nullptr) // Jeśli go nie ma, to
        {
            p = new HTNode;    // tworzymy dla niego nowy węzeł
            p->next = root;    // Węzeł trafi na początek listy
            p->left = nullptr; // Ustawiamy pola węzła
            p->right = nullptr;
            p->symbol = sym;
            p->count = 1;
            root = p; // Wstawiamy węzeł na początek listy
        }
        else
        {
            p->count++; // Zwiększamy licznik wystąpień znaku
        }
    }
    fclose(f);

    MergeSort(root);
    HTNode *node = root;
    while (node)
    {
        cout << "Symbol: " << node->symbol << " wystepuje razy: " << node->count << endl;
        node = node->next;
    }
    MakeTree(root);

    FILE *myfile;
    myfile = fopen("/home/dominik/Studia/KKD/skompresowany_plik.bin", "wb");
    FILE *f2 = freopen(argv[1], "rb", stdin);
    if (myfile)
    {
        while ((sym = getchar()) != EOF)
        {
            CodeSym(sym, root, "");
            for (int b = 0; b < symbolcode.length(); b++)
            {
                // int bit = int(symbolcode[b]) - '0';
                WriteBit(symbolcode[0], myfile);
            }
        }
    }
    fclose(f2);
    Flush_Bits(myfile);
    fclose(myfile);
    DeleteTree(root);
    cout << endl
         << endl;

    return 0;
}