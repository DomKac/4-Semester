#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "splay_tree.h"

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

Node* left_rotate(Node* node)
{
    Node* y = node->right;
    node->right = y->left;
    y->left = node;
    return y;
}

Node* right_rotate(Node *node)
{
    Node* y = node->left;
    node->left = y->right;
    y->right = node;
    return y;
}

// This function brings the key at root if key is present in tree.
// If key is not present, then it brings the last accessed item at
// root.  This function modifies the tree and returns the new root
Node* splay(Node *root, int key)
{
    // Base cases: root is NULL or key is present at root
    if (root == NULL || root->key == key)
        return root;
 
    // Key lies in left subtree
    if (root->key > key)
    {
        // Key is not in tree, we are done
        if (root->left == NULL) return root;
 
        // Zig-Zig (Left Left)
        if (root->left->key > key)
        {
            // First recursively bring the key as root of left-left
            root->left->left = splay(root->left->left, key);
 
            // Do first rotation for root, second rotation is done after else
            root = right_rotate(root);
        }
        else if (root->left->key < key) // Zig-Zag (Left Right)
        {
            // First recursively bring the key as root of left-right
            root->left->right = splay(root->left->right, key);
 
            // Do first rotation for root->left
            if (root->left->right != NULL)
                root->left = left_rotate(root->left);
        }
 
        // Do second rotation for root
        return (root->left == NULL)? root: right_rotate(root);
    }
    else // Key lies in right subtree
    {
        // Key is not in tree, we are done
        if (root->right == NULL) return root;
 
        // Zag-Zig (Right Left)
        if (root->right->key > key)
        {
            // Bring the key as root of right-left
            root->right->left = splay(root->right->left, key);
 
            // Do first rotation for root->right
            if (root->right->left != NULL)
                root->right = right_rotate(root->right);
        }
        else if (root->right->key < key)// Zag-Zag (Right Right)
        {
            // Bring the key as root of right-right and do first rotation
            root->right->right = splay(root->right->right, key);
            root = left_rotate(root);
        }
 
        // Do second rotation for root
        return (root->right == NULL)? root: left_rotate(root);
    }
}

Node* insert_Node(Node* root, int key)
{
    if (root == NULL)
        return new_Node(key);
    
    root = splay(root, key);
    
    if (key == root->key)
        return root;
    
    Node* new = new_Node(key);

    if (root->key > key)
    {
        new->right = root;
        new->left = root->left;
        root->left = NULL;
    }
    else
    {
        new->left = root;
        new->right = root->right;
        root->right = NULL;
    }
 
    return new;
}

Node* delete_Node_parent(Node* root, int key)
{

    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = delete_Node_parent(root->left, key);
 

    else if (key > root->key)
        root->right = delete_Node_parent(root->right, key);
 
    else {
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
 
        Node* temp = tree_minimum(root->right);
 
        root->key = temp->key;

        root->right = delete_Node_parent(root->right, temp->key);
    }
    return root;
}

Node* delete_Node(Node* root, int key)
{
    if (root == NULL)
        return NULL;

    root = splay(root, key);
    
    if (key != root->key)
        return root;
    
    Node* temp;
    if (root->left == NULL)
    {
        temp = root;
        root = root->right;
    }
    else
    {
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }
    free(temp);

    return root;    
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

Node* tree_search(Node* root, int key){

    return splay(root, key);
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
    fill_traces(n);             /* Uzupełniamy trace'y do printowania drzewa */                
    
    int key;
    scanf("%d", &key);          /* Pierwszy klucz traktujemy jako root */
    root = new_Node(key);
    print_tree(root);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &key);
        root = insert_Node(root, key);
        printf("Dodaje element %d\n", key);
        print_tree(root);
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &key);
        root = delete_Node(root, key);
        printf("Dodaje element %d\n", key);
        print_tree(root);
    }
    

    free_tree(root);
    free(left_trace);
    free(right_trace);

    return 0;
}
