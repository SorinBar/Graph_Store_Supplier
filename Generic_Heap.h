#ifndef GENERIC_HEAP
#define GENERIC_HEAP
    #include "Vector.h"

    typedef struct Heap{
        Vector *vect;
    }Heap;

    typedef int(*compare)(void*, void*);

    void HEAP_init(Heap **heap, size_t itemSize);
    int HEAP_insert(Heap *heap, void *item, compare cmp);
    void HEAP_remove_root(Heap *heap, compare cmp);
    void HEAP_free(Heap **heap);

#endif