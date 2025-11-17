#include <stdlib.h>
#include <stdio.h>
#include "zbior_ary.h"
#include <math.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

long long Q = 0;

//i want this function)
// this func computes rest
// for negative numbers, it adds q to get a positive rest
// for exmpl getRest(-3) with q = 5 return 2 (instead of -3)
// its better to work with positive rests
long getRest(long long a){
    long long r = a % Q;
    if (r < 0) r += Q;
    return r;
}

bool isElementInItem(item it, long long x){
    return (x >= it.a && x <= it.b) && (x - it.a) % Q == 0;
}

zbior_ary ciag_arytmetyczny(int a, int q, int b){
    if (Q == 0) Q = q; // define global q
    item *sets = (item *)malloc(sizeof(item));
    item it = {a, b, getRest(a)};
    sets[0] = it;
    zbior_ary z;

    z.n = 1;
    z.q = Q;
    z.sets = sets;
    
    return z;
}

zbior_ary singleton(int a){
    item *sets = (item *)malloc(1 * sizeof(item));
    item it = {a, a, getRest(a)};
    sets[0] = it;
    zbior_ary z;

    z.n = 1;
    z.q = Q;
    z.sets = sets;

    return z;
}

unsigned ary(zbior_ary A){
    return (unsigned)A.n;
}

// if they has common rest, for q = 2, [1,3] == [5,7] is common, [2,4] != [1,3] not common
bool isItemsCommon(item item1, item item2){
    if(Q == 1) return true;
    return item1.rest == item2.rest;
}

bool isItemValid(item it){
    return it.a <= it.b;
}

zbior_ary createZbior(long long n, long long q, item *sets){
    zbior_ary newZbior;
    newZbior.q = q;
    newZbior.n = n;
    newZbior.sets = sets;
    return newZbior;
}

// extend range of this items with q, for searching progression of items
bool isItemsIntersectsWithQ(item item1, item item2){
    long long max_start = max(item1.a, item2.a - Q);
    long long min_end = min(item1.b, item2.b + Q);

    return max_start <= min_end;
}

//extended range but return intersection
item getItemsIntersectionWithQ(item item1, item item2){
    item newItem;
    newItem.a = max(item1.a, item2.a - Q);
    newItem.b = min(item1.b, item2.b + Q);
    newItem.rest = item1.rest;
    return newItem;
}

//Function that compares two items
//firstly on rests, then a then b
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
            cnt += (long long unsigned)((it.b - it.a) / Q + 1);
        }
    }
    
    return (unsigned)cnt;
}

zbior_ary suma(zbior_ary A, zbior_ary B){
    long long n = A.n + B.n;
    item *newSets = (item *)malloc((unsigned)n * sizeof(item));
    long long insertIdx = 0, idxA = 0, idxB = 0;

    while (idxA < A.n && idxB < B.n){
        item itemA = A.sets[idxA];
        item itemB = B.sets[idxB];

        // check if i can sum current items with prev items
        bool isJoined = false;
        if (insertIdx > 0){
            item prevItem = newSets[insertIdx - 1];

            if (isItemsCommon(prevItem, itemA) && isItemsIntersectsWithQ(prevItem, itemA)){
                newSets[insertIdx - 1] = getItemsSum(prevItem, itemA);
                idxA++;
                isJoined = true;
            }else if (isItemsCommon(prevItem, itemB) && isItemsIntersectsWithQ(prevItem, itemB)){
                newSets[insertIdx - 1] = getItemsSum(prevItem, itemB);
                idxB++;
                isJoined = true;
            }
        }

        //if we dont sum prev i current items then try to sum a and b
        if(!isJoined){
            if (isItemsCommon(itemA, itemB) && isItemsIntersectsWithQ(itemA, itemB)){
                newSets[insertIdx] = getItemsSum(itemA, itemB);
                insertIdx++;
                idxA++;
                idxB++;
            }else if (isItemLower(itemA, itemB)){ // if we cant sum it we move pointer
                newSets[insertIdx] = itemA;       // if a lower than b, move idxA else move idxB 
                idxA++;
                insertIdx++;
            }else{
                newSets[insertIdx] = itemB;
                idxB++;
                insertIdx++;
            }
        }
    }

    // now fill newSets with items which wasn`t added
    for (long long i = idxA; i < A.n; ++i){
        bool isJoined = false;
        item itemA = A.sets[i];
        if (insertIdx > 0){
            item prevItem = newSets[insertIdx - 1];
            if (isItemsCommon(itemA, prevItem) && isItemsIntersectsWithQ(itemA, prevItem)){
                newSets[insertIdx - 1] = getItemsSum(itemA, prevItem);
                isJoined = true;
            }
        }

        if(!isJoined){
            newSets[insertIdx] = itemA;
            insertIdx++;
        }
    }
    
    for(long long i = idxB; i < B.n; ++i){
        bool isJoined = false;
        item itemB = B.sets[i];
        if (insertIdx > 0){
            item prevItem = newSets[insertIdx - 1];
            if (isItemsCommon(itemB, prevItem) && isItemsIntersectsWithQ(itemB, prevItem)){
                newSets[insertIdx - 1] = getItemsSum(itemB, prevItem);
                isJoined = true;
            }
        }

        if(!isJoined){
            newSets[insertIdx] = itemB;
            insertIdx++;
        }
    }
    
    //check can i decrease size of my newSets array
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
        //i need to control when i have invalid items
        //if i have invalid items then i need to move my currentA or itemB and
        //i cant be sure is idxA < A.n or idxB < B.n
        bool isValid = true;
        item itemB = B.sets[idxB];        
        if(isItemsCommon(currentA, itemB)){
            item intersection = getItemsIntersection(currentA, itemB);

            if(!isItemValid(intersection)){ // if intersection doesn`t exist then i change idxs
                if(isItemLower(currentA, itemB)){ // default idxs moving
                    newSets[insertIdx] = currentA;
                    insertIdx++;
                    idxA++;
                    if(idxA < A.n) currentA = A.sets[idxA];
                }else{
                    idxB++;
                }
                isValid = false;
            }else { // if intersection exists
                item leftDiff = {currentA.a, intersection.a - Q, currentA.rest}; 
                if(isItemValid(leftDiff)){                     
                    newSets[insertIdx] = leftDiff;
                    insertIdx++;
                }
                
                //trying to get right part of currentA 
                currentA.a = intersection.b + Q;
                if(!isItemValid(currentA)){ // check isRight part of currentA exists, if not get another currentA
                    idxA++;
                    if(idxA < A.n) currentA = A.sets[idxA];
                    isValid = false;
                }
            }
        }

        // If there were no invalid items in this iteration,
        // then I can freely move the items.
        if(isValid){
            if(isItemLower(currentA, itemB)){
                newSets[insertIdx] = currentA;
                insertIdx++;
                idxA++;
                if(idxA < A.n) currentA = A.sets[idxA];
            }else{
                idxB++;
            }
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
            //trying to get intersection
            item intersection = getItemsIntersection(itemA, itemB);
            if(isItemValid(intersection)){
                //if intersection valid add
                newSets[insertIdx] = intersection;
                insertIdx++;
            }

            // we already knows that rests are the same 
            // and we need to check which item ends faster and move this item
            // for example [-15, 5] and [-20, 100], we have a 
            //chance that itemB will intersect next item  
            if(itemA.b < itemB.b){
                idxA++;
            } else{
                idxB++;
            }
        } else {
            //simple comparing of two items and moving idxs
            if(isItemLower(itemA, itemB)){
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

    item itemB = {b, b, getRest(b)}; //create singleton b
    long long l = 0, r = A.n - 1;

    while (l <= r){
        long long mid = l + (r - l) / 2;
        item midItem = A.sets[mid];

        if (isElementInItem(midItem, b)){
            return true;
        }

        if (isItemLower(itemB, midItem)){ //if i already have function that
                                          // compare items i can use it but with singleton b
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return false;
}
