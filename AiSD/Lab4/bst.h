#ifndef BST_H
#define BST_H

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
Node* tree_search(Node* root, int key);
Node* delete_Node(Node* root, int key); 
void  insert_Node(Node* root, int key); 
void  free_tree(Node* root);
int   tree_height(Node* root);

void  print_tree(Node* root);
void  print_BST(Node* root, int depth, char prefix); /* Printowanie doktora Kika */
void  fill_traces(int n);

void  delete_Node_old(Node* root, int key); /* z pseudokodu dr Kika */

#endif
