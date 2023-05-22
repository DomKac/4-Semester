#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Tworzymy strukturę liścia, który będzie podstawowym budulcem drzewa kodowania.
// Definiujemy w niej wskaźniki na lewe dziecko i prawe dziecko,
// jej wartość(ilość wystąpień/ich sumę), znak do kodowania, a także zakodowany znak.
struct Node
{
    Node *left;
    Node *right;
    char character;
    int value;
    Node(char c, int v, Node *l = nullptr, Node *r = nullptr)
    { // tworzymy konstruktor struktury
        left = l;
        right = r;
        character = c;
        value = v;
    }
    ~Node()
    {                 // pamiętajmy, że zawsze powinno się wyczyścić wszelkie zmienne
        delete right; // dlatego zwalniamy pamięc zajętą przez dwójkę dzieci
        delete left;  // z racji, iż jest to destruktor, funkcja ta wywoła się również u usuniętych dzieci
    }
    bool isLeaf()
    {
        return character != '\0'; // tworzymy funkcję pomocniczą, która wskażę, czy jest to liść zawierający jakiś znak
    }
};

// Tworzymy strukturę, która pomoże nam przy tworzeniu drzewa kodowania.
// Będzie ona porównywać dwa liście z drzewa/
struct comparator
{
    bool operator()(Node *a, Node *b)
    {
        if (a->value != b->value)        // jeżeli liście są różnej wartości
            return a->value > b->value;  // wykonaj zwykłe porównanie
        if (!a->isLeaf() && b->isLeaf()) // jeżeli są równe i drugi jest kontenerem, to zawsze będzie on uznawany jako większy
            return false;
        if (!b->isLeaf() && a->isLeaf()) // jeżeli są równe i drugi jest kontenerem, to zawsze będzie on uznawany jako większy
            return true;
        if (a->isLeaf() && b->isLeaf())         // jeżeli oba są liściami
            return a->character > b->character; // to decyduje kolejność alfabetyczna
        return true;                            // jeżeli żaden z powyższych warunków nie zostanie spełniony, zwracamy true
    }
};

// Definiujemy metodę, która stworzy drzewo kodowania Huffmana, a następnie zwróci jego korzeń
// Argumentem jest tekst, który chcemy zakodować
Node *createHuffmanTree(string line)
{
    map<char, int> counter; // korzystamy z obiektu map, aby zliczyć wystąpienia dla każdego znaku
    for (char c : line)
    {
        if (counter.find(c) == counter.end())
        {                   // jeżeli znaku nie ma w mapie
            counter[c] = 1; // dodajemy go
        }
        else
        {
            counter[c]++; // jeżeli jest, zwiększamy jego ilość wystąpień
        }
    }

    // Tworzymy obiekt priority_queue, który będzie przechowywać nieprzypisane elementy drzewa.
    // Obiekt priority_queue pozwoli nam stworzyć uporządkowaną listę liści drzewa - najmniejsze będą najwyżej.
    // Do porównywania elementów wykorzystujemy wcześniej zdefiniowaną strukturę comparator.
    priority_queue<Node *, vector<Node *>, comparator> nodes;

    for (auto entry : counter)
    {
        nodes.push(new Node(entry.first, entry.second)); // tworzymy liście drzewa, bazując na znakach i ich ilości wystąpień
    }
    Node *root; // definiujemy zmienną, która docelowo będzie korzeniem naszego drzewa
    while (nodes.size() > 1)
    {                           // następnie iterujemy, dopóki w nodes nie zostanie ostatni element - korzeń drzewa
        Node *n1 = nodes.top(); // pobieramy pierwszy, najmniejszy element z priority queue
        nodes.pop();            // a następnie go usuwamy
        Node *n2 = nodes.top(); // ponawiamy powyższe kroki, aby uzyskać drugi, najmniejszy element
        nodes.pop();
        if (n1->value == n2->value && !n1->isLeaf())
        {                   // jeżeli oba liście mają tą samą wartość, a jeden z nich jest kontenerem, to powinien on być traktowany jako większy element
            Node *pom = n1; // dlatego w takiej sytuacji podmieniamy wskaźniki
            n1 = n2;
            n2 = pom;
        }
        root = new Node('\0', n1->value + n2->value, n1, n2); // tworzymy liść-kontener, który będzie przechowywać dwa powyższe elementy i sumę ich wartości
        nodes.push(root);                                     // a następnie dodajemy go do priority queue
    }
    return root; // gdy w priority queue zostanie tylko jeden wyraz, to oznacza, że drzewo zostało zbudowane, a wyraz ten jest jego korzeniem; zwracamy go
}

// Tworzymy rekurencyjną funkcję, która zakoduje elementy zależnie od ich pozycji w drzewie.
// Jako argumenty podajemy korzeń drzewa, tekst pomocniczy przy rekurencji, a także mapę kodowania
void encodeNodes(Node *node, string val, map<char, string> *map)
{
    if (node == nullptr)
    {           // warunek STOP funkcji rekurencyjnej:
        return; // jeżeli trafimy na koniec drzewa, przerywamy działanie
    }
    if (node->isLeaf())
    {                                                   // jeżeli jest to liść przechowujący znak
        cout << node->character << " : " + val << endl; // to drukujemy go i jego zakodowaną wartość
        map->insert({node->character, val});            // a następnie dodajemy obie wartości do mapy
    }
    encodeNodes(node->left, val + '0', map);  // wywołujemy jeszcze raz funkcję dla lewej strony drzewa - rekurencja
    encodeNodes(node->right, val + '1', map); // wywołujemy jeszcze raz funkcję dla prawej strony drzewa - rekurencja
}

// Tworzymy funkcję, która odkoduje zakodowany tekst bazując na zbudowanym drzewie.
string decode(Node *root, string encoded)
{
    string decoded = "";      // zmienna pomocnicza
    Node *currentNode = root; // wskaźnik na aktualnie sprawdzany liść
    for (char c : encoded)
    { // iterujemy poprzez zakodowany tekst
        if (c == '0')
        { // jeżeli iterowany znak jest zerem, to oznacza, że musimy iść w lewo
            if (currentNode->left->isLeaf())
            {                                            // jeżeli dziecko po lewo jest liściem przechowującym znak
                decoded += currentNode->left->character; // dodajemy ten znak do zmiennej pomocniczej
                currentNode = root;                      // a następnie wracamy na początek drzewa
            }
            else
            {
                currentNode = currentNode->left; // jeżeli trafiliśmy na kontener, ustawiamy na niego wskaźnik
            }
        }
        else
        { // jeżeli jest to inny znak (1), to przechodzimy na prawą stronę
            if (currentNode->right->isLeaf())
            {                                             // jeżeli dziecko po prawo jest liściem przechowującym znak
                decoded += currentNode->right->character; // dodajemy ten znak do zmiennej pomocniczej
                currentNode = root;                       // a następnie wracamy na początek drzewa
            }
            else
            {
                currentNode = currentNode->right; // jeżeli trafiliśmy na kontener, ustawiamy na niego wskaźnik
            }
        }
    }
    return decoded; // na koniec zwracamy odkodowany tekst
}

int main()
{
    // pobieramy najpierw tekst od użytkownika
    cout << "Kodowanie Huffmana. Podaj tekst, który chcesz zakodować:" << endl;
    string line;
    getline(cin, line);

    // tworzymy drzewo bazując na tekście
    Node *root = createHuffmanTree(line);

    // kodujemy wartości w drzewie, drukujemy je i dodajemy do nowej mapy, która powiąże znaki z ich zakodowanymi wartościami
    cout << "Oto tablica kodowania Huffmana:" << endl;
    map<char, string> encodedValues;
    encodeNodes(root, "", &encodedValues);

    // kodujemy tekst, bazując na utworzonej mapie kodowania
    string encodedLine = "";
    for (char c : line)
    {
        encodedLine += encodedValues[c];
    }
    cout << "Oto twoj tekst po zakodowaniu: " << encodedLine << endl;

    // odkodowujemy tekst, aby sprawdzić działanie
    cout << "Oto tekst po odkodowaniu: " << decode(root, encodedLine) << endl;

    // sprzątamy po sobie :)
    delete root;
    return 0;
}