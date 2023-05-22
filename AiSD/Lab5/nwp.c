#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void lcs_lenght(const unsigned* X,  const unsigned* Y, size_t m, size_t n, unsigned** b, unsigned** c);
void print_lcs_help(const unsigned* X, size_t m, size_t n, unsigned** b, size_t i, size_t j);
void print_lcs(const unsigned* X, size_t m, size_t n, unsigned** b);
void print_array(unsigned* A, size_t n);

static size_t comp = 0;
static size_t shift = 0;

void lcs_lenght(const unsigned* X,  const unsigned* Y, size_t m, size_t n, unsigned** b, unsigned** c){

    for (size_t i = 1; i <= m; i++){
        c[i][0] = 0;
        shift++;  
    }
    for (size_t j = 0; j <= n; j++){
        c[0][j] = 0;
        shift++;  
    }
    for (size_t i = 1; i <= m; i++){
        for (size_t j = 1; j <= n; j++){
            if (X[i-1] == Y[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = 0; /* strzałka w lewo-góra */
                comp++; 
                shift+=2;  
            }
            else if (c[i-1][j] >= c[i][j-1]) {
                c[i][j] = c[i-1][j];
                b[i][j] = 1; /* stzałka w góre */
                comp+=2; 
                shift+=2;   
            }   
            else {
                c[i][j] = c[i][j-1];
                b[i][j] = 2; /* stzałka w lewo */ 
                comp+=2; 
                shift+=2;  
            }
        }
    }
}

void print_lcs_help(const unsigned* X, size_t m, size_t n, unsigned** b, size_t i, size_t j) {
    if (i == 0 || j == 0) {
        return;
    }
    if (b[i][j] == 0) {
        print_lcs_help(X, m, n, b, i-1, j-1);
        printf("%u ", X[i-1]);
    }
    else if (b[i][j] == 1)
        print_lcs_help(X, m, n, b, i-1, j);
    else
        print_lcs_help(X, m, n, b, i, j-1); 
}

void print_lcs(const unsigned* X, size_t m, size_t n, unsigned** b) {
    printf("{ ");
    print_lcs_help(X,m,n,b,m,n);
    printf("}\n");
}

void print_array(unsigned* A, size_t n) {
    printf("{ ");
    for (size_t i = 0; i < n; i++)
    {
       printf("%u, ", A[i]);
    }
    printf("}\n");
}

int main(void){

    unsigned key;

    size_t m;
    scanf("%zu", &m);
    unsigned* X = malloc(m*sizeof(unsigned));
    for (size_t i = 0; i < m; i++) {
        scanf("%u", &key);
        X[i] = key;
    }

    size_t n;
    scanf("%zu", &n);
    unsigned* Y = malloc(n*sizeof(unsigned));
    for (size_t i = 0; i < n; i++) {
        scanf("%u", &key);
        Y[i] = key;
    }

    unsigned** b = (unsigned**)malloc((m+1)*sizeof(unsigned*));
    unsigned** c = (unsigned**)malloc((m+1)*sizeof(unsigned*));
    for (size_t i = 0; i < m+1; i++) {
        b[i] = (unsigned*)malloc((n+1)*sizeof(unsigned));
        c[i] = (unsigned*)malloc((n+1)*sizeof(unsigned));
    }
    
    lcs_lenght(X,Y,m,n,b,c);
    unsigned odp = c[m][n];
    if (n<50 && m<50) {
        print_array(X,m);
        print_array(Y,n);
        printf("Dlugosc najdluzszego podciagu = %u\n", odp);
        printf("Najdluzszy podciag:\t");
        print_lcs(X,m,n,b);
    }
    else {
        printf("%zu\t%zu\t%zu\t%u\n", n, shift, comp, odp);
    }
    
    for (size_t i = 0; i < m+1; i++) {
        free(b[i]);
        free(c[i]);
    }
    free(b);
    free(c);
    free(X);
    free(Y);

    return EXIT_SUCCESS;
}
