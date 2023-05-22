#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

// zmienne globalne
string symbolcode = ""; // zawiera w sobie kod sumbolu w formie stringa (np. "1001")
int current_bit = 0;    // przydaje sie przy wpisywaniu bajtow do pliku (możemy wysłać wyłącznie paczki 8 bitów)
unsigned char bit_buffer;
int diff_symbols = 0;

struct Node
{
    Node *next;
    Node *left;
    Node *right;
    int symbol;
    int count;
};

// Tworzy drzewo Huffmana z wcześniej wygenerowanej listy
void MakeTree(Node *&root)
{
    Node *p, *r, *v1, *v2;

    while (true)
    {
        v1 = root; // pobiermay z listy 2 pierwsze węzły
        v2 = v1->next;

        if (!v2)
            break;

        root = v2->next; // jako tymczasowego roota ustawiamy następnika v2

        p = new Node;                     // tworzymy nowy węzeł p który będzie rootem dla v1 i v2
        p->left = v1;                     // v1 będzie lewym liściem p
        p->right = v2;                    // v2 będzie prawym liściem p
        p->count = v1->count + v2->count; // sumujemy liczby wystąpień które są przechowywane w v1 i v2 i zapisujemy
                                          // jako liczbę wystąpien w węźle p

        // Węzeł wstawiamy z powrotem na listę tak, aby była uporządkowana

        if (!root || (p->count <= root->count))
        {
            p->next = root;
            root = p;
            continue;
        }

        r = root;

        while (r->next && (p->count > r->next->count))
        {
            r = r->next;
        }
        p->next = r->next;
        r->next = p;
    }
}

// function to convert decimal to binary
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
// Usuwanie drzewa
void DeleteTree(Node *v)
{
    if (v)
    {
        DeleteTree(v->left);
        DeleteTree(v->right);
        delete v;
    }
}
// Zakodowanie znaku
bool CodeSym(int c, Node *p, string b)
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

Node *Merge(Node *h1, Node *h2)
{
    auto *t1 = new Node;
    auto *t2 = new Node;
    auto *temp = new Node;

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

void MergeSort(Node *&head)
{
    auto *first = new Node;
    auto *second = new Node;
    auto *temp = new Node;
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

void printBT(const std::string &prefix, const Node *node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // print the value of the node
        std::cout << node->symbol << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void printBT(const Node *node)
{
    printBT("", node, false);
}

void uposledzony_slownik(Node *node, FILE *myfile)
{
    int len = diff_symbols - 1;
    fwrite(&len, 1, 1, myfile);
    while (node)
    {
        fwrite(&(node->symbol), 1, 1, myfile);
        fwrite(&(node->count), 2, 1, myfile); // zwiększamy maksymalnego counta
        node = node->next;
    }
}

int binToDec(string bin) // "01110011"
{

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

int main(int argc, char **argv)
{
    FILE *f = freopen(argv[1], "rb", stdin);
    int sym;

    Node *root;
    Node *p;
    root = nullptr; // tworzymy liste
    while ((sym = getchar()) != EOF)
    {
        p = root; // Szukamy na liście symbolu 'sym'
        while (p && (p->symbol != sym))
        {
            p = p->next;
        }
        if (p == nullptr)
        {
            p = new Node;
            p->next = root;
            p->left = nullptr;
            p->right = nullptr;
            p->symbol = sym;
            p->count = 1;
            root = p;
            diff_symbols++;
        }
        else
        {
            p->count++;
        }
    }
    fclose(f);
    MergeSort(root);

    Node *node = root;
    while (node)
    {
        cout << "sym = " << node->symbol << " wystapienia " << node->count << endl;
        node = node->next;
    }

    FILE *myfile;
    myfile = fopen("/home/dominik/Studia/KKD/Lab2/skompresowany_plik.bin", "wb");

    uposledzony_slownik(root, myfile); // wysłanie słownika
    MakeTree(root);
    printBT(root);

    FILE *f2 = freopen(argv[1], "rb", stdin);

    string text = "";
    string x = "";
    int liczba;
    if (myfile)
    {
        cout << endl;
        while ((sym = getchar()) != EOF)
        {
            CodeSym(sym, root, "");
            text = text + symbolcode;
            while (text.length() >= 8)
            {
                x = text.substr(0, 8);
                liczba = binToDec(x);
                fwrite(&liczba, 1, 1, myfile);
                text = text.substr(8);
            }
        }
        int ile_dopisac_0 = 8 - text.length();
        for (int i = 0; i < ile_dopisac_0; i++)
        {
            text = text + "0";
        }
        x = text.substr(0, 8);
        liczba = binToDec(x);
        fwrite(&liczba, 1, 1, myfile);
        text = text.substr(8);
        cout << text << endl;
    }

    fclose(f2);
    fclose(myfile);
    DeleteTree(root);

    return 0;
}