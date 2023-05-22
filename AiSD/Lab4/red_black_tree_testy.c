#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "red_black_tree.h"

static Node* T_nil = NULL;      /* wartownik */
static Node* root = NULL;

static double comparisions = 0;
static double read_pointers = 0;

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
    read_pointers+=3;
    if (y->left != T_nil)
    {
        y->left->parent = x;
        read_pointers++;
    }
    y->parent = x->parent;  /* Ojcem y uczyń ojca x */
    read_pointers++;
    if (x->parent == T_nil)
    {
        root = y;
        read_pointers+=2;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
        read_pointers+=3;
    }
    else if (x == x->parent->right) // git
    {
        x->parent->right = y;
        read_pointers+=4;
    }
    read_pointers=+2;
    y->left = x;            /* Przyłącz x jako lewego syna y */
    x->parent = y;
}

void right_rotate(Node* x){

    Node* y;
    y = x->left;     /* Inicjuj y */ 
    x->left = y->right;     /* Zamien prawe poddrzewo y na lewe poddrzewo x */
    read_pointers+=3;
    if (y->right != T_nil)
    {
        y->right->parent = x;
        read_pointers++;
    }
    y->parent = x->parent;  /* Ojcem y uczyń ojca x */ 
    if (x->parent == T_nil)
    {
        root = y;
        read_pointers+=2;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
        read_pointers+=3;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
        read_pointers+=4;
    }
    read_pointers=+2;
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
    read_pointers+=3;
    while (x != T_nil)
    {
        y = x;
        comparisions++;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
        read_pointers+=2;
    }
    read_pointers++;
    z->parent = y;
    if (y == T_nil)
    {
        root = z;
        read_pointers+=2;
    }
    else if (z->key < y->key)
    {
        y->left = z;
        read_pointers++;
        comparisions++;
    }
    else
    {
        y->right = z;
        comparisions++;
    }
    read_pointers+=2;
    z->left = T_nil;
    z->right = T_nil;
    z->color = 'R';
    
    insert_fixup(z);
} 

void insert_fixup(Node* z)
{ 
    read_pointers++;
    Node* y = NULL;
    while (z->parent->color == 'R') // ok
    {
        read_pointers++;
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            read_pointers++;
            if (y->color == 'R')
            {
                z->parent->color = 'B';                 /* Przypadek 1 */ 
                y->color = 'B';                         /* Przypadek 1 */ 
                z->parent->parent->color = 'R';         /* Przypadek 1 */ 
                z = z->parent->parent;                  /* Przypadek 1 */ 
                read_pointers++;
            } // ok
            else 
            {
                read_pointers++;
                if (z == z->parent->right)
                {
                    read_pointers++;
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
            read_pointers++;
            if (y->color == 'R')
            {
                z->parent->color = 'B';                 /* Przypadek 4 */ 
                y->color = 'B';                         /* Przypadek 4 */ 
                z->parent->parent->color = 'R';         /* Przypadek 4 */ 
                z = z->parent->parent;                  /* Przypadek 4 */
                read_pointers++; 
            }
            else 
            {
                read_pointers++;
                if (z == z->parent->left)
                {
                    read_pointers++;
                    z = z->parent;                      /* Przypadek 5 */ 
                    right_rotate(z);              /* Przypadek 5 */
                }
                z->parent->color = 'B';                 /* Przypadek 6 */
                z->parent->parent->color = 'R';         /* Przypadek 6 */
                left_rotate(z->parent->parent);   /* Przypadek 6 */
            }
        }
        read_pointers++;
    }
    root->color = 'B'; 
}

void transplant(Node* u, Node* v)
{
    read_pointers++;
    if (u->parent == T_nil)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
        read_pointers++;
    }
    else
    {
        u->parent->right = v;
        read_pointers++;
    }
    v->parent = u->parent;
    read_pointers++;
}

Node* tree_search(Node* node, int key){
    comparisions++;
    read_pointers++;
    if (node == T_nil || key == node->key)
        return node;

    comparisions++;
    if (key < node->key)
        return tree_search(node->left, key);
    else
        return tree_search(node->right, key);
}

Node* tree_minimum(Node* node){
    Node* x = node;
    
    while(x->left != T_nil){
        x = x->left;
        read_pointers++;
    } 
    return x;
}

void  delete_Node(int key)
{
    read_pointers+=2;
    Node* z = tree_search(root, key);
    if (z == T_nil)
        return;
    
    Node* y = z;
    Node* x = NULL;
    char y_original_color = y->color;
    read_pointers+=3;
    if (z->left == T_nil)
    {
        x = z->right;
        read_pointers++;
        transplant(z, z->right);
    }
    else if(z->right == T_nil)
    {
        x = z->left;
        read_pointers+=2;
        transplant(z, z->left);
    }
    else
    {
        y = tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        read_pointers+=4;
        if (y->parent == z)
        {
            read_pointers++;
            x->parent = y;
        }
        else
        {
            transplant(y, y->right);
            read_pointers+=2;
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        read_pointers+=2;
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
    read_pointers++;
    while (x != root && x->color == 'B')
    {
        read_pointers++;
        if (x == x->parent->left)
        {
            read_pointers++;
            w = x->parent->right;
            if (w->color == 'R')
            {
                w->color = 'B';
                x->parent->color = 'R';
                left_rotate(x->parent);
                w = x->parent->right;
                read_pointers++;
            }
            if (w->left->color == 'B' && w->right->color == 'B')
            {
                w->color = 'R';
                x = x->parent;
                read_pointers++;
            }
            else
            {
                read_pointers++;
                if (w->right->color == 'B')
                {
                    w->left->color = 'B';
                    w->color = 'R';
                    right_rotate(w);
                    w = x->parent->right;
                    read_pointers++;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->right->color = 'B';
                left_rotate(x->parent);
                x = root;
                read_pointers++;
            }
        }
        else
        {
            read_pointers++;
            w = x->parent->left;
            if (w->color == 'R')
            {
                w->color = 'B';
                x->parent->color = 'R';
                right_rotate(x->parent);
                w = x->parent->left;
                read_pointers++;
            }
            if (w->left->color == 'B' && w->right->color == 'B')
            {
                w->color = 'R';
                x = x->parent;
                read_pointers++;
            }
            else
            {
                if (w->left->color == 'B')
                {
                    w->right->color = 'B';
                    w->color = 'R';
                    left_rotate(w);
                    w = x->parent->left;
                    read_pointers++;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->left->color = 'B';
                right_rotate(x->parent);
                x = root;
                read_pointers++;
            }
        }
        read_pointers++;
    }
    x->color = 'B';
}

int tree_height(Node* node)
{
    if (node == T_nil)
    {
       return -1;
    }
    else
    {
        /* compute the depth of each subtree */
        int lDepth = tree_height(node->left);
        int rDepth = tree_height(node->right);
 
        /* use the larger one */ 
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

void free_tree(Node* node)
{ 
    if (node == T_nil)
    { 
        return;
    } 
    free_tree(node->left);
    free_tree(node->right);

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
    
    int n, k;
    double height = 0;
    double sum_c = 0;
    double maks_c = 0;
    double sum_r = 0;
    double maks_r = 0;
    double sum_h = 0;
    double maks_h = 0;

    scanf("%d", &n);
    fill_traces(n);             /* Uzupełniemy trace'y do printowania drzewa */ 

    for(int i = 0; i < n; i++){
      scanf("%d", &k);
      insert_Node(k);

     if(i < 2049 ){
          height = tree_height(root);
      }
      else if(i%50 == 0){
          height = tree_height(root);
      }

      if(comparisions >= maks_c) maks_c = comparisions;
      if(read_pointers >= maks_r) maks_r = read_pointers;
      //if(curr_height >= maks_height) maks_height = curr_height;
      sum_c+= comparisions;
      sum_r+= read_pointers;
      sum_h+= height;


      //printf("%d, %d, %d, %d \n", n, comparisions, read_pointers, height );
      //curr_height = 0;
      comparisions = 0;
      read_pointers = 0;
    }

    maks_h = height;

    for(int i = 0; i < n; i++){
        scanf("%d", &k);
        delete_Node(k);
        if(i < 2049 )
        {
            height = tree_height(root);
        }
        else if(i%50 == 0)
        {
          height = tree_height(root);
        }

        if(comparisions >= maks_c) maks_c = comparisions;
        if(read_pointers >= maks_r) maks_r = read_pointers;
        sum_c+= comparisions;
        sum_r+= read_pointers;
        sum_h+= height;

        comparisions = 0;
        read_pointers = 0;
    }

    double height_avg = sum_h/(2*n);
    double comp_avg = sum_c/(2*n);
    double reads_avg = sum_r/(2*n);

    //printf("size_n,  comp_avg,  comp_maks, reads_avg, reads_maks, h_avg,   h_final   h_maks \n");
    printf("%d, %f, %f, %f, %f, %f, %f, %f \n", n, comp_avg, maks_c, reads_avg, maks_r, height_avg, height, maks_h);


    free_tree(root);
    free(T_nil);
    free(left_trace);
    free(right_trace);
    return 0;
}
