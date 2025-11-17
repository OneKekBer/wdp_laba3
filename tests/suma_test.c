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

void roznica_test(){
    // --- 0. Настройка ---
    // z_A = {[0, 100]}, q=2. 
    // ЭТО УСТАНАВЛИВАЕТ ГЛОБАЛЬНЫЙ Q = 2
    zbior_ary z_A = ciag_arytmetyczny(0, 2, 100);
    printf("z_A (A): ");
    print_zbior(z_A); // Ожидаемый вывод: 0 2 4 ... 100

    // z_B_part1 = {[10, 20]}, q=2
    zbior_ary z_B_part1 = ciag_arytmetyczny(10, 2, 20);
    // z_B_part2 = {[30, 40]}, q=2
    zbior_ary z_B_part2 = ciag_arytmetyczny(30, 2, 40);
    // z_B = {[10, 20], [30, 40]} (q=2)
    zbior_ary z_B = suma(z_B_part1, z_B_part2);
    printf("z_B (B): ");
    print_zbior(z_B); // Ожидаемый вывод: 10 12 ... 20 30 32 ... 40


    // === ТЕСТ 1: "КЛАССИЧЕСКОЕ КРОМСАНИЕ" (Один A, много B) ===
    // A - B, где A = [0, 100], B = {[10, 20], [30, 40]}. Q=2.
    // Должен "вырезать" [8, 22] и [28, 42].
    // Результат: {[0, 6], [24, 26], [44, 100]} (q=2)
    zbior_ary z_R1 = roznica(z_A, z_B);
    printf("Test 1 (A - B): ");
    print_zbior(z_R1); // Ожидаемый вывод: 0 2 4 6 24 26 44 46 ... 100


    // === ТЕСТ 2: "ПОЛНОЕ ПОГЛОЩЕНИЕ" (Много A, один B) ===
    // B - A, где B = {[10, 20], [30, 40]}, A = [0, 100]. Q=2.
    // A "вырезает" [ -2, 102 ], что полностью поглощает B.
    // Результат: {} (пусто)
    zbior_ary z_R2 = roznica(z_B, z_A);
    printf("Test 2 (B - A): ");
    print_zbior(z_R2); // Ожидаемый вывод: (пусто)


    // === ТЕСТ 3: "A - A" (Самовычитание) ===
    // A - A
    // Результат: {} (пусто)
    zbior_ary z_R3 = roznica(z_A, z_A);
    printf("Test 3 (A - A): ");
    print_zbior(z_R3); // Ожидаемый вывод: (пусто)


    // === ТЕСТ 4: "NON-COMMON" (Пересекаются, но isItemsCommon = false) ===
    // A = {[0, 100]}, q=2, Q=2
    // z_B_noncommon = {[11, 21]}, q=2
    // isItemsCommon([0, 100], [11, 21], 2) -> (abs(0-11)%2 == 1) -> false
    // `roznica` должна "проигнорировать" [11, 21], A не должен измениться.
    zbior_ary z_B_noncommon = ciag_arytmetyczny(11, 2, 21);
    zbior_ary z_R4 = roznica(z_A, z_B_noncommon);
    printf("Test 4 (Non-Common): ");
    print_zbior(z_R4); // Ожидаемый вывод: 0 2 4 ... 100 (z_A)


    // === ТЕСТ 5: "СМЕШАННЫЙ" (Common и Non-Common) ===
    // A = {[0, 100]}, q=2, Q=2
    // B = {[10, 20](common), [31, 41](non-common), [50, 60](common)}
    // Собираем z_B_mix...
    zbior_ary z_B_nc_part = ciag_arytmetyczny(31, 2, 41); // [31, 41] (non-common)
    zbior_ary z_B_c_part = ciag_arytmetyczny(50, 2, 60);  // [50, 60] (common)
    zbior_ary z_B_mix1 = suma(z_B_part1, z_B_nc_part);    // {[10, 20], [31, 41]}
    zbior_ary z_B_mix = suma(z_B_mix1, z_B_c_part);       // {[10, 20], [31, 41], [50, 60]}
    
    // A - z_B_mix
    // Должен вырезать [8, 22] и [48, 62].
    // Должен проигнорировать [31, 41].
    // Результат: {[0, 6], [24, 46], [64, 100]}
    zbior_ary z_R5 = roznica(z_A, z_B_mix);
    printf("Test 5 (Mixed): ");
    print_zbior(z_R5); // Ожидаемый вывод: 0 2 4 6 24 26 ... 46 64 66 ... 100


    // --- Очистка ---
    free_zbior(z_A);
    free_zbior(z_B_part1);
    free_zbior(z_B_part2);
    free_zbior(z_B);
    free_zbior(z_R1);
    free_zbior(z_R2);
    free_zbior(z_R3);
    free_zbior(z_B_noncommon);
    free_zbior(z_R4);
    free_zbior(z_B_nc_part);
    free_zbior(z_B_c_part);
    free_zbior(z_B_mix1);
    free_zbior(z_B_mix);
    free_zbior(z_R5);
}

void f7(){
    zbior_ary z0, z1, z2, z3, z4, z5, z6, z7;
    z0 = ciag_arytmetyczny(-15, 5, 5);
    z1 = ciag_arytmetyczny(-4, 5, 1);
    z2 = ciag_arytmetyczny(-14, 5, -4);
    print_zbior(roznica(suma(z0, z1), z2));
}

void f8(){ //good roznica test 
    zbior_ary z0, z1, z2, z3, z4, z5, z6, z7;
    z0 = ciag_arytmetyczny(-20, 5, 5);
    z2 = ciag_arytmetyczny(20, 5, 100);
    z1 = ciag_arytmetyczny(-10, 5, 50);
    z3 = suma(z0, z2);
    print_zbior(z3);
    print_zbior(roznica(z1, z3));    
}

void f9(){
    zbior_ary z0, z1, z2, z3, z4, z5, z6, z7;
    z0 = ciag_arytmetyczny(-15, 5, 5);
    z2 = singleton(-11);
    //z1 = (-10, 5, 50);
    z3 = suma(z0, z2);
    print_zbior(z3);
    print_zbior(roznica(z2, z3));    
}

void f10(){
    zbior_ary z0, z1, z2, z3, z4, z5, z6, z7;
    z0 = ciag_arytmetyczny(-15, 5, 5);
    z1 = ciag_arytmetyczny(-4, 5, 1);
    z2 = ciag_arytmetyczny(-14, 5, -4);
    z3 = suma(z0, z1);
    print_zbior(z3);
    print_zbior(roznica(z3, z2));    
}
void f11(){
    zbior_ary z0, z1, z2, z3, z4, z5, z6, z7;
    z0 = ciag_arytmetyczny(-1, 3, 5);
    int odp = nalezy(z0, 4);
    printf("%d", odp);
    //z2 = ciag_arytmetyczny(-14, 5, -4);
    //z3 = iloczyn(z0, z1);
    //print_zbior(z3);

    //print_zbior(roznica(z3, z2));    
}

void f12(){ // iloczyn test
    zbior_ary z0, z1, z2, z3, z4, z5, z6, z7;
    z0 = ciag_arytmetyczny(2, 4, 6);
    z1 = ciag_arytmetyczny(-2, 4, 2);

    z2 = iloczyn(z0, z1);
    print_zbior(z2);
    //z2 = ciag_arytmetyczny(-14, 5, -4);
    //z3 = iloczyn(z0, z1);
    //print_zbior(z3);

    //print_zbior(roznica(z3, z2));    
}

void f13(){ // iloczyn test
    zbior_ary z0, z1, z2, z3, z4, z5, z6, z7;
    z0 = ciag_arytmetyczny(-5, 3, 4);
    z1 = singleton(4);

    z2 = roznica(z0, z1);
    print_zbior(z2);
    //z2 = ciag_arytmetyczny(-14, 5, -4);
    //z3 = iloczyn(z0, z1);
    //print_zbior(z3);

    //print_zbior(roznica(z3, z2));    
}

void f14(){ // iloczyn test
    zbior_ary z0, z1, z2, z3, z4, z5, z6, z7;
    z0 = ciag_arytmetyczny(-17, 2, -1);
    z1 = ciag_arytmetyczny(-5, 2, 7);
    z3 = suma(z0, z1);
    z4 = singleton(-1);

    z5 = iloczyn(z3, z4);
    print_zbior(z5);
    //z2 = ciag_arytmetyczny(-14, 5, -4);
    //z3 = iloczyn(z0, z1);
    //print_zbior(z3);

    //print_zbior(roznica(z3, z2));    
}

void f15() {
    printf("\n--- Test (Симуляция входной последовательности) ---\n");
    
    // Массив для хранения всех созданных наборов (v[0] до v[6])
    zbior_ary v[7]; 
    
    // 0. (type 0) v[0] = ciag_arytmetyczny(11, 1, 18)
    v[0] = ciag_arytmetyczny(11, 1, 18);
    printf("[0] (0 11 1 18): "); print_zbior(v[0]);
    
    // 1. (type 1) v[1] = singleton(-3)
    v[1] = singleton(-3);
    printf("[1] (1 -3): "); print_zbior(v[1]);
    
    // 2. (type 2) v[2] = suma(v[1], v[0])
    v[2] = suma(v[1], v[0]);
    printf("[2] (2 1 0): "); print_zbior(v[2]);
    
    // 3. (type 1) v[3] = singleton(-11)
    v[3] = singleton(-11);
    printf("[3] (1 -11): "); print_zbior(v[3]);
    
    // 4. (type 5) nalezy(v[3], -1) -> Output
    bool nalezy_result = nalezy(v[3], -1);
    printf("Output (5 3 -1): %s\n", nalezy_result ? "1 (true)" : "0 (false)");
    
    // 5. (type 0) v[4] = ciag_arytmetyczny(-5, 1, 16)
    v[4] = ciag_arytmetyczny(-5, 1, 16);
    printf("[4] (0 -5 1 16): "); print_zbior(v[4]);

    // 6. (type 7) ary(v[2]) -> Output
    unsigned ary_result = ary(v[2]);
    printf("Output (7 2): %u\n", ary_result);
    
    // 7. (type 3) v[5] = iloczyn(v[4], v[2])
    print_zbior(v[4]);
    print_zbior(v[2]);
    v[5] = iloczyn(v[4], v[2]);
    printf("[5] (3 4 2): "); print_zbior(v[5]);

    // 8. (type 4) v[6] = roznica(v[0], v[2])
    v[6] = roznica(v[0], v[2]);
    printf("[6] (4 0 2): "); print_zbior(v[6]);
    
    // Cleanup: Освобождаем память для всех созданных наборов
    for (int i = 0; i < 7; ++i) {
        free_zbior(v[i]);
    }
}



int main() {
    f15();
    //roznica_test();
    //test5_b_covers_start();

    return 0;
}
