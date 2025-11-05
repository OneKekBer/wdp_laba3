#include <stdlib.h>
#include <stdio.h>
#include "zbior_ary.h"
#include <math.h>
#include <assert.h>
#include "../tests/print.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int Q = 0;

zbior_ary ciag_arytmetyczny(int a, int q, int b){
    if(Q == 0) Q = q;

    item *sets = (item *)malloc(sizeof(item));
    item i = {a, b};
    zbior_ary z;
    
    sets[0] = i;
    z.n = 1;
    z.q = q;
    z.sets = sets;
    return z;
}

zbior_ary singleton(int a){
    item *sets = (item *)malloc(1 * sizeof(item));
    item it = {a, a};
    zbior_ary z;
    
    sets[0] = it;
    z.sets = sets;
    z.n = 1;
    z.q = Q;
    return z;
}

unsigned moc(zbior_ary A){ //maybe current item
    int cnt = 0;
    for(int i = 0; i < A.n; ++i){
        item item = A.sets[i];
        
        cnt += (item.b - item.a) / Q + 1;
    } 

    return (unsigned)cnt;
}

unsigned ary(zbior_ary A){
    return (unsigned)A.n;
}

void print_item1(item i) {
    printf("item");
    printf("[%d,%d]", i.a, i.b);
    printf("\n");
}

//if they has common q, [1,3] == [5,7] is common, [2,4] != [1,3] not common
bool isItemsCommon(item item1, item item2, int q){
    if(q == 1) return true;
    return (abs(item1.a - item2.a) % q == 0) && (abs(item1.b - item2.b) % q == 0);
}

bool isItemValid(item item){
    return item.a <= item.b;
}

bool isItemsIntersectsWithQ(item item1, item item2) {
    long long expanded_a = (long long)item2.a - Q;
    long long expanded_b = (long long)item2.b + Q;
    
    long long max_start = max((long long)item1.a, expanded_a);
    long long min_end = min((long long)item1.b, expanded_b);

    return max_start <= min_end;
}

item getItemsIntersectionWithQ(item item1, item item2){
    long long expanded_a = (long long)item2.a - Q;
    long long expanded_b = (long long)item2.b + Q;

    item newItem;
    newItem.a = (int)max((long long)item1.a, expanded_a);
    newItem.b = (int)min((long long)item1.b, expanded_b);
    return newItem;
}

bool isItemsIntersects(item item1, item item2) {
    return (max(item1.a, item2.a) <= min(item1.b, item2.b));
}

item getItemsIntersection(item item1, item item2){
    item newItem;
    newItem.a = max(item1.a, item2.a);
    newItem.b = min(item1.b, item2.b);    
    return newItem;
}

item getItemsSum(item item1, item item2){
    item newItem;
    newItem.a = min(item1.a, item2.a);
    newItem.b = max(item1.b, item2.b);
    return newItem;
}

//assume that all sets are sorted
zbior_ary suma(zbior_ary A, zbior_ary B){
    int n = A.n + B.n;
    item *newSets = (item *)malloc((unsigned)n * sizeof(item));
    int insertIdx = 0, idxA = 0, idxB = 0;

    while(idxA < A.n && idxB < B.n){
        item itemA = A.sets[idxA]; // W: can be dangerous
        item itemB = B.sets[idxB];
        
        if(insertIdx > 0){
            item prevItem = insertIdx > 0 ? newSets[insertIdx - 1] : (item){0, 0};
            bool merged = false;

            if(isItemsCommon(prevItem, itemA, Q) && isItemsIntersectsWithQ(prevItem, itemA)){
                newSets[insertIdx - 1] = getItemsSum(prevItem, itemA);
                idxA++;
                merged = true;
            }

            if(isItemsCommon(prevItem, itemB, Q) && isItemsIntersectsWithQ(prevItem, itemB)){
                newSets[insertIdx - 1] = getItemsSum(prevItem, itemB);
                idxB++;
                merged = true;
            }            

            if(merged) continue;
        }   
        // print_item1(itemA);
        // print_item1(itemB);
        // printf("%d", Q);
        if(isItemsCommon(itemA, itemB, Q) && isItemsIntersectsWithQ(itemA, itemB)){
            // printf("common rabotaet");
            newSets[insertIdx] = getItemsSum(itemA, itemB); 
            insertIdx++;
            idxA++;
            idxB++;
            continue;
        }

        if(itemA.a < itemB.a){
            newSets[insertIdx] = itemA;
            idxA++;
            insertIdx++;
        }
        else{
            newSets[insertIdx] = itemB;
            idxB++;
            insertIdx++;
        } 
    }

    //now fill newSets with items which wasnt added
    if(idxA < A.n){
        for(int i = idxA; i < A.n; ++i){
            item itemA = A.sets[i];

            if(insertIdx > 0){
                item prevItem = newSets[insertIdx - 1];

                if(isItemsCommon(itemA, prevItem, Q) && isItemsIntersectsWithQ(itemA, prevItem)){
                    newSets[insertIdx - 1] = getItemsSum(itemA, prevItem);        
                    continue;
                }
            }   

            newSets[insertIdx] = itemA;
            insertIdx++;
        }
    }
    
    if(idxB < B.n){
        for(int i = idxB; i < B.n; ++i){
            item itemB = B.sets[i];

            if(insertIdx > 0){
                item prevItem = newSets[insertIdx - 1];

                if(isItemsCommon(itemB, prevItem, Q) && isItemsIntersectsWithQ(itemB, prevItem)){
                    newSets[insertIdx - 1] = getItemsSum(itemB, prevItem);        
                    continue;
                }
            }   

            newSets[insertIdx] = itemB;
            insertIdx++;
        }
    }

    if(insertIdx < n){
        item *reSets = (item *)realloc(newSets, (unsigned)insertIdx * sizeof(item));
        if(reSets != NULL) newSets = reSets;
    }
   
    zbior_ary newZbior;
    newZbior.n = insertIdx;
    newZbior.q = max(A.q, max(B.q, Q));
    newZbior.sets = newSets;
    return newZbior;
}

bool areSameSign(int a, int b) {
    // Если (a ^ b) >= 0, знаковые биты были одинаковы.
    return (a ^ b) >= 0; 
}

zbior_ary createZbior(int n, int q, item *sets){
    zbior_ary newZbior;
    newZbior.q = q;
    newZbior.n = n;
    newZbior.sets = sets;
    return newZbior;
}

bool isEmptyZbior(zbior_ary A){
    return A.sets == NULL;
}

zbior_ary roznica(zbior_ary A, zbior_ary B){
    if(B.n == 0) return A;
    int n = A.n + B.n;
    int insertIdx = 0, idxA = 0, idxB = 0;
    item *newSets = (item *)malloc((unsigned)n * sizeof(item));
    
    item currentA;
    if(idxA < A.n){
        currentA = A.sets[idxA];
    }else{
        return createZbior(0, 0, NULL);
    }
    
    while(idxA < A.n &&  idxB < B.n){
        item itemB = B.sets[idxB];
    
        if(isItemsIntersects(currentA, itemB)){
            if(isItemsCommon(currentA, itemB, Q)){
                if(currentA.a < itemB.a){ //when a = [2,8] b = [6,8] leftDiff = [2,4] for q = 2 
                    item leftDiff;
                    leftDiff.a = currentA.a;
                    leftDiff.b = itemB.a - Q;
                    newSets[insertIdx] = leftDiff;
                    insertIdx++;
                }
            
                if(currentA.b > itemB.b){ //when a = [2,8] b = [2,4] rightDiff = [6,8] for q = 2
                    currentA.a = itemB.b + Q;
                    idxB++;
                }else{
                    idxA++;
                    if(idxA < A.n) currentA = A.sets[idxA];  
                }
            }else{
                
                if(idxA + 1 < A.n){
                    if(isItemsIntersects(A.sets[idxA + 1], itemB)){
                        newSets[insertIdx] = currentA;
                        idxA++;
                        insertIdx++;
                        currentA = A.sets[idxA];
                        continue;
                    }
                }

                if(idxB + 1 < B.n){
                    if(isItemsIntersects(B.sets[idxA + 1], currentA)){
                        idxB++;
                        continue;
                    }
                }

                if (currentA.a < itemB.a) {
                    newSets[insertIdx] = currentA;
                    insertIdx++;
                    idxA++;
                    if(idxA < A.n) currentA = A.sets[idxA];
                } else if (itemB.a < currentA.a) {
                    idxB++;
                } else {
                    // Начинаются в одной точке, но не common
                    idxA++;
                    idxB++;
                }
            }
        }else if(currentA.b < itemB.a){
            newSets[insertIdx] = currentA;
            insertIdx++;
            idxA++;
            if(idxA < A.n) currentA = A.sets[idxA];
        }else{
            idxB++;
        }
    }

    if(idxA < A.n){
        newSets[insertIdx] = currentA;
        insertIdx++; 
        idxA++;
        for(int i = idxA; i < A.n; ++i){
            newSets[insertIdx] = A.sets[i];
            insertIdx++;
        }
    }
    
    //if result is empty item 
    if(insertIdx == 0){ // REWORK
        return createZbior(0, 0, NULL);
    }
 
    if (insertIdx < n) {
        item *reSets = (item *)realloc(newSets, insertIdx * sizeof(item));
        if (reSets != NULL) newSets = reSets;
    }

    return createZbior(insertIdx, Q, newSets);
}

zbior_ary iloczyn(zbior_ary A, zbior_ary B){
    int n = max(A.n, B.n);
    item *newSets = (item *)malloc((unsigned)n * sizeof(item));
    int insertIdx = 0, idxA = 0, idxB = 0;

    while(idxA < A.n && idxB < B.n){
    item itemA = A.sets[idxA];
    item itemB = B.sets[idxB];

    if(isItemsIntersects(itemA, itemB)){
        if(isItemsCommon(itemA, itemB, Q)) {
            //printf("yes");
            item intersection = getItemsIntersection(itemA, itemB);
            if (isItemValid(intersection)) {
                newSets[insertIdx] = intersection;
                insertIdx++;
            }
            
            if (itemA.b < itemB.b) {
                idxA++;
            } else if (itemB.b < itemA.b) {
                idxB++;
            } else {
                idxA++;
                idxB++;
            }
        } 
        else {
            if(idxA + 1 < A.n){
                if(isItemsIntersects(A.sets[idxA + 1], itemB)){
                    idxA++;
                    continue;
                }
            }

            if(idxB + 1 < B.n){
                if(isItemsIntersects(B.sets[idxA + 1], itemA)){
                    idxB++;
                    continue;
                }
            }

            if (itemA.a < itemB.a) {
                idxA++;
            } else if (itemB.a < itemA.a) {
                idxB++;
            } else {
                idxA++;
                idxB++;
            }
        }
    } 
    // 3. Нет геометрического пересечения: A левее B
    else if(itemA.b < itemB.a){
        idxA++;
    } 
    // 4. Нет геометрического пересечения: B левее A
    else { // (itemB.b < itemA.a)
        idxB++;
    }
}

    if(insertIdx < n){
        item *reSets = (item *)realloc(newSets, (unsigned)insertIdx * sizeof(item));
        if(reSets != NULL) newSets = reSets;
    }

    return createZbior(insertIdx, max(A.q, max(B.q, Q)), newSets);
}

//find info bout b > 0 ? or not
bool nalezy(zbior_ary A, int b) {
    int l = 0, r = A.n - 1;

    while (l <= r) {
        int mid = l + (r - l) / 2;
        item midItem = A.sets[mid];

        if (midItem.b == 0 && midItem.a >= 0) {
            if (midItem.a == b)
                return true;
            if (b < midItem.a)
                r = mid - 1;
            else
                l = mid + 1;
            continue;
        }

        //check if element b in range of [a,b]
        if (b >= midItem.a && b <= midItem.b){
            if (isItemsCommon(midItem, (item){b, b}, Q))
                return true;
        }

        if (b < midItem.a)
            r = mid - 1;
        else
            l = mid + 1;
    }

    return false;
}

