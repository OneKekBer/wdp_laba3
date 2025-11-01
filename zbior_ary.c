#include <stdlib.h>
#include <stdio.h>
#include "zbior_ary.h"
#include <math.h>
#include <assert.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int Q = 0;

zbior_ary ciag_arytmetyczny(int a, int q, int b){
    if(Q == 0) Q = q;

    item *sets = malloc(sizeof(item));
    item i = {a, b};
    zbior_ary z;
    
    sets[0] = i;
    z.n = 1;
    z.sets = sets;
    return z;
}

zbior_ary singleton(int a){
    item *sets = malloc(sizeof(item));
    item it = {a, 0};
    zbior_ary z;
    
    sets[0] = it;
    z.sets = sets;
    z.n = 1;
    return z;
}

unsigned moc(zbior_ary A){
    int cnt = 0;
    for(int i = 0; i < A.n; ++i){
        item val = A.sets[i];
        if(val.b == 0){
            cnt++;
            continue;
        }

        cnt += (val.b - val.a) / Q + 1;
    } 

    return (unsigned)cnt;
}

unsigned ary(zbior_ary A){
    return (unsigned)A.n;
}

void print_item1(item i) {
    printf("item");
    if (i.b == 0) printf("{%d}", i.a);
    else printf("[%d,%d]", i.a, i.b);
    printf("\n");

}


//if they has common q, [1,3] == [5,7] is common, [2,4] != [1,3] not common
bool isItemsCommon(item item1, item item2, int q){
    if(q == 1) return true;
    return (abs(item1.a - item2.a) % q == 0) && (abs(item1.b - item2.b) % q == 0);
}

bool isItemsIntersects(item item1, item item2) {
    if(item2.b == 0 && item1.b == 0) return item1.a == item2.a;
    if(item2.b == 0){
        return item2.a >= item1.a && item2.a <= item1.b;
    }if(item1.b == 0){
        return item1.a >= item2.a && item1.a <= item2.b;
    }else{
        // printf("norm\n");
        return (item1.a <= item2.b) && (item2.a <= item1.b);
    } 
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
    item *cSets = malloc((unsigned)n * sizeof(item));
    int insertIdx = 0, idxA = 0, idxB = 0;

    while(idxA < A.n || idxB < B.n){
        if(idxA >= A.n || idxB >= B.n) break;
        item itemA = A.sets[idxA]; // W: can be dangerous
        item itemB = B.sets[idxB];
        
        if(insertIdx > 0){
            item prevItem = insertIdx > 0 ? cSets[insertIdx - 1] : (item){0, 0};
            bool merged = false;

            if(isItemsCommon(prevItem, itemA, Q) && isItemsIntersects(prevItem, itemA)){
                cSets[insertIdx - 1] = getItemsSum(prevItem, itemA);
                idxA++;
                merged = true;
            }

            if(isItemsCommon(prevItem, itemB, Q) && isItemsIntersects(prevItem, itemB)){
                cSets[insertIdx - 1] = getItemsSum(prevItem, itemB);
                idxB++;
                merged = true;
            }            

            if(merged) continue;
        }   
        // print_item1(itemA);
        // print_item1(itemB);
        // printf("%d", Q);
        if(isItemsCommon(itemA, itemB, Q) && isItemsIntersects(itemA, itemB)){
            // printf("common rabotaet");
            cSets[insertIdx] = getItemsSum(itemA, itemB); 
            insertIdx++;
            idxA++;
            idxB++;
            continue;
        }

        if(itemA.a < itemB.a){
            cSets[insertIdx] = itemA;
            idxA++;
            insertIdx++;
        }
        else{
            cSets[insertIdx] = itemB;
            idxB++;
            insertIdx++;
        } 
    }

    //now fill cSets with items which wasnt added
    if(idxA < A.n){
        for(int i = idxA; i < A.n; ++i){
            item itemA = A.sets[i];

            if(insertIdx > 0){
                item prevItem = cSets[insertIdx - 1];

                if(isItemsCommon(itemA, prevItem, Q) && isItemsIntersects(itemA, prevItem)){
                    cSets[insertIdx - 1] = getItemsSum(itemA, prevItem);        
                    continue;
                }
            }   

            cSets[insertIdx] = itemA;
            insertIdx++;
        }
    }
    
    if(idxB < B.n){
        for(int i = idxB; i < B.n; ++i){
            item itemB = B.sets[i];

            if(insertIdx > 0){
                item prevItem = cSets[insertIdx - 1];

                if(isItemsCommon(itemB, prevItem, Q) && isItemsIntersects(itemB, prevItem)){
                    cSets[insertIdx - 1] = getItemsSum(itemB, prevItem);        
                    continue;
                }
            }   

            cSets[insertIdx] = itemB;
            insertIdx++;
        }
    }
   
    if(insertIdx < n){
        item *reSets = realloc(cSets, (unsigned)insertIdx * sizeof(item));
        if(reSets != NULL) cSets = reSets;
    }
   
    zbior_ary newZbior;
    newZbior.n = insertIdx;
    newZbior.sets = cSets;
    return newZbior;
}

zbior_ary iloczyn(zbior_ary A, zbior_ary B){
    int n = max(A.n, B.n);
    item *newSets = malloc((unsigned)n * sizeof(item));
    int insertIdx = 0, idxA = 0, idxB = 0;

    while(idxA < A.n || idxB < B.n){
        if(idxA >= A.n || idxB >= B.n) break;
        item itemA = A.sets[idxA]; // W: can be dangerous
        item itemB = B.sets[idxB];

        if(isItemsCommon(itemA, itemB, Q) && isItemsIntersects(itemA, itemB)){
            newSets[insertIdx] = getItemsIntersection(itemA, itemB);
            insertIdx++;
        }
        
        if(itemA.a < itemB.a) idxA++;
        else idxB++;    
    }

    zbior_ary newZbior;
    newZbior.n = insertIdx;
    newZbior.sets = newSets;
    return newZbior;

}

//find info bout b > 0 ? or not
bool nalezy(zbior_ary A, int b){
    int l = 0, r = A.n - 1;   
    
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        item midItem = A.sets[mid];
        
        if(midItem.a == b || midItem.b == b) return true;
        if(b >= midItem.a && b <= midItem.b && isItemsCommon(midItem, (item){b, 0}, Q)) return true;

        if(midItem.b == 0){
            if(midItem.a > b){
                r = mid;
            }else{
                l = mid + 1;
            }
            continue;
        }

        if(midItem.b < b){
            l = mid + 1;
        }else{
            r = mid;
        } 
    }

    return false;
}