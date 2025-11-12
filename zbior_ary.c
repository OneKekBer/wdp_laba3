#include <stdlib.h>
#include <stdio.h>
#include "zbior_ary.h"
#include <math.h>
#include <assert.h>
//#include "../tests/print.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

long long Q = 0;

zbior_ary ciag_arytmetyczny(long long a, long long q, long long b)
{
    if (Q == 0)
        Q = q;

    item *sets = (item *)malloc(sizeof(item));
    item i = {a, b};
    zbior_ary z;

    sets[0] = i;
    z.n = 1;
    z.q = q;
    z.sets = sets;
    return z;
}

zbior_ary singleton(long long a)
{
    item *sets = (item *)malloc(1 * sizeof(item));
    item it = {a, a};
    zbior_ary z;

    sets[0] = it;
    z.sets = sets;
    z.n = 1;
    z.q = Q;
    return z;
}

unsigned ary(zbior_ary A)
{
    return (unsigned)A.n;
}

// if they has common q, [1,3] == [5,7] is common, [2,4] != [1,3] not common
bool isItemsCommon(item item1, item item2, long long q)
{
    if (q == 1)
        return true;
    return (llabs(item1.a - item2.a) % q == 0) && (llabs(item1.b - item2.b) % q == 0);
}


bool isItemValid(item item)
{
    return item.a <= item.b;
}

zbior_ary createZbior(long long n, long long q, item *sets)
{
    zbior_ary newZbior;
    newZbior.q = q;
    newZbior.n = n;
    newZbior.sets = sets;
    return newZbior;
}

bool isEmptyZbior(zbior_ary A)
{
    return A.sets == NULL;
}

bool isItemsIntersectsWithQ(item item1, item item2)
{
    long long expandedA = item2.a - Q;
    long long expandedB = item2.b + Q;

    long long max_start = max(item1.a, expandedA);
    long long min_end = min(item1.b, expandedB);

    return max_start <= min_end;
}

item getItemsIntersectionWithQ(item item1, item item2)
{
    long long expandedA = item2.a - Q;
    long long expandedB = item2.b + Q;

    item newItem;
    newItem.a = max(item1.a, expandedA);
    newItem.b = min(item1.b, expandedB);
    return newItem;
}

bool isItemsIntersects(item item1, item item2)
{
    return (max(item1.a, item2.a) <= min(item1.b, item2.b));
}

item getItemsIntersection(item item1, item item2)
{
    item newItem;
    newItem.a = max(item1.a, item2.a);
    newItem.b = min(item1.b, item2.b);
    return newItem;
}

item getItemsSum(item item1, item item2)
{
    item newItem;
    newItem.a = min(item1.a, item2.a);
    newItem.b = max(item1.b, item2.b);
    return newItem;
}

unsigned moc(zbior_ary A)
{ // maybe current item
    unsigned long long cnt = 0;
    for (long long i = 0; i < A.n; ++i)
    {
        item item = A.sets[i];
        if(isItemValid(item)){
            cnt += (item.b - item.a) / Q + 1;
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

            if (isItemsCommon(prevItem, itemA, Q) && isItemsIntersectsWithQ(prevItem, itemA))
            {
                newSets[insertIdx - 1] = getItemsSum(prevItem, itemA);
                idxA++;
                merged = true;
            }

            if (isItemsCommon(prevItem, itemB, Q) && isItemsIntersectsWithQ(prevItem, itemB))
            {
                newSets[insertIdx - 1] = getItemsSum(prevItem, itemB);
                idxB++;
                merged = true;
            }

            if (merged)
                continue;
        }

        if (isItemsCommon(itemA, itemB, Q) && isItemsIntersectsWithQ(itemA, itemB)){
            newSets[insertIdx] = getItemsSum(itemA, itemB);
            insertIdx++;
            idxA++;
            idxB++;
            continue;
        }

        if (itemA.a < itemB.a)
        {
            newSets[insertIdx] = itemA;
            idxA++;
            insertIdx++;
        }
        else
        {
            newSets[insertIdx] = itemB;
            idxB++;
            insertIdx++;
        }
    }

    // now fill newSets with items which wasnt added
    if (idxA < A.n)
    {
        for (long long i = idxA; i < A.n; ++i)
        {
            item itemA = A.sets[i];
            if (insertIdx > 0)
            {
                item prevItem = newSets[insertIdx - 1];

                if (isItemsCommon(itemA, prevItem, Q) && isItemsIntersectsWithQ(itemA, prevItem))
                {
                    newSets[insertIdx - 1] = getItemsSum(itemA, prevItem);
                    continue;
                }
            }

            newSets[insertIdx] = itemA;
            insertIdx++;
        }
    }

    if (idxB < B.n)
    {
        for (long long i = idxB; i < B.n; ++i)
        {
            item itemB = B.sets[i];
            if (insertIdx > 0)
            {
                item prevItem = newSets[insertIdx - 1];

                if (isItemsCommon(itemB, prevItem, Q) && isItemsIntersectsWithQ(itemB, prevItem))
                {
                    newSets[insertIdx - 1] = getItemsSum(itemB, prevItem);
                    continue;
                }
            }

            newSets[insertIdx] = itemB;
            insertIdx++;
        }
    }

    if (insertIdx < n)
    {
        item *reSets = (item *)realloc(newSets, (unsigned)insertIdx * sizeof(item));
        if (reSets != NULL)
            newSets = reSets;
    }

    return createZbior(insertIdx, max(A.q, max(B.q, Q)), newSets);
}

zbior_ary roznica(zbior_ary A, zbior_ary B){
    if (B.n == 0)
        return A;
    if (A.n == 0)
        return createZbior(0, 0, NULL);

    long long n = A.n + B.n;
    long long insertIdx = 0, idxA = 0, idxB = 0;
    item *newSets = (item *)malloc((unsigned)n * sizeof(item));
    item currentA = A.sets[idxA];

    while (idxA < A.n && idxB < B.n){
        item itemB = B.sets[idxB];

        if (isItemsIntersects(currentA, itemB)){
            if (isItemsCommon(currentA, itemB, Q)){
                bool merged = false;

                if (currentA.a <= itemB.a - Q){
                    item leftDiff;
                    leftDiff.a = currentA.a;
                    leftDiff.b = itemB.a - Q;

                    currentA.a = itemB.b + Q;
                    newSets[insertIdx] = leftDiff;
                    insertIdx++;
                    merged = true;
                }

                if (currentA.b >= itemB.b + Q){
                    merged = true;
                    currentA.a = itemB.b + Q;
                }

                if (!merged){
                    idxA++;
                    if (idxA < A.n)
                    {
                        currentA = A.sets[idxA];
                        continue;
                    }
                }
                else{
                    idxB++;
                    continue;
                }
            }
            else{
                if (currentA.a < itemB.a){
                    newSets[insertIdx] = currentA;
                    currentA = A.sets[idxA + 1];
                    insertIdx++;
                    idxA++;
                    continue;
                }

                idxB++;
            }
        }
        else{
            if (itemB.b < currentA.a){
                idxB++;
            }
            else{
                newSets[insertIdx] = currentA;
                insertIdx++;
                idxA++;
                if (idxA < A.n)
                    currentA = A.sets[idxA];
            }
        }
    }

    if (idxA < A.n)
    {
        newSets[insertIdx] = currentA;
        insertIdx++;
        idxA++;
        for (long long i = idxA; i < A.n; ++i)
        {
            newSets[insertIdx] = A.sets[i];
            insertIdx++;
        }
    }

    // if result is empty item
    if (insertIdx == 0)
        return createZbior(0, 0, NULL);
    

    if (insertIdx < n)
    {
        item *reSets = (item *)realloc(newSets, insertIdx * sizeof(item));
        if (reSets != NULL)
            newSets = reSets;
    }

    return createZbior(insertIdx, Q, newSets);
}

zbior_ary iloczyn(zbior_ary A, zbior_ary B){
    if(A.n == 0 || B.n == 0) return createZbior(0, 0, NULL);
    int n = max(A.n, B.n);
    item *newSets = (item *)malloc((unsigned)n * sizeof(item));
    int insertIdx = 0, idxA = 0, idxB = 0;

    while (idxA < A.n && idxB < B.n)
    {
        item itemA = A.sets[idxA];
        item itemB = B.sets[idxB];

        if (isItemsIntersects(itemA, itemB)){
            if (isItemsCommon(itemA, itemB, Q)){
                item intersection = getItemsIntersection(itemA, itemB);
                if (isItemValid(intersection))
                {
                    newSets[insertIdx] = intersection;
                    insertIdx++;
                }

                if (itemA.b < itemB.b)
                    idxA++;
                else if (itemB.b < itemA.b)
                    idxB++;
                else{
                    idxA++;
                    idxB++;
                }
            }else{
                if (itemA.a < itemB.a){
                    idxA++;
                }
                else if (itemB.a < itemA.a){
                    idxB++;
                }
                else{
                    idxA++;
                    idxB++;
                }
            }
        }
        else if (itemA.b < itemB.a){
            idxA++;
        }
        else{
            idxB++;
        }
    }

    if (insertIdx < n){
        item *reSets = (item *)realloc(newSets, (unsigned)insertIdx * sizeof(item));
        if (reSets != NULL)
            newSets = reSets;
    }

    return createZbior(insertIdx, max(A.q, max(B.q, Q)), newSets);
}

bool nalezy(zbior_ary A, long long b){
    long long l = 0, r = A.n - 1;

    while (l <= r)
    {
        long long mid = l + (r - l) / 2;
        item midItem = A.sets[mid];

        if (midItem.b == 0 && midItem.a >= 0)
        {
            if (midItem.a == b)
                return true;
            if (b < midItem.a)
                r = mid - 1;
            else
                l = mid + 1;
            continue;
        }

        // check if element b in range of [a,b]
        if (b >= midItem.a && b <= midItem.b)
        {
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