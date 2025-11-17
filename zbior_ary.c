#include <stdlib.h>
#include <stdio.h>
#include "zbior_ary.h"
#include <math.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

long long Q = 0;

long getRest(long long a){
    long long r = a % Q;
    if (r < 0) r += Q;
    return r;
}

bool isElementInItem(item it, long long x){
    return (x >= it.a && x <= it.b) && (x - it.a) % Q == 0;
}

zbior_ary ciag_arytmetyczny(int a, int q, int b){
    if (Q == 0) Q = q;

    item *sets = (item *)malloc(sizeof(item));
    item i = {a, b, getRest(a)};
    //printf("%ld, %ld, %ld\n",i.a, i.b, i.rest);
    zbior_ary z;

    sets[0] = i;
    z.n = 1;
    z.q = q;
    z.sets = sets;
    return z;
}

zbior_ary singleton(int a){
    item *sets = (item *)malloc(1 * sizeof(item));
    item it = {a, a, getRest(a)};
    zbior_ary z;

    sets[0] = it;
    z.sets = sets;
    z.n = 1;
    z.q = Q;
    return z;
}

unsigned ary(zbior_ary A){
    return (unsigned)A.n;
}

// if they has common q, [1,3] == [5,7] is common, [2,4] != [1,3] not common
bool isItemsCommon(item item1, item item2){
    if(Q == 1) return true;
    return item1.rest == item2.rest;
}

bool isItemValid(item item){
    return item.a <= item.b;
}

zbior_ary createZbior(long long n, long long q, item *sets){
    zbior_ary newZbior;
    newZbior.q = q;
    newZbior.n = n;
    newZbior.sets = sets;
    return newZbior;
}

bool isItemsIntersectsWithQ(item item1, item item2){
    long long expandedA = item2.a - Q;
    long long expandedB = item2.b + Q;

    long long max_start = max(item1.a, expandedA);
    long long min_end = min(item1.b, expandedB);

    return max_start <= min_end;
}

item getItemsIntersectionWithQ(item item1, item item2){
    long long expandedA = item2.a - Q;
    long long expandedB = item2.b + Q;

    item newItem;
    newItem.a = max(item1.a, expandedA);
    newItem.b = min(item1.b, expandedB);
    newItem.rest = item1.rest;
    return newItem;
}

bool isItemsIntersects(item item1, item item2){
    return (max(item1.a, item2.a) <= min(item1.b, item2.b));
}

bool isItemsEqual(item item1, item item2){
    return item1.a == item2.a &&
        item1.b == item2.b &&
        item1.rest == item2.rest;
}

bool isItemLower(item item1, item item2){
    if(item1.rest < item2.rest) return true;
    if(item1.rest > item2.rest) return false;
    
    if(item1.a < item2.a) return true;
    if(item1.a > item2.a) return false;
    
    if(item1.b < item2.b) return true;
    
    return false;
}

item getItemsIntersection(item item1, item item2){
    item newItem;
    newItem.a = max(item1.a, item2.a);
    newItem.b = min(item1.b, item2.b);
    newItem.rest = item1.rest;
    return newItem;
}

item getItemsSum(item item1, item item2){
    item newItem;
    newItem.a = min(item1.a, item2.a);
    newItem.b = max(item1.b, item2.b);
    newItem.rest = item1.rest;
    return newItem;
}

unsigned moc(zbior_ary A){
    unsigned long long cnt = 0;
    for (long long i = 0; i < A.n; ++i){
        item it = A.sets[i];
        if(isItemValid(it)){
            cnt += (it.b - it.a) / Q + 1;
        }
    }
    
    return (unsigned)cnt;
}

// assume that all sets are sorted
zbior_ary suma(zbior_ary A, zbior_ary B){
    long long n = A.n + B.n;
    item *newSets = (item *)malloc((unsigned)n * sizeof(item));
    long long insertIdx = 0, idxA = 0, idxB = 0;

    while (idxA < A.n && idxB < B.n){
        item itemA = A.sets[idxA];
        item itemB = B.sets[idxB];

        // if i can sum current items with prev i do this
        if (insertIdx > 0){
            item prevItem = newSets[insertIdx - 1];
            bool merged = false;

            if (isItemsCommon(prevItem, itemA) && isItemsIntersectsWithQ(prevItem, itemA)){
                newSets[insertIdx - 1] = getItemsSum(prevItem, itemA);
                idxA++;
                merged = true;
            }else if (isItemsCommon(prevItem, itemB) && isItemsIntersectsWithQ(prevItem, itemB)){
                newSets[insertIdx - 1] = getItemsSum(prevItem, itemB);
                idxB++;
                merged = true;
            }

            if (merged)
                continue;
        }

        if (isItemsCommon(itemA, itemB) && isItemsIntersectsWithQ(itemA, itemB)){
            newSets[insertIdx] = getItemsSum(itemA, itemB);
            insertIdx++;
            idxA++;
            idxB++;
            continue;
        }

        if (isItemLower(itemA, itemB)){
            newSets[insertIdx] = itemA;
            idxA++;
            insertIdx++;
        }else{
            newSets[insertIdx] = itemB;
            idxB++;
            insertIdx++;
        }
    }

    // now fill newSets with items which wasnt added
    if (idxA < A.n){ //rewrite on while
        for (long long i = idxA; i < A.n; ++i){
            item itemA = A.sets[i];
            if (insertIdx > 0){
                item prevItem = newSets[insertIdx - 1];
                if (isItemsCommon(itemA, prevItem) && isItemsIntersectsWithQ(itemA, prevItem)){
                    newSets[insertIdx - 1] = getItemsSum(itemA, prevItem);
                    continue;
                }
            }

            newSets[insertIdx] = itemA;
            insertIdx++;
        }
    }

    if (idxB < B.n){
        for (long long i = idxB; i < B.n; ++i){
            item itemB = B.sets[i];
            if (insertIdx > 0){
                item prevItem = newSets[insertIdx - 1];
                if (isItemsCommon(itemB, prevItem) && isItemsIntersectsWithQ(itemB, prevItem)){
                    newSets[insertIdx - 1] = getItemsSum(itemB, prevItem);
                    continue;
                }
            }

            newSets[insertIdx] = itemB;
            insertIdx++;
        }
    }

    if (insertIdx < n){
        item *reSets = (item *)realloc(newSets, (unsigned)insertIdx * sizeof(item));
        if (reSets != NULL)
            newSets = reSets;
    }

    return createZbior(insertIdx, Q, newSets);
}

zbior_ary roznica(zbior_ary A, zbior_ary B){
    if (A.n == 0)
        return createZbior(0, 0, NULL);

    long long n = A.n + B.n;
    long long insertIdx = 0, idxA = 0, idxB = 0;
    item *newSets = (item *)malloc((unsigned)n * sizeof(item));
    item currentA = A.sets[idxA];

    while (idxA < A.n && idxB < B.n){
        item itemB = B.sets[idxB];
        
        if(isItemsCommon(currentA, itemB)){
            item intersection = getItemsIntersection(currentA, itemB);
            if(!isItemValid(intersection)){ // if intersection dosnt exist
                if(isItemLower(currentA, itemB)){ // default sdvig looks terrible
                    newSets[insertIdx] = currentA;
                    insertIdx++;
                    idxA++;
                    if(idxA < A.n) currentA = A.sets[idxA];
                }else{
                    idxB++;
                }
                continue;
            }

            //if intersection exists
            item leftDiff = {currentA.a, intersection.a - Q, currentA.rest}; //trying to get right part of currentA 
            if(isItemValid(leftDiff)){                     
                newSets[insertIdx] = leftDiff;
                insertIdx++;
            }
            
            currentA.a = intersection.b + Q;
            if(!isItemValid(currentA)){ // check isRight part of currentA exists, if not get another currentA
                //printf("fa");
                idxA++;
                if(idxA < A.n)
                    currentA = A.sets[idxA];
                continue;
            }
        }

        if(isItemLower(currentA, itemB)){
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
        for (long long i = idxA; i < A.n; ++i){
            newSets[insertIdx] = A.sets[i];
            insertIdx++;
        }
    }

    // if result is empty item
    if (insertIdx == 0)
        return createZbior(0, 0, NULL);
    
    if (insertIdx < n){
        item *reSets = (item *)realloc(newSets, (unsigned)insertIdx * sizeof(item));
        if (reSets != NULL)
            newSets = reSets;
    }

    return createZbior(insertIdx, Q, newSets);
}

zbior_ary iloczyn(zbior_ary A, zbior_ary B){
    if(A.n == 0 || B.n == 0)
        return createZbior(0, Q, NULL);
        
    long long n = A.n + B.n;
    item *newSets = (item *)malloc((unsigned)n * sizeof(item));
    long long insertIdx = 0, idxA = 0, idxB = 0;

    while (idxA < A.n && idxB < B.n){
        item itemA = A.sets[idxA];
        item itemB = B.sets[idxB];
        
        if(isItemsCommon(itemA, itemB)){
            // Mają ten sam rest - znajdź przecięcie
            item intersection = getItemsIntersection(itemA, itemB);
            if(isItemValid(intersection)){
                newSets[insertIdx] = intersection;
                insertIdx++;
            }
            
            if(itemA.b < itemB.b)
                idxA++;
            else
                idxB++;
            
        } else {
            if(itemA.rest < itemB.rest){
                idxA++;
            } else {
                idxB++;
            }
        }
    }

    if (insertIdx == 0)
        return createZbior(0, Q, NULL);

    if (insertIdx < n){
        item *reSets = (item *)realloc(newSets, (unsigned)insertIdx * sizeof(item));
        if (reSets != NULL)
            newSets = reSets;
    }

    return createZbior(insertIdx, Q, newSets);
}

bool nalezy(zbior_ary A, int b){
    if (A.n == 0)
        return false;

    item itemB = {b, b, getRest(b)};
    long long l = 0, r = A.n - 1;

    while (l <= r){
        long long mid = l + (r - l) / 2;
        item midItem = A.sets[mid];

        if (isElementInItem(midItem, b)){
            return true;
        }

        if (isItemLower(itemB, midItem)){
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return false;
}
