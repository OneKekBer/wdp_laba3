#include "../zbior_ary.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

bool itemsEqual(item a, item b)
{
   return a.a == b.a && a.b == b.b;
}

int main(void)
{
   printf("=== Running item function tests ===\n\n");

   // --- getItemsSum ---
   printf("[TEST] getItemsSum\n");
   assert(itemsEqual(getItemsSum((item){1, 4}, (item){2, 5}), (item){1, 5}) && "getItemsSum merge");
   assert(itemsEqual(getItemsSum((item){1, 6}, (item){2, 5}), (item){1, 6}) && "getItemsSum merge");
   assert(itemsEqual(getItemsSum((item){2, 7}, (item){5, 9}), (item){2, 9}) && "getItemsSum overlap");
   assert(itemsEqual(getItemsSum((item){2, 0}, (item){1, 3}), (item){1, 3}) && "getItemsSum overlap");
   assert(itemsEqual(getItemsSum((item){1, 1}, (item){1, 1}), (item){1, 1}) && "getItemsSum same");
   assert(itemsEqual(getItemsSum((item){1, 6}, (item){6, 0}), (item){1, 6}) && "getItemsSum same");
   assert(!itemsEqual(getItemsSum((item){3, 0}, (item){5, 0}), (item){3, 5}) && "getItemsSum singletons");
   assert(!itemsEqual(getItemsSum((item){1, 4}, (item){2, 6}), (item){1, 5}) && "getItemsSum negative check");
   printf("✔ getItemsSum passed all tests.\n\n");

   // --- isItemsIntersects ---
   printf("[TEST] isItemsIntersects\n");
   assert(isItemsIntersects((item){1, 5}, (item){4, 10}) == true && "intersects overlap");
   assert(isItemsIntersects((item){1, 5}, (item){6, 9}) == false && "intersects disjoint");
   assert(isItemsIntersects((item){1, 5}, (item){5, 0}) == true && "intersects edge");
   assert(isItemsIntersects((item){1, 3}, (item){1, 6}) == true && "intersects edge");
   assert(isItemsIntersects((item){5, 0}, (item){1, 5}) == true && "intersects singleton-in-segment");
   assert(isItemsIntersects((item){5, 0}, (item){6, 0}) == false && "intersects two singletons no overlap");
   assert(isItemsIntersects((item){5, 0}, (item){5, 0}) == true && "intersects same singleton");
   printf("✔ isItemsIntersects passed all tests.\n\n");

   // --- isItemsCommon ---
   printf("[TEST] isItemsCommon\n");
   assert(isItemsCommon((item){2, 6}, (item){8, 12}, 2) == true && "common q=2 yes");
   assert(isItemsCommon((item){2, 6}, (item){9, 13}, 2) == false && "common q=2 no");
   assert(isItemsCommon((item){2, 12}, (item){17, 22}, 5) == true && "common q=5 yes");
   assert(isItemsCommon((item){2, 12}, (item){3, 8}, 5) == false && "common q=5 no");
   assert(isItemsCommon((item){0, 0}, (item){5, 5}, 5) == true && "common 0,0 with 5,5 q=5");
   assert(isItemsCommon((item){1, 1}, (item){6, 6}, 5) == true && "common singletons q=5");
   assert(isItemsCommon((item){1, 1}, (item){7, 7}, 5) == false && "common singletons q=5 no");
   printf("✔ isItemsCommon passed all tests.\n\n");

   // --- isItemsCommon ---
   printf("[TEST] getItemsIntersection\n");
   assert(itemsEqual(getItemsIntersection((item){3, 6}, (item){2, 4}), (item){3, 4}) && "getItemsSum merge");
   assert(itemsEqual(getItemsIntersection((item){5, 0}, (item){5, 0}), (item){5, 0}) && "getItemsSum merge");
   assert(itemsEqual(getItemsIntersection((item){1, 6}, (item){5, 0}), (item){5, 0}) && "getItemsSum merge");
   printf("✔ getItemsIntersection passed all tests.\n\n");

   printf("=== All tests passed successfully! ===\n");
   return 0;
}
