#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include "./../zbior_ary.h"


using namespace std;

// Funkcja konwertująca zbior_ary na wektor liczb
vector<long long> zbior_to_vector(zbior_ary A) {
    vector<long long> result;
    for (long long i = 0; i < A.n; i++) {
        item it = A.sets[i];
        for (long long x = it.a; x <= it.b; x += A.q) {
            result.push_back(x);
        }
    }
    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()), result.end());
    return result;
}

// Funkcja porównująca zbior_ary z oczekiwanym wektorem
bool isCorrect(zbior_ary A, const vector<long long>& expected) {
    vector<long long> actual = zbior_to_vector(A);
    
    if (actual.size() != expected.size()) {
        cout << "  ❌ Rozmiary się różnią: actual=" << actual.size() 
             << ", expected=" << expected.size() << endl;
        return false;
    }
    
    for (size_t i = 0; i < actual.size(); i++) {
        if (actual[i] != expected[i]) {
            cout << "  ❌ Różnica na pozycji " << i << ": actual=" 
                 << actual[i] << ", expected=" << expected[i] << endl;
            return false;
        }
    }
    
    return true;
}

// Pomocnicza funkcja do wypisywania zbioru
void print_zbior(zbior_ary z) {
    vector<long long> v = zbior_to_vector(z);
    cout << "  Elementy: ";
    if (v.empty()) {
        cout << "(pusty)";
    } else {
        for (size_t i = 0; i < min(v.size(), size_t(20)); i++) {
            cout << v[i] << " ";
        }
        if (v.size() > 20) cout << "... (+" << (v.size() - 20) << " więcej)";
    }
    cout << endl;
}

void free_zbior(zbior_ary z) {
    if (z.sets != NULL) {
        free(z.sets);
    }
}

// Test 1: A - A = ∅
bool test1() {
    cout << "\n=== TEST 1: A - A = ∅ ===" << endl;
    zbior_ary z0 = ciag_arytmetyczny(-18, 5, 12);
    zbior_ary z1 = roznica(z0, z0);
    
    vector<long long> expected = {};  // Pusty
    bool result = isCorrect(z1, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else { 
        cout << "  ❌ FAILED" << endl;
        print_zbior(z1);
    }
    
    free_zbior(z0);
    free_zbior(z1);
    return result;
}

// Test 2: A - ∅ = A
bool test2() {
    cout << "\n=== TEST 2: A - ∅ = A ===" << endl;
    zbior_ary z0 = ciag_arytmetyczny(10, 7, 80);
    zbior_ary z_empty = createZbior(0, 7, NULL);
    zbior_ary z1 = roznica(z0, z_empty);
    
    vector<long long> expected = {10, 17, 24, 31, 38, 45, 52, 59, 66, 73, 80};
    bool result = isCorrect(z1, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else {
        cout << "  ❌ FAILED" << endl;
        print_zbior(z1);
    }
    
    free_zbior(z0);
    free_zbior(z1);
    return result;
}

// Test 3: ∅ - A = ∅
bool test3() {
    cout << "\n=== TEST 3: ∅ - A = ∅ ===" << endl;
    zbior_ary z_empty = createZbior(0, 5, NULL);
    zbior_ary z0 = ciag_arytmetyczny(5, 5, 35);
    zbior_ary z1 = roznica(z_empty, z0);
    
    vector<long long> expected = {};
    bool result = isCorrect(z1, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else {
        cout << "  ❌ FAILED" << endl;
        print_zbior(z1);
    }
    
    free_zbior(z0);
    free_zbior(z1);
    return result;
}

// Test 4: B całkowicie pokrywa A
bool test4() {
    cout << "\n=== TEST 4: B całkowicie pokrywa A ===" << endl;
    zbior_ary z0 = ciag_arytmetyczny(10, 5, 30);
    zbior_ary z1 = ciag_arytmetyczny(5, 5, 40);
    zbior_ary z2 = roznica(z0, z1);
    
    vector<long long> expected = {};
    bool result = isCorrect(z2, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else {
        cout << "  ❌ FAILED" << endl;
        print_zbior(z2);
    }
    
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    return result;
}

// Test 5: B pokrywa początek A
bool test5() {
    cout << "\n=== TEST 5: B pokrywa początek A ===" << endl;
    zbior_ary z0 = ciag_arytmetyczny(10, 5, 50);
    zbior_ary z1 = ciag_arytmetyczny(10, 5, 25);
    zbior_ary z2 = roznica(z0, z1);
    
    vector<long long> expected = {30, 35, 40, 45, 50};
    bool result = isCorrect(z2, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else {
        cout << "  ❌ FAILED" << endl;
        print_zbior(z2);
    }
    
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    return result;
}

// Test 6: B pokrywa koniec A
bool test6() {
    cout << "\n=== TEST 6: B pokrywa koniec A ===" << endl;
    zbior_ary z0 = ciag_arytmetyczny(10, 5, 50);
    zbior_ary z1 = ciag_arytmetyczny(35, 5, 50);
    zbior_ary z2 = roznica(z0, z1);
    
    vector<long long> expected = {10, 15, 20, 25, 30};
    bool result = isCorrect(z2, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else {
        cout << "  ❌ FAILED" << endl;
        print_zbior(z2);
    }
    
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    return result;
}

// Test 7: B w środku A
bool test7() {
    cout << "\n=== TEST 7: B w środku A (dzieli na dwie części) ===" << endl;
    zbior_ary z0 = ciag_arytmetyczny(10, 5, 50);
    zbior_ary z1 = ciag_arytmetyczny(25, 5, 35);
    zbior_ary z2 = roznica(z0, z1);
    
    vector<long long> expected = {10, 15, 20, 40, 45, 50};
    bool result = isCorrect(z2, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else {
        cout << "  ❌ FAILED" << endl;
        print_zbior(z2);
    }
    
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    return result;
}

// Test 8: Różne reszty
bool test8() {
    cout << "\n=== TEST 8: Różne reszty modulo q ===" << endl;
    zbior_ary z0 = ciag_arytmetyczny(10, 7, 80);  // rest = 3
    zbior_ary z1 = ciag_arytmetyczny(11, 7, 81);  // rest = 4
    zbior_ary z2 = roznica(z0, z1);
    
    vector<long long> expected = {10, 17, 24, 31, 38, 45, 52, 59, 66, 73, 80};
    bool result = isCorrect(z2, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else {
        cout << "  ❌ FAILED" << endl;
        print_zbior(z2);
    }
    
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    return result;
}

// Test 9: Wiele przedziałów w B
bool test9() {
    cout << "\n=== TEST 9: Wiele przedziałów w B ===" << endl;
    zbior_ary z0 = ciag_arytmetyczny(0, 5, 100);
    zbior_ary z1 = ciag_arytmetyczny(10, 5, 20);
    zbior_ary z2 = ciag_arytmetyczny(40, 5, 50);
    zbior_ary z3 = suma(z1, z2);
    zbior_ary z4 = roznica(z0, z3);
    
    vector<long long> expected;
    // {0, 5, 25, 30, 35, 55, 60, 65, ..., 100}
    expected.push_back(0);
    expected.push_back(5);
    for (long long x = 25; x <= 35; x += 5) expected.push_back(x);
    for (long long x = 55; x <= 100; x += 5) expected.push_back(x);
    
    bool result = isCorrect(z4, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else {
        cout << "  ❌ FAILED" << endl;
        print_zbior(z4);
    }
    
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    free_zbior(z3);
    free_zbior(z4);
    return result;
}

// Test 10: Liczby ujemne
bool test10() {
    cout << "\n=== TEST 10: Liczby ujemne ===" << endl;
    zbior_ary z0 = ciag_arytmetyczny(-50, 7, -10);
    zbior_ary z1 = ciag_arytmetyczny(-36, 7, -22);
    zbior_ary z2 = roznica(z0, z1);
    
    vector<long long> expected = {-50, -43, -15};
    bool result = isCorrect(z2, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else {
        cout << "  ❌ FAILED" << endl;
        print_zbior(z2);
    }
    
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    return result;
}

// Test 11: Singleton
bool test11() {
    cout << "\n=== TEST 11: Singleton ===" << endl;
    zbior_ary z0 = ciag_arytmetyczny(0, 10, 100);
    zbior_ary z1 = singleton(50);
    zbior_ary z2 = roznica(z0, z1);
    
    vector<long long> expected;
    for (long long x = 0; x <= 100; x += 10) {
        if (x != 50) expected.push_back(x);
    }
    
    bool result = isCorrect(z2, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else {
        cout << "  ❌ FAILED" << endl;
        print_zbior(z2);
    }
    
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    return result;
}

// Test 12: Złożone nakładanie
bool test12() {
    cout << "\n=== TEST 12: Złożone nakładanie ===" << endl;
    zbior_ary z0 = ciag_arytmetyczny(0, 3, 60);
    zbior_ary z1 = ciag_arytmetyczny(6, 3, 12);
    zbior_ary z2 = ciag_arytmetyczny(21, 3, 27);
    zbior_ary z3 = ciag_arytmetyczny(45, 3, 54);
    
    zbior_ary z4 = suma(z1, z2);
    zbior_ary z5 = suma(z4, z3);
    print_zbior(z5);
    zbior_ary z6 = roznica(z0, z5);
    
    vector<long long> expected;
    // {0, 3, 15, 18, 30, 33, 36, 39, 42, 57, 60}
    expected.push_back(0);
    expected.push_back(3);
    expected.push_back(15);
    expected.push_back(18);
    for (long long x = 30; x <= 42; x += 3) expected.push_back(x);
    expected.push_back(57);
    expected.push_back(60);
    
    bool result = isCorrect(z6, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else {
        cout << "  ❌ FAILED" << endl;
        print_zbior(z6);
    }
    
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    free_zbior(z3);
    free_zbior(z4);
    free_zbior(z5);
    free_zbior(z6);
    return result;
}

// Test 13: Zbiory rozłączne
bool test13() {
    cout << "\n=== TEST 13: Zbiory rozłączne ===" << endl;
    zbior_ary z0 = ciag_arytmetyczny(0, 5, 30);
    zbior_ary z1 = ciag_arytmetyczny(100, 5, 130);
    zbior_ary z2 = roznica(z0, z1);
    
    vector<long long> expected = {0, 5, 10, 15, 20, 25, 30};
    bool result = isCorrect(z2, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else {
        cout << "  ❌ FAILED" << endl;
        print_zbior(z2);
    }
    
    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    return result;
}

// Test 14: Kombinowany
bool test14() {
    cout << "\n=== TEST 14: Kombinowany test ===" << endl;
    zbior_ary z0, z1, z2, z3, z4, z5;

    z0 = ciag_arytmetyczny(-18, 5, 12);
    z1 = iloczyn(z0, z0);
    z2 = roznica(z1, z0);
    z3 = singleton(5);
    z4 = suma(z1, z3);
    z5 = roznica(z4, z1);
    
    vector<long long> expected = {5};
    bool result = isCorrect(z5, expected);
    
    if (result) cout << "  ✅ PASSED" << endl;
    else {
        cout << "  ❌ FAILED" << endl;
        print_zbior(z5);
    }

    free_zbior(z0);
    free_zbior(z1);
    free_zbior(z2);
    free_zbior(z3);
    free_zbior(z4);
    free_zbior(z5);
    return result;
}

int main() {
    cout << "==================================================" << endl;
    cout << "   AUTOMATYCZNE TESTY DLA FUNKCJI ROZNICA" << endl;
    cout << "==================================================" << endl;
    
    int passed = 0, total = 14;
    
    if (test1()) passed++;
    if (test2()) passed++;
    if (test3()) passed++;
    if (test4()) passed++;
    if (test5()) passed++;
    if (test6()) passed++;
    if (test7()) passed++;
    if (test8()) passed++;
    if (test9()) passed++;
    if (test10()) passed++;
    if (test11()) passed++;
    if (test12()) passed++;
    if (test13()) passed++;
    if (test14()) passed++;
    
    cout << "\n==================================================" << endl;
    cout << "   WYNIKI: " << passed << "/" << total << " testów zaliczonych" << endl;
    if (passed == total) {
        cout << "   🎉 WSZYSTKIE TESTY PRZESZŁY! 🎉" << endl;
    } else {
        cout << "   ⚠️  " << (total - passed) << " testów nie powiodło się" << endl;
    }
    cout << "==================================================" << endl;
    
    return (passed == total) ? 0 : 1;
}