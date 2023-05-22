#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

#define swap2(a, b) \
    (a = a^b),      \
    (b = a^b),      \
    (a = b^a)       
                  

static inline void swap(unsigned* a, unsigned* b);

static inline size_t parent(size_t i);
static inline size_t left(size_t i);
static inline size_t right(size_t i);

void max_heapify(unsigned A[], size_t i);
void build_max_heap(unsigned A[], size_t n);
void heapsort(unsigned A[], size_t n);

void max_heapify_pr(unsigned A[], size_t i, size_t heap_size);
unsigned heap_maximum(unsigned A[]);
unsigned heap_extract_max(unsigned A[], size_t heap_size);
void heap_increase_key(unsigned A[], size_t i, unsigned key);
void max_heap_insert(unsigned A[], unsigned key, size_t heap_size);

void wypisz_tablice(unsigned tab[], size_t n);
void print_BST(unsigned A[], int depth,char prefix, size_t current ,size_t n);
void fill_traces(size_t n);
void print_tree(unsigned A[], size_t n);

#endif
