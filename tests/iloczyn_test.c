#include "../zbior_ary.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

// ======================== PRINT HELPERS ==========================
void print_item(FILE *out, item i) {
    if (i.b == 0) fprintf(out, "{%d}", i.a);
    else fprintf(out, "[%d,%d]", i.a, i.b);
}

void zbior_to_string(zbior_ary z, char *buffer) {
    buffer[0] = '\0';
    strcat(buffer, "{");
    for (int i = 0; i < z.n; ++i) {
        char tmp[64];
        if (z.sets[i].b == 0)
            sprintf(tmp, "{%d}", z.sets[i].a);
        else
            sprintf(tmp, "[%d,%d]", z.sets[i].a, z.sets[i].b);

        strcat(buffer, tmp);
        if (i < z.n - 1) strcat(buffer, ", ");
    }
    strcat(buffer, "}");
}

void print_zbior(zbior_ary z) {
    printf("{");
    for (int i = 0; i < z.n; ++i) {
        if (z.sets[i].b == 0) printf("{%d}", z.sets[i].a);
        else printf("[%d,%d]", z.sets[i].a, z.sets[i].b);
        if (i < z.n - 1) printf(", ");
    }
    printf("}\n");
}

void free_zbior(zbior_ary z) {
    free(z.sets);
}

// ======================== TEST FRAMEWORK ==========================

void check_result(const char *test_name, zbior_ary result, const char *expected) {
    char buf[512];
    zbior_to_string(result, buf);
    if (strcmp(buf, expected) == 0) {
        printf("%s: ✅ OK\n", test_name);
    } else {
        printf("%s: ❌ FAIL\n", test_name);
        printf("  Expected: %s\n", expected);
        printf("  Got:      %s\n", buf);
    }
}

// =========================== TESTS ================================

int main() {
    zbior_ary A, B, C, D;

    // Test 1
    A = ciag_arytmetyczny(1, 1, 6);     // [1,6]
    B = ciag_arytmetyczny(3, 1, 16);    // [3,16]
    C = iloczyn(A, B);                  // [3,6]
    check_result("Test 1 — iloczyn", C, "{{3}, {4}, {5}, {6}}");
    free_zbior(A); free_zbior(B); free_zbior(C);

    // Test 2
    A = ciag_arytmetyczny(2, 1, 8);     // [2,8]
    D = ciag_arytmetyczny(14, 1, 18);   // [14,18]
    B = ciag_arytmetyczny(6, 1, 16);    // [6,16]
    C = iloczyn(suma(A, D), B);         // [6,8] + [14,16]
    check_result("Test 2 — suma+iloczyn", C, "{{6}, {7}, {8}, {14}, {15}, {16}}");
    free_zbior(A); free_zbior(B); free_zbior(C); free_zbior(D);

    // Test 3 — brak przecięcia
    A = ciag_arytmetyczny(1, 1, 3);
    B = ciag_arytmetyczny(10, 1, 15);
    C = iloczyn(A, B);
    check_result("Test 3 — brak przecięcia", C, "{}");
    free_zbior(A); free_zbior(B); free_zbior(C);

    // Test 4 — różna długość (A krótszy)
    A = ciag_arytmetyczny(1, 1, 3);   // 1..3
    B = ciag_arytmetyczny(2, 1, 10);  // 2..10
    C = suma(A, B);                   // 1..10
    check_result("Test 4 — A krótszy", C, "{{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}}");
    free_zbior(A); free_zbior(B); free_zbior(C);

    // Test 5 — B krótszy
    A = ciag_arytmetyczny(1, 1, 10);
    B = ciag_arytmetyczny(5, 1, 7);
    C = suma(A, B);
    check_result("Test 5 — B krótszy", C, "{{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}}");
    free_zbior(A); free_zbior(B); free_zbior(C);

    // Test 6 — singleton + ciąg
    A = singleton(5);
    B = ciag_arytmetyczny(1, 1, 10);
    C = suma(A, B);
    check_result("Test 6 — singleton + ciąg", C, "{{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}}");
    free_zbior(A); free_zbior(B); free_zbior(C);

    // Test 7 — koniec jednego zbioru wcześniej
    A = ciag_arytmetyczny(1, 1, 4);
    B = ciag_arytmetyczny(3, 1, 10);
    C = suma(A, B);
    check_result("Test 7 — resztki", C, "{{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}}");
    free_zbior(A); free_zbior(B); free_zbior(C);

    // Test 8 — pełne nakładanie
    A = ciag_arytmetyczny(1, 1, 10);
    B = ciag_arytmetyczny(1, 1, 10);
    C = iloczyn(A, B);
    check_result("Test 8 — pełne nakładanie", C, "{{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}}");
    free_zbior(A); free_zbior(B); free_zbior(C);

    // Test 9 — puste przecięcie z singletonem
    A = singleton(100);
    B = ciag_arytmetyczny(1, 1, 10);
    C = iloczyn(A, B);
    check_result("Test 9 — singleton bez przecięcia", C, "{}");
    free_zbior(A); free_zbior(B); free_zbior(C);

    // Test 10 — nakładanie na końcach
    A = ciag_arytmetyczny(1, 1, 5);
    B = ciag_arytmetyczny(5, 1, 10);
    C = suma(A, B);
    check_result("Test 10 — nakładanie końców", C, "{{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}}");
    free_zbior(A); free_zbior(B); free_zbior(C);

    printf("\n=== Wszystkie testy zakończone ===\n");
    return 0;
}
