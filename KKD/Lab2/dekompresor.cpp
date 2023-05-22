#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>

using namespace std;

// zmienne globalne
long long symbol_counter = 0;

struct Node
{
    Node *left;
    Node *right;
    Node *next;
    int symbol;
    int count;
};

Node *root;
Node *w = new Node;

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

void dekoder(string text, ofstream &out)
{
    char literka;
    for (size_t i = 0; i < text.length() && symbol_counter < root->count; i++)
    {
        if (text[i] == '1') // prawda kiedy bit = 1
        {
            if (w->right)
            {

                w = w->right;
                if (!w->right)
                {
                    literka = (char)(w->symbol);
                    out << literka;
                    symbol_counter++;
                    // printf("%c", w->symbol);
                    w = root;
                }
            }
        }
        else if (text[i] == '0')
        {
            if (w->left)
            {
                // printf("0");
                w = w->left;
                if (!w->left)
                {

                    literka = (char)(w->symbol);
                    out << literka;
                    symbol_counter++;
                    // printf("%c", w->symbol);
                    w = root;
                }
            }
        }
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
    // a_c#de.f,gh

    // pierwsze odczytywanie pilku będzie odopowiadało za sczytanie słownika
    // symbole w pilku będą ułożone w kolejności rosnącej zatem wpisujemy je do listy po kolei

    int diff_symbols;
    diff_symbols = getchar();
    cout << "Livzba symboli w slowniku: " << diff_symbols << endl;

    // pobieramy słownik ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Node *p = new Node;
    root = p;
    int b;
    for (int i = 0; i <= diff_symbols; i++)
    {
        p->symbol = getchar();

        b = getchar();
        b |= getchar() << 8;
        p->count = b; // binToDec(wystapienia);

        cout << "sym = " << p->symbol << " wystapienia " << p->count << endl;
        // Node *newp = new Node;
        if (i != diff_symbols)
        {
            p->next = new Node;
            p = p->next;
        }
    }
    //`~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    MakeTree(root);
    printBT(root);
    cout << endl;
    int sym;
    string text = "";
    w = root;
    ofstream out("output.txt");
    while ((sym = getchar()) != EOF)
    {
        text = decToBinary(sym);
        dekoder(text, out);
    }

    cout << "Ilosc symboli:  " << root->count << endl;

    out.close();
    fclose(f);
    DeleteTree(root);

    return 0;
}
