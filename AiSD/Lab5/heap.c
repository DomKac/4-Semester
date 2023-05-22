#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "heap.h"

static size_t comp = 0;
static size_t shift = 0;
static size_t heap_size = 0;

static inline size_t parent(size_t i){
    return ((i-1) >> 1);
}

static inline size_t left(size_t i){
    return ((i << 1) | 1);
}

static inline size_t right(size_t i){
    return (((i+1) << 1));
}

static inline void swap(unsigned* a,unsigned* b){
    *a = *a^*b;
    *b = *a^*b;
    *a = *b^*a;
}

void max_heapify(unsigned A[], size_t i){
    size_t l = left(i);
    size_t r = right(i);
    size_t largest;
    
    comp++;
    if (l <= heap_size && A[l] > A[i]){
        largest = l;
    }
    else{
        largest = i;
    }
    comp++;
    if (r <= heap_size && A[r] > A[largest]){
        largest = r;
    }
    comp++; /* nie jestem pewien */
    if (largest != i){
        shift++;
        swap(&A[i], &A[largest]);
        max_heapify(A,largest);
    }
}

void build_max_heap(unsigned A[], size_t n){
    heap_size = n;
    for (size_t i = n/2; i < __SIZE_MAX__; --i){
        max_heapify(A, i); 
    }  
}

void heapsort(unsigned A[], size_t n){
    build_max_heap(A, n);
    for (size_t i = n; i >= 1; --i){
        shift++;
        swap(&A[0], &A[i]);
        --heap_size;
        max_heapify(A,0); 
    } 
}

void wypisz_tablice(unsigned tab[], size_t n)
{
    printf(" {");
    for (size_t i = 0; i < n - 1; ++i)
        printf("%u, ", tab[i]);
    
    printf("%u }\n", tab[n-1]);
}

int main(void){

    size_t n;
    scanf("%zu", &n);

    unsigned tab[n];

    unsigned key;
    for (size_t i = 0; i < n; i++)
    {
        scanf("%u", &key);
        tab[i] = key;
    }
    
    if (n < 50) {
        puts("Pierwotna tablica: ");
        wypisz_tablice(tab,n);
        heapsort(tab, n-1);
        puts("Tablica po heapsorcie: ");
        wypisz_tablice(tab,n);
    }
    else {
        heapsort(tab, n-1);
        printf("%zu\t%zu\t%zu\n",n,shift,comp);
    }

    return EXIT_SUCCESS;
}
