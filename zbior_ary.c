#include <stdlib.h>
#include <stdio.h>
#include "zbior_ary.h"
#include <math.h>

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
    item i = {a, 0};

    zbior_ary z;
    z.n = 1;
    return z;
}

void delete(zbior_ary *A){
    free(A.sets);
    free(A);
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
    printf("%d", cnt);
    return (unsigned)cnt;
}

unsigned ary(zbior_ary A){
    return (unsigned)A.n;
}

bool nalezy(zbior_ary A, int b){
    
    for(int i = 0; i < A.n; ++i){

    }

    return false;
}