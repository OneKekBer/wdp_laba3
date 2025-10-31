#include <stdlib.h>
#include <stdio.h>
#include "zbior_ary.h"
#include <math.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

zbior_ary ciag_arytmetyczny(int a, int q, int b){
    item *sets = malloc(sizeof(item));
    item i = {a, b};
    zbior_ary z;
    
    sets[0] = i;
    z.Q = q;
    z.n = 1;

    z.sets = sets;
    return z;
}

zbior_ary singleton(int a){
    item *sets = malloc(sizeof(item));
    item it = {a, 0};
    sets[0] = it;
    zbior_ary z;
    z.sets = sets;
    z.n = 1;
    z.Q = 0;
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

        cnt += (val.b - val.a) / A.Q + 1;
    } 

    return (unsigned)cnt;
}

unsigned ary(zbior_ary A){
    return (unsigned)A.n;
}

// bool nalezy(zbior_ary A, int b){
    
//     for(int i = 0; i < A.n; ++i){

//     }

//     return false;
// }

//if they has common q, [1,3] == [5,7] is common, [2,4] != [1,3] not common
bool isItemsCommon(item item1, item item2, int q){
    return (abs(item1.a - item2.a) % q == 0) && (abs(item1.b - item2.b) % q == 0);
}

bool isItemsIntersects(item item1, item item2) {
    if(item2.b == 0 && item1.b == 0) return item1.a == item2.a;
    if(item2.b == 0){
        return item2.a >= item1.a && item2.a <= item1.b;
    }if(item1.b == 0){
        return item1.a >= item2.a && item1.a <= item2.b;
    }else return (item1.a <= item2.b) && (item2.a <= item1.b);
}

item getItemsSum(item item1, item item2){
    item newItem;
    newItem.a = min(item1.a, item2.a);
    newItem.b = max(item1.b, item2.b);
    return newItem;
}

zbior_ary suma(zbior_ary A, zbior_ary B){
    int n = A.n + B.n;
    item *cSets = malloc((unsigned)n * sizeof(item));
    int insertIndex = 0, idxA = 0, idxB = 0;

    //W: dont forget bout singletons!!
    //idea: i have two pointers that check every item if they have common part
    while(idxA < A.n && idxB < B.n ){ 
        item itemA = A.sets[idxA];
        item itemB = B.sets[idxB];
        
        if(isItemsIntersects(itemA, itemB) && isItemsCommon(itemA, itemB, max(A.Q, B.Q))){
            item newItem = getItemsSum(itemA, itemB);        
            cSets[insertIndex] = newItem;
            idxA++;
            idxB++;
            insertIndex++;
            continue;
        }

        if(itemA.a > itemB.a){ // W: code repeating make smth with that!!
            cSets[insertIndex] = itemB;
            insertIndex++;
            idxB++;
            continue;
        }
        if(itemA.a < itemB.a){
            cSets[insertIndex] = itemA;
            insertIndex++;
            idxA++;
            continue;    
        }

        cSets[insertIndex] = itemA;
        cSets[++insertIndex] = itemB;
        idxA++;
        idxB++;
    }

    printf("idxA: %d, A.n: %d\n", idxA, A.n);
    if(idxA < A.n){
        for(int i = idxA; i < A.n; ++i){
            cSets[insertIndex] = A.sets[i];
            insertIndex++;
        }
    }
    printf("idxB: %d, B.n: %d\n", idxB, B.n);
    if(idxB < B.n){
        for(int i = idxB; i < B.n; ++i){
            printf("a:%d b:%d ", B.sets[i].a, B.sets[i].b);
            cSets[insertIndex] = B.sets[i];
            insertIndex++;
        }
    }

    // if(insertIndex < n){
    //     cSets = realloc(cSets, (unsigned)insertIndex * sizeof(item));
    // }

    zbior_ary C;
    C.n = insertIndex;
    C.sets = cSets;
    return C;
}