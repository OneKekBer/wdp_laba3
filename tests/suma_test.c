#include "../zbior_ary.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

void print_item(item i) {
    if (i.b == 0) printf("{%d}", i.a);
    else printf("[%d,%d]", i.a, i.b);
}

void print_zbior(zbior_ary z) {
    printf("{");
    for (int i = 0; i < z.n; ++i) {
        print_item(z.sets[i]);
        if (i < z.n - 1) printf(", ");
    }
    printf("}\n");
}

void free_zbior(zbior_ary z) {
    free(z.sets);
}

int main() {
    zbior_ary A, B, C, D, E, F;
    
    printf("Test 1:\n");
    A = ciag_arytmetyczny(1, 1, 6);
    B = ciag_arytmetyczny(3, 1, 16);
    C = suma(A, B);
    print_zbior(C);
    free_zbior(A); free_zbior(B); free_zbior(C);

    printf("Test 2:\n");
    A = ciag_arytmetyczny(1, 1, 10);
    B = ciag_arytmetyczny(5, 1, 15);
    C = suma(A, B);
    print_zbior(C);
    free_zbior(A); free_zbior(B); free_zbior(C);

   printf("Test 3:\n");
    A = ciag_arytmetyczny(1, 1, 3);
    B = singleton(5);
    C = suma(A, B);
    print_zbior(C);
    free_zbior(A); free_zbior(B); free_zbior(C);

    printf("Test 4:\n");
    A = ciag_arytmetyczny(1, 1, 14);
    B = ciag_arytmetyczny(5, 1, 15);
    C = suma(A, B);
    print_zbior(C);
    free_zbior(A); free_zbior(B); free_zbior(C);
    
    printf("Test 5:\n");
    A = ciag_arytmetyczny(1, 1, 5);
    B = ciag_arytmetyczny(6, 1, 10);
    C = suma(A, B);
    print_zbior(C);
    free_zbior(A); free_zbior(B); free_zbior(C);

    printf("Test 6:\n");
    A = ciag_arytmetyczny(1, 1, 3);
    B = singleton(5);
    C = suma(A, B);
    print_zbior(C);
    D = ciag_arytmetyczny(1, 1, 6);
    E = suma(C, D);
    print_zbior(E);
    free_zbior(A); free_zbior(B); free_zbior(C); free_zbior(D); free_zbior(E);

    printf("Test 7:\n");
    A = ciag_arytmetyczny(5, 1, 25);
    B = ciag_arytmetyczny(1, 1, 5);
    C = suma(A, B);
    print_zbior(C);
    free_zbior(A); free_zbior(B); free_zbior(C);

    printf("Test 8:\n");
    A = singleton(5);
    B = singleton(5);
    C = suma(A, B);
    print_zbior(C);
    free_zbior(A); free_zbior(B); free_zbior(C);

    printf("Test 9:\n");
    A = singleton(5);
    B = singleton(6);
    C = suma(A, B);
    print_zbior(C);
    free_zbior(A); free_zbior(B); free_zbior(C);

    printf("Test 10:\n");
    A = singleton(5);
    B = singleton(6);
    C = suma(A, B);
    //print_zbior(C);
    D = ciag_arytmetyczny(200, 1, 300);
    E = ciag_arytmetyczny(1, 1, 3);
    F = suma(suma(D, E), C);
    
    print_zbior(F);
        free_zbior(A); free_zbior(B); free_zbior(C); free_zbior(D); free_zbior(E); free_zbior(F);
    return 0;
}
