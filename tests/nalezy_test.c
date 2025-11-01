#include "../zbior_ary.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))



void free_zbior(zbior_ary z) {
    free(z.sets);
}

int main() {
    zbior_ary A, B, C, D, E, F;
    
    
    A = ciag_arytmetyczny(1, 1, 6);
    B = ciag_arytmetyczny(3, 1, 16);
    C = suma(A, B);
    free_zbior(A); free_zbior(B); free_zbior(C);

    
    A = ciag_arytmetyczny(1, 1, 10);
    B = ciag_arytmetyczny(5, 1, 15);
    C = suma(A, B);
    free_zbior(A); free_zbior(B); free_zbior(C);

   
    A = ciag_arytmetyczny(1, 1, 3);
    B = singleton(5);
    C = suma(A, B);
    free_zbior(A); free_zbior(B); free_zbior(C);

    
    A = ciag_arytmetyczny(1, 1, 14);
    B = ciag_arytmetyczny(5, 1, 15);
    C = suma(A, B);
    free_zbior(A); free_zbior(B); free_zbior(C);
    
    
    A = ciag_arytmetyczny(1, 1, 5);
    B = ciag_arytmetyczny(6, 1, 10);
    C = suma(A, B);
    free_zbior(A); free_zbior(B); free_zbior(C);

    
    A = ciag_arytmetyczny(1, 1, 3);
    B = singleton(5);
    C = suma(A, B);
    D = ciag_arytmetyczny(1, 1, 6);
    E = suma(C, D);
    free_zbior(A); free_zbior(B); free_zbior(C); free_zbior(D); free_zbior(E);

    
    A = ciag_arytmetyczny(5, 1, 25);
    B = ciag_arytmetyczny(1, 1, 5);
    C = suma(A, B);
   assert(nalezy(C, 26) == false);

    free_zbior(A); free_zbior(B); free_zbior(C);

    
    A = singleton(5);
    B = singleton(5);
    C = suma(A, B);
   assert(nalezy(C, 5) == true);

    free_zbior(A); free_zbior(B); free_zbior(C);

    
    A = singleton(5);
    B = singleton(6);
    C = suma(A, B);
   assert(nalezy(C, 6) == true);

    free_zbior(A); free_zbior(B); free_zbior(C);

    
    A = singleton(5);
    B = singleton(6);
    C = suma(A, B);
    D = ciag_arytmetyczny(200, 1, 300);
    E = ciag_arytmetyczny(1, 1, 3);
    F = suma(suma(D, E), C);
    
   assert(nalezy(F, 5) == true);
   printf("GIT");
   free_zbior(A); free_zbior(B); free_zbior(C); free_zbior(D); free_zbior(E); free_zbior(F);
    return 0;
}
