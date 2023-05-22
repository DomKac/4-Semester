#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <tgmath.h>
#include "heap.h"

static size_t comp = 0;
static size_t shift = 0;

static inline size_t parent(size_t i){
    return ((i-1) >> 1);
}

static inline size_t left(size_t i){
    return ((i << 1) | 1); /* problem dla i = 0 */ 
}

static inline size_t right(size_t i){
    return (((i+1) << 1));
}

void max_heapify_pr(unsigned A[], size_t i, size_t heap_size){
    size_t l = left(i);
    size_t r = right(i);
    size_t largest;
    comp++;
    if (l < heap_size && A[l] > A[i]){
        largest = l;
    } 
    else{
        largest = i;
    }
    comp++;
    if (r < heap_size && A[r] > A[largest]){
        largest = r;
    }
    comp++;
    if (largest != i){
        /* swap(&A[i], &A[largest]); */ 
        shift++;
        swap2(A[i], A[largest]);
        max_heapify_pr(A,largest, heap_size);
    }
}

inline unsigned heap_maximum(unsigned A[]){
    return A[0];
}

unsigned heap_extract_max(unsigned A[], size_t heap_size){
    if (heap_size == 0){
        fprintf(stderr, "%s", "Kopiec pusty!\n");
        return 0; 
    }
    unsigned max = A[0];
    shift++;
    A[0] = A[heap_size-1];
    max_heapify_pr(A, 0, heap_size-1);
    return max;
}

void heap_increase_key(unsigned A[], size_t i, unsigned key){
    comp++;
    if (key < A[i]){
        fprintf(stderr, "%s", "nowy klucz jest mniejszy niz klucz aktualny!\n");
        return;
    }
    A[i] = key;
    comp++;
    while (i > 0 && A[parent(i)] < A[i]){
        /* swap(&A[i], &A[parent(i)]); */
        shift++;
        swap2(A[i], A[parent(i)]);
        i = parent(i);
    }
}

void max_heap_insert(unsigned A[], unsigned key, size_t heap_size){
    A[heap_size] = 0;
    heap_increase_key(A,heap_size, key); 
}


void wypisz_tablice(unsigned tab[], size_t n){
    
    if (n < 1)
        return;
    
    printf(" {");
    for (size_t i = 0; i < n - 1; ++i)
        printf("%u, ", tab[i]);
    
    printf("%u }\n", tab[n-1]);
}

// global variables used in `print_BST`
static char* left_trace; // needs to be allocaded with size
static char* right_trace; // needs to be allocaded with size

void print_BST(unsigned A[], int depth,char prefix, size_t current ,size_t n)
{
  if( current >= n ) return;
  if( left(current) < n ){
    print_BST(A, depth+1, '/', left(current), n);
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
  printf("[%u]\n", A[current]);
  left_trace[depth]=' ';
  if( right(current) < n ){
    right_trace[depth]='|';
    print_BST(A, depth+1, '\\', right(current), n);
  }
}
void fill_traces(size_t n)
{
    left_trace  = (char*)malloc((sizeof(char)*(unsigned long)n) + 1);
    right_trace = (char*)malloc((sizeof(char)*(unsigned long)n) + 1);
    for(size_t i=0; i<=n; i++)
    {
        left_trace[i]=' ';
        right_trace[i]=' ';
    }
}

void print_tree(unsigned A[], size_t n)
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ HEAP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    print_BST(A, 0, '-', 0, n);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

int main(void){

    size_t n;
    scanf("%zu", &n);

    unsigned tab[n];
    unsigned help;
    unsigned key;
    
    if (n < 50) {
        
        fill_traces(n);  
        for (size_t i = 0; i < n; i++) {
            scanf("%u", &key);
            tab[i] = key;
            max_heap_insert(tab, key, i);
            printf("Wstawiam %u\n", key);
            print_tree(tab, i+1);
        }
        for (size_t i = n-1; i < __SIZE_MAX__; --i) {
            help = heap_extract_max(tab,i+1);
            printf("Usunalem  %u\n", help);
            print_tree(tab, i);
        }
        free(left_trace);
        free(right_trace);
    }
    else {
        for (size_t i = 0; i < n; i++)
        {
            scanf("%u", &key);
            tab[i] = key;
            max_heap_insert(tab, key, i);
        }
        for (size_t i = n-1; i < __SIZE_MAX__; --i)
        {
            help = heap_extract_max(tab,i+1);
        }
        printf("%zu\t%zu\t%zu\n",n,shift,comp);
    }

    return EXIT_SUCCESS;
}
