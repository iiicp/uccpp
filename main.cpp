#include <iostream>
#include "Heap.h"

int main() {

    Heap *h = Heap::sharedHeap();
    h->init();
    char *p1 = (char *)h->allocate(BLOCK_SIZE);
    printf("p1 = %p\n", p1);
    h->free();
    char *p2 = (char *)h->allocate(BLOCK_SIZE);
    printf("p2 = %p\n", p2);
    return 0;
}
