#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"



Node* new_Node(int key)
{
    /*    (typ zminnej)malloc(rozmiar podnego typu)    */ 
    Node* new = (Node*)malloc(sizeof(Node));
    new->key = key;
    new->parent = NULL;
    new->left = NULL;
    new->right = NULL;
    
    return new;
}

void insert_Node(Node* root, int key)
{
    Node* z = new_Node(key);
    Node* x = root;
    Node* y = NULL;

    while(x != NULL){
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
    if (y == NULL)
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
    
}

Node* delete_Node(Node* root, int key)
{
    // base case
    if (root == NULL)
        return root;
 
    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (key < root->key)
        root->left = delete_Node(root->left, key);
 
    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (key > root->key)
        root->right = delete_Node(root->right, key);
 
    // if key is same as root's key,
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        Node* temp = tree_minimum(root->right);
 
        // Copy the inorder
        // successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = delete_Node(root->right, temp->key);
    }
    return root;
}

void delete_Node_old(Node* root, int key)
{
    Node* z = tree_search(root, key);
    Node* y = NULL;
    Node* x = NULL;

    if (z->left == NULL || z->right == NULL)
    {
        y = z;
    }
    else
    {
        y = tree_successor(z);
    }
    if (y->left != NULL)
    {
        x = y->left;
    }
    else
    {
        x = y->right;
    }
    if (x != NULL)
    {
        x->parent = y->parent;
    }
    if (y->parent == NULL)
    {
        root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
    if (y != z)
    {
        z->key = y->key;
        z->left = y->left;
        z->right = y->right;
        z->parent = y->parent;
    }
    printf("Deleting %d from tree \n", key);
    free(y);
}

Node* tree_minimum(Node* root){
    Node* x = root;
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}

Node* tree_maksimum(Node* root){
    Node* x = root;
    while(x->right != NULL){
        x = x->right;
    }
    return x;
}

Node* tree_successor(Node* node){
    
    if(node->right != NULL){
        return tree_minimum(node->right);
    }
    Node* y = node->parent;
    while (y != NULL && node == y->right)
    {
        node = y;
        y = y->parent;
    }

    return y;
}

Node* tree_search(Node* node, int key){

    if (node == NULL || key == node->key)
    {
        return node;
    }
    if (key < node->key)
    {
        return tree_search(node->left, key);
    }
    else
    {
        return tree_search(node->right, key);
    }
}

int tree_height(Node* root)
{
    if (root == NULL)
    {
       return -1;
    }
    else
    {
        /* compute the depth of each subtree */
        int lDepth = tree_height(root->left);
        int rDepth = tree_height(root->right);
 
        /* use the larger one */
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

void free_tree(Node* root)
{
    if (root == NULL)
    {
        return;
    } 
    free_tree(root->left);
    free_tree(root->right);

    printf("Deleting node: %d \n", root->key);
    free(root);
}

// global variables used in `print_BST`
static char* left_trace; // needs to be allocaded with size
static char* right_trace; // needs to be allocaded with size

void print_BST(Node * root, int depth,char prefix)
{
  if( root == NULL ) return;
  if( root->left != NULL ){
    print_BST(root->left, depth+1, '/');
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
  printf("[%d]\n", root->key);
  left_trace[depth]=' ';
  if( root->right != NULL ){
    right_trace[depth]='|';
    print_BST(root->right, depth+1, '\\');
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

void print_tree(Node* root)
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BST ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    print_BST(root, 0, '-');
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

int main(void)
{
    Node* root = NULL;          /* tworzymy korzeń naszego drzewa */

    int n;                      /* Liczba kluczy do wstawienia */
    scanf("%d", &n);
    fill_traces(n);             /* Uzupełniemy trace'y do printowania drzewa */                
    
    int key;
    scanf("%d", &key);          /* Pierwszy klucz traktujemy jako root */
    root = new_Node(key);
    print_tree(root);

    for (int i = 1; i < n; i++)
    {
        scanf("%d", &key);
        insert_Node(root, key);
        printf("Dodaje element %d\n", key);
        print_tree(root);
    }

    int height = tree_height(root);

    printf("Wysokosc drzewa = %d\n", height);
    
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &key);
        delete_Node(root, key);
        printf("Usuwam element %d\n", key);
        print_tree(root);
    }

    free_tree(root);
    free(left_trace);
    free(right_trace);

    return 0;
}
