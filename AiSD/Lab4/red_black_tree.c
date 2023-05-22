#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "red_black_tree.h"

static Node* T_nil = NULL;      /* wartownik */
static Node* root = NULL;

Node* new_Node(int key)
{
    /*    (typ zminnej)malloc(rozmiar podnego typu)    */ 
    Node* new = (Node*)malloc(sizeof(Node));
    new->key = key;
    new->color = 'B';
    new->parent = T_nil;
    new->left = T_nil;
    new->right = T_nil;
 
    return new;
}

void left_rotate(Node* x)
{
 
    Node* y = x->right;     /* Inicjuj y */ 
    x->right = y->left;     /* Zamien lewe poddrzewo y na prawe poddrzewo x */
    if (y->left != T_nil)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;  /* Ojcem y uczyń ojca x */ 
    if (x->parent == T_nil)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else if (x == x->parent->right) // git
    {
        x->parent->right = y;
    }
    y->left = x;            /* Przyłącz x jako lewego syna y */
    x->parent = y;
}

void right_rotate(Node* x){

    Node* y;
    y = x->left;     /* Inicjuj y */ 
    x->left = y->right;     /* Zamien prawe poddrzewo y na lewe poddrzewo x */
    if (y->right != T_nil)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;  /* Ojcem y uczyń ojca x */ 
    if (x->parent == T_nil)
    {
        root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    y->right = x;            /* Przyłącz x jako prawgo syna y */
    x->parent = y;
}

void insert_Node(int key){
 
    if (root == NULL)
    {   
        root = new_Node(key);
        return;
    }
    
    Node* z = new_Node(key);
    Node* y = T_nil;
    Node* x = root;
    while (x != T_nil)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == T_nil)
    {
        root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    z->left = T_nil;
    z->right = T_nil;
    z->color = 'R';
    
    insert_fixup(z);
} 

void insert_fixup(Node* z)
{ 
    Node* y = NULL;
    while (z->parent->color == 'R') // ok
    {
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if (y->color == 'R')
            {
                z->parent->color = 'B';                 /* Przypadek 1 */ 
                y->color = 'B';                         /* Przypadek 1 */ 
                z->parent->parent->color = 'R';         /* Przypadek 1 */ 
                z = z->parent->parent;                  /* Przypadek 1 */ 
            } // ok
            else 
            {
                if (z == z->parent->right)
                {
                    z = z->parent;                      /* Przypadek 2 */ 
                    left_rotate(z);                /* Przypadek 2 */
                }
                z->parent->color = 'B';                 /* Przypadek 3 */
                z->parent->parent->color = 'R';         /* Przypadek 3 */
                right_rotate(z->parent->parent);  /* Przypadek 3 */
            }
        } //ok
        else if (z->parent == z->parent->parent->right)
        {
            y = z->parent->parent->left;
            if (y->color == 'R')
            {
                z->parent->color = 'B';                 /* Przypadek 4 */ 
                y->color = 'B';                         /* Przypadek 4 */ 
                z->parent->parent->color = 'R';         /* Przypadek 4 */ 
                z = z->parent->parent;                  /* Przypadek 4 */ 
            }
            else 
            {
                if (z == z->parent->left)
                {
                    z = z->parent;                      /* Przypadek 5 */ 
                    right_rotate(z);              /* Przypadek 5 */
                }
                z->parent->color = 'B';                 /* Przypadek 6 */
                z->parent->parent->color = 'R';         /* Przypadek 6 */
                left_rotate(z->parent->parent);   /* Przypadek 6 */
            }
        }
        
    }
    root->color = 'B'; 
}

void transplant(Node* u, Node* v)
{
    if (u->parent == T_nil)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

Node* tree_search(Node* node, int key){

    if (node == T_nil || key == node->key)
        return node;  
    if (key < node->key)
        return tree_search(node->left, key);
    else
        return tree_search(node->right, key);
}

Node* tree_minimum(Node* node){
    Node* x = node; 
    while(x->left != T_nil){
        x = x->left;
    } 
    return x;
}

void  delete_Node(int key)
{
    Node* z = tree_search(root, key);
    if (z == T_nil)
        return;
    
    Node* y = z;
    Node* x = NULL;
    char y_original_color = y->color;
    if (z->left == T_nil)
    {
        x = z->right;
        transplant(z, z->right);
    }
    else if(z->right == T_nil)
    {
        x = z->left;
        transplant(z, z->left);
    }
    else
    {
        y = tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == 'B')
    {
        delete_fixup(x);
    }
    free(z);
}

void  delete_fixup(Node* x)
{
    Node* w = NULL;

    while (x != root && x->color == 'B')
    {
        if (x == x->parent->left)
        {
            w = x->parent->right;
            if (w->color == 'R')
            {
                w->color = 'B';
                x->parent->color = 'R';
                left_rotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 'B' && w->right->color == 'B')
            {
                w->color = 'R';
                x = x->parent;
            }
            else
            {
                if (w->right->color == 'B')
                {
                    w->left->color = 'B';
                    w->color = 'R';
                    right_rotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->right->color = 'B';
                left_rotate(x->parent);
                x = root;
            }
        }
        else
        {
            w = x->parent->left;
            if (w->color == 'R')
            {
                w->color = 'B';
                x->parent->color = 'R';
                right_rotate(x->parent);
                w = x->parent->left;
            }
            if (w->left->color == 'B' && w->right->color == 'B')
            {
                w->color = 'R';
                x = x->parent;
            }
            else
            {
                if (w->left->color == 'B')
                {
                    w->right->color = 'B';
                    w->color = 'R';
                    left_rotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->left->color = 'B';
                right_rotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 'B';
}

void free_tree(Node* node)
{ 
    if (node == T_nil)
    { 
        return;
    } 
    free_tree(node->left);
    free_tree(node->right);

    printf("Deleting node: %d \n", node->key);
    free(node);
}

// global variables used in `print_BST`
static char* left_trace; // needs to be allocaded with size
static char* right_trace; // needs to be allocaded with size

void print_BST(Node * node, int depth,char prefix)
{
  if( node == T_nil ) return;
  if( node->left != T_nil ){
    print_BST(node->left, depth+1, '/');
  }
  if(prefix == '/') left_trace[depth-1]='|';
  if(prefix == '\\') right_trace[depth-1]=' ';
  if( depth==0) printf("-");
  if( depth>0) printf(" ");
  for(int i=0; i<depth-1; i++)
    if( left_trace[i]== '|' || right_trace[i]=='|' ) 
    {
      printf("| ");
    } else 
    {
      printf("  ");
    }
  if( depth>0 ) printf("%c-", prefix);
  printf("[%d|%c]\n", node->key, node->color);
  left_trace[depth]=' ';
  if( node->right != T_nil ){
    right_trace[depth]='|';
    print_BST(node->right, depth+1, '\\');
  }
}
void fill_traces(int n)
{
    left_trace  = (char*)malloc((sizeof(char)*(unsigned long)n) + 1);
    right_trace = (char*)malloc((sizeof(char)*(unsigned long)n) + 1);
    for(int i=0; i<=n; i++)
    {
        left_trace[i]=' ';
        right_trace[i]=' ';
    }
}

void print_tree(void)
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BST ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    print_BST(root, 0, '-');
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}


int main(void)
{
    T_nil = (Node*)malloc(sizeof(Node));
    T_nil->color = 'B';

    int n;                      /* Liczba kluczy do wstawienia */
    scanf("%d", &n);
    fill_traces(n);             /* Uzupełniemy trace'y do printowania drzewa */                
    
    int key;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &key);
        printf("Dodaje klucz %d\n", key);
        insert_Node(key);
        print_tree();
    }

    printf("Ususwam 5!\n");
    delete_Node(5);
    print_tree();

       printf("Ususwam 19!\n");
    delete_Node(19);
    print_tree();

       printf("Ususwam 12!\n");
    delete_Node(12);
    print_tree();

    printf("Ususwam 8!\n");
    delete_Node(8);
    print_tree();

    printf("Ususwam 8!\n");
    delete_Node(8);
    print_tree();

    free_tree(root);
    free(T_nil);
    free(left_trace);
    free(right_trace);
    return 0;
}
