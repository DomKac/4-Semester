#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stddef.h>

typedef struct Node
{
    int key;                /* wartość węzła        */
    char color;             /* kolor węzła (R/B)    */
    char pad[3];            /* spadingowane bajty   */
    struct Node* left;      /* lewe poddrzewo       */
    struct Node* right;     /* prawe poddrzewo      */
    struct Node* parent;    /* rodzic węzła         */
   
} Node; // |k|k|k|k|c|p|p|p|

/* Prototypy funkcji */
Node* new_Node(int key);                
Node* tree_minimum(Node* node);         
Node* tree_maksimum(Node* node);        
Node* tree_successor(Node* node);       
Node* tree_search(Node* node, int key);
void  free_tree(Node* node);
void  left_rotate(Node* node);
void  right_rotate(Node* node);
void  delete_Node(int key);
void  delete_fixup(Node* node);
void  transplant(Node* u, Node* v);
void  insert_Node(int key); 
void  insert_fixup(Node* node);
int   tree_height(Node* node);

void  print_tree(void);
void  print_BST(Node* root, int depth, char prefix); /* Printowanie doktora Kika */
void  fill_traces(int n);

#endif
