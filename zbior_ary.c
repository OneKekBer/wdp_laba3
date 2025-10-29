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

void delete(zbior_ary A){
    free(A.sets);
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

bool nalezy(zbior_ary A, int b){
    
    for(int i = 0; i < A.n; ++i){

    }

    return false;
}

zbior_ary suma(zbior_ary A, zbior_ary B){
    zbior_ary new_zbior;
    // i need to check on equal items
    new_zbior.n = zbior_ary.A + zbior_ary.B;
    item *sets = malloc(unsigned(new_zbior.n) * sizeof(item));
    
    for(int i = 0; i < new_zbior.n; ++i){
        
    }

    reutrn new_zbior;
}