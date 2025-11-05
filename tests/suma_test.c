#include "../zbior_ary.h"
#include "../../tests/print.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

void print_item(item i) {
    printf("[%d,%d]", i.a, i.b);
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
    if(z.sets == NULL) return;
    if(z.n == 0)return;
    free(z.sets);
}

void f1(){
    zbior_ary z0, z1, z2, z3, z4, z5, z6, z7, z8;

    // 1. Команда: 0 -18 5 12
    z0 = ciag_arytmetyczny(-18, 5, 12);
    // print_zbior(z0); // Ожидаемый вывод: -18 -13 -8 -3 2 7 12 

    // 2. Команда: 3 0 0
    z1 = iloczyn(z0, z0);
    // print_zbior(z1); // Ожидаемый вывод: -18 -13 -8 -3 2 7 12 

    // 3. Команда: 4 1 0
    z2 = roznica(z1, z0);
    // print_zbior(z2); // Ожидаемый вывод: (пусто)

    // 4. Команда: 1 5
    z3 = singleton(5);
    // print_zbior(z3); // Ожидаемый вывод: 5 

    // 5. Команда: 2 1 3
    z4 = suma(z1, z3);
    //print_zbior(z4); // Ожидаемый вывод: -18 -13 -8 -3 2 5 7 12 

    // 6. Команда: 4 4 1
    z5 = roznica(z4, z1);
    //print_zbior(z5); // Ожидаемый вывод: 5 

    // 7. Команда: 3 5 3
    z6 = iloczyn(z5, z3);
    //print_zbior(z6); // Ожидаемый вывод: 5 

    //-18 -13 -8 -3 2 5 7 12 
    //5
    // 8. Команда: 3 4 5
    printf("--");
    print_zbior(z4);
    print_zbior(z5);

    z7 = iloczyn(z4, z5);
    // print_zbior(z7); // Ожидаемый вывод: 5 

    // 9. Команда: 4 2 3
    z8 = roznica(z2, z3);
    // print_zbior(z8); // Ожидаемый вывод: (пусто)

    // --- Очистка ---
    // Ты ДОЛЖЕН освобождать память после каждой операции,
    // которую ты создал.
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    free_zbior(z3);
    free_zbior(z4);
    free_zbior(z5);
    free_zbior(z6);
    free_zbior(z7);
    free_zbior(z8);

}
void f2(){
    // Объявляем переменные для 10 результатов
    zbior_ary z0, z1, z2, z3, z4, z5, z6, z7, z8, z9;

    // 1. Команда: 0 -12 7 9
    z0 = ciag_arytmetyczny(-12, 7, 9);
    print_zbior(z0); // Ожидаемый вывод: -12 -5 2 9 

    // 2. Команда: 1 -8
    z1 = singleton(-8);
    print_zbior(z1); // Ожидаемый вывод: -8 

    // 3. Команда: 3 1 1
    z2 = iloczyn(z1, z1);
    print_zbior(z2); // Ожидаемый вывод: -8 

    // 4. Команда: 0 15 7 15
    z3 = ciag_arytmetyczny(15, 7, 15);
    print_zbior(z3); // Ожидаемый вывод: 15 

    // 5. Команда: 2 2 0
    z4 = suma(z2, z0);
    print_zbior(z4); // Ожидаемый вывод: -12 -8 -5 2 9 (или зависит от isItemsCommon)

    // 6. Команда: 0 -17 7 -17
    z5 = ciag_arytmetyczny(-17, 7, -17);
    print_zbior(z5); // Ожидаемый вывод: -17 

    // 7. Команда: 3 1 4
    z6 = iloczyn(z1, z4);
    print_zbior(z6); // Ожидаемый вывод: -8 

    // 8. Команда: 2 2 6
    z7 = suma(z2, z6);
    print_zbior(z7); // Ожидаемый вывод: -8 

    // 9. Команда: 1 16
    z8 = singleton(16);
    print_zbior(z8); // Ожидаемый вывод: 16 

    // 10. Команда: 2 2 3
    z9 = suma(z2, z3);
    print_zbior(z9); // Ожидаемый вывод: -8 15 (или зависит от isItemsCommon)

    // --- Очистка ---
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    free_zbior(z3);
    free_zbior(z4);
    free_zbior(z5);
    free_zbior(z6);
    free_zbior(z7);
    free_zbior(z8);
    free_zbior(z9);

}

void f3(){
    // Объявляем переменные для 8 операций
    zbior_ary z0, z1, z2, z3, z4, z5, z6, z7; // z7 не будет использована

    // 1. Команда: 0 9 2 15
    z0 = ciag_arytmetyczny(9, 2, 15);
    print_zbior(z0); // Ожидаемый вывод: 9 11 13 15 

    // 2. Команда: 0 10 2 20
    z1 = ciag_arytmetyczny(10, 2, 20);
    print_zbior(z1); // Ожидаемый вывод: 10 12 14 16 18 20 

    // 3. Команда: 7 0
    // (Эта команда не создает новое множество, она вызывает ary(z0))
    // (Предполагая, что ary возвращает unsigned)
    printf("%u\n", ary(z0)); // Ожидаемый вывод: 1 

    // 4. Команда: 2 0 1
    z2 = suma(z0, z1);
    print_zbior(z2); // Ожидаемый вывод: 9 10 11 12 13 14 15 16 18 20 (или зависит от isItemsCommon)

    // 5. Команда: 4 1 1
    z3 = roznica(z1, z1);
    print_zbior(z3); // Ожидаемый вывод: (пусто)

    printf("ss");
    print_zbior(z2);
    print_zbior(z1);

    // 6. Команда: 4 2 1
    z4 = roznica(z2, z1);
    print_zbior(z4); // Ожидаемый вывод: 9 11 13 15 (т.е. z0)
    print(z4);
    // 7. Команда: 0 10 2 16
    z5 = ciag_arytmetyczny(10, 2, 16);
    //print_zbior(z5); // Ожидаемый вывод: 10 12 14 16 

    // 8. Команда: 0 -5 2 17
    z6 = ciag_arytmetyczny(-5, 2, 17);
    //print_zbior(z6); // Ожидаемый вывод: -5 -3 -1 1 3 5 7 9 11 13 15 17 

    // --- Очистка ---
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    free_zbior(z3);
    free_zbior(z4);
    free_zbior(z5);
    free_zbior(z6);
    // z7 не использовалась, освобождать не нужно

}

void f4(){ // suma with q
    // Объявляем переменные для 7 операций, создающих множества
    zbior_ary z0, z1, z2, z3, z4, z5, z6;

    // 1. Команда: 0 -13 7 -6
    z0 = ciag_arytmetyczny(-13, 7, -6);
    print_zbior(z0); // Ожидаемый вывод: -13 -6 

    // 2. Команда: 2 0 0
    z1 = suma(z0, z0);
    print_zbior(z1); // Ожидаемый вывод: -13 -6 

    // 3. Команда: 5 1 8
    // (Это nalezy(z1, 8), она не создает z2)
    printf("%u\n", nalezy(z1, 8)); // Ожидаемый вывод: 0 

    // 4. Команда: 5 0 16
    // (Это nalezy(z0, 16), она не создает z2)
    printf("%u\n", nalezy(z0, 16)); // Ожидаемый вывод: 0 

    // 5. Команда: 1 15
    z2 = singleton(15);
    print_zbior(z2); // Ожидаемый вывод: 15 

    // 6. Команда: 1 -20
    z3 = singleton(-20);
    print_zbior(z3); // Ожидаемый вывод: -20 

    // 7. Команда: 1 0
    z4 = singleton(0);
    print_zbior(z4); // Ожидаемый вывод: 0 

    // 8. Команда: 2 0 3
    printf("zz");
    print_zbior(z0);
    print_zbior(z3);
    z5 = suma(z0, z3);

    print_zbior(z5); // Ожидаемый вывод: -20 -13 -6 (или зависит от isItemsCommon)

    // 9. Команда: 7 5
    // (Это ary(z5), она не создает z6)
    print_zbior(z5);
    printf("%u\n", ary(z5)); // Ожидаемый вывод: (зависит от suma, вероятно 2 или 3)

    // 10. Команда: 2 5 4
    z6 = suma(z5, z4);
    //print_zbior(z6); // Ожидаемый вывод: -20 -13 -6 0 (или зависит от isItemsCommon)

    // --- Очистка ---
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    free_zbior(z3);
    free_zbior(z4);
    free_zbior(z5);
    free_zbior(z6);
}

void f5(){ //55459
    // Объявляем переменные для 6 операций, создающих множества
    zbior_ary z0, z1, z2, z3, z4, z5;

    // 1. Команда: 0 0 2 20
    z0 = ciag_arytmetyczny(0, 2, 20);
    print_zbior(z0); // Ожидаемый вывод: 0 2 4 6 8 10 12 14 16 18 20 

    // 2. Команда: 0 -11 2 5
    z1 = ciag_arytmetyczny(-11, 2, 5);
    print_zbior(z1); // Ожидаемый вывод: -11 -9 -7 -5 -3 -1 1 3 5 

    // 3. Команда: 0 -14 2 14
    z2 = ciag_arytmetyczny(-14, 2, 14);
    print_zbior(z2); // Ожидаемый вывод: -14 -12 -10 -8 -6 -4 -2 0 2 4 6 8 10 12 14 

    printf("zz");
    print_zbior(z1);
    print_zbior(z0);
    // 4. Команда: 2 1 0
    z3 = suma(z1, z0);
    print_zbior(z3); // Ожидаемый вывод: (зависит от isItemsCommon)

    // 5. Команда: 5 0 -13
    // (Это nalezy(z0, -13), она не создает z4)
    printf("%u\n", nalezy(z0, -13)); // Ожидаемый вывод: 0 

    // 6. Команда: 7 0
    // (Это ary(z0), она не создает z4)
    printf("%u\n", ary(z0)); // Ожидаемый вывод: 1 
    printf("pizdec");
    print_zbior(z3);
    print_zbior(z2);

    // 7. Команда: 3 3 2
    z4 = iloczyn(z3, z2);
    print_zbior(z4); // Ожидаемый вывод: (зависит от z3)

    // 8. Команда: 5 2 10
    // (Это nalezy(z2, 10), она не создает z5)
    printf("%u\n", nalezy(z2, 10)); // Ожидаемый вывод: 1 

    // 9. Команда: 4 4 4
    z5 = roznica(z4, z4);
    print_zbior(z5); // Ожидаемый вывод: (пусто)

    // --- Очистка ---
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    free_zbior(z3);
    free_zbior(z4);
    free_zbior(z5);
}

void f6(){ //38577
    // Объявляем переменные для 8 операций, создающих множества
    zbior_ary z0, z1, z2, z3, z4, z5, z6, z7;

    // 1. Команда: 0 -8 7 13
    z0 = ciag_arytmetyczny(-8, 7, 13);
    print_zbior(z0); // Ожидаемый вывод: -8 -1 6 13 

    // 2. Команда: 5 0 7
    // (Это nalezy(z0, 7), она не создает z1)
    printf("%u\n", nalezy(z0, 7)); // Ожидаемый вывод: 0 

    // 3. Команда: 5 0 12
    // (Это nalezy(z0, 12), она не создает z1)
    printf("%u\n", nalezy(z0, 12)); // Ожидаемый вывод: 0 

    // 4. Команда: 3 0 0
    z1 = iloczyn(z0, z0);
    print_zbior(z1); // Ожидаемый вывод: -8 -1L -1 6 13 

    // 5. Команда: 1 5
    z2 = singleton(5);
    print_zbior(z2); // Ожидаемый вывод: 5 

    // 6. Команда: 0 6 7 6
    z3 = ciag_arytmetyczny(6, 7, 6);
    print_zbior(z3); // Ожидаемый вывод: 6 

    // 7. Команда: 2 2 3
    z4 = suma(z2, z3);
    print_zbior(z4); // Ожидаемый вывод: 5 6 (или зависит от isItemsCommon)

    // 8. Команда: 3 3 4
    z5 = iloczyn(z3, z4);
    print_zbior(z5); // Ожидаемый вывод: 6 

    // 9. Команда: 4 4 1
    printf("ddd");
    print_zbior(z4);
    print_zbior(z1);

    z6 = roznica(z4, z1);
    print_zbior(z6); // Ожидаемый вывод: 5 (или зависит от isItemsCommon)

    // 10. Команда: 4 3 6
    printf("ddd");
    print_zbior(z3);
    print_zbior(z6);
    z7 = roznica(z3, z6);
    print_zbior(z7); // Ожидаемый вывод: (зависит от z6, вероятно 6 или пусто)

    // --- Очистка ---
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    free_zbior(z3);
    free_zbior(z4);
    free_zbior(z5);
    free_zbior(z6);
    free_zbior(z7);
}

int main() {

    f6();
    return 0;
}
