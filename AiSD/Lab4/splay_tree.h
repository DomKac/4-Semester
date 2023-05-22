#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <stddef.h>

typedef struct Node
{
    int key;                /* wartość węzła        */
    char pad[4];            /* spadingowane bajty   */
    struct Node* left;      /* lewe poddrzewo       */
    struct Node* right;     /* prawe poddrzewo      */
    struct Node* parent;    /* rodzic węzła         */
   
} Node;

/* Prototypy funkcji */
Node* new_Node(int key);                
Node* tree_minimum(Node* root);         
Node* tree_maksimum(Node* root);        
Node* tree_successor(Node* node);       
void  free_tree(Node* root);
int   tree_height(Node* root);

/* splay */
Node* left_rotate(Node* node);
Node* right_rotate(Node* node);
Node* splay(Node* node, int key);

/* functions using splay */
Node* tree_search(Node* root, int key);
Node* insert_Node(Node* root, int key); 
Node* delete_Node(Node* root, int key);

void  print_tree(Node* root);
void  print_BST(Node* root, int depth, char prefix); /* Printowanie doktora Kika */
void  fill_traces(int n);

Node* delete_Node_parent(Node* root, int key);


#endif
