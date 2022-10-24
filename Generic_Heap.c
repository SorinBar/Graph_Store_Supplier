#include "Generic_Heap.h"

// Initiaize heap
void HEAP_init(Heap **heap, size_t itemSize){
    *heap = (Heap*)malloc(sizeof(Heap));
    VECTOR_init(&((*heap)->vect), itemSize);
}
// Insert node in heap
int HEAP_insert(Heap *heap, void *item, compare cmp){
    if(VECTOR_push_back(heap->vect, item) == -1)
        return -1;
    unsigned int currentPos = heap->vect->len - 1;
    unsigned int parentPos;
    void *current, *parent;
    while(currentPos){
        parentPos = (currentPos - 1) / 2;
        current = VECTOR_get_item(heap->vect, currentPos);
        parent = VECTOR_get_item(heap->vect, parentPos);
        if(cmp(current, parent) > 0){
            VECTOR_switch(heap->vect, currentPos, parentPos);
            currentPos = parentPos;
        }
        else
            break;
    }
    return 0;
}
// If only the root is misplaced it will correct the heap
void HEAP_heapify(Heap *heap, compare cmp){
    unsigned int currentPos = 0;
    unsigned int leftPos, rightPos;
    void *current, *left, *right;
    while(1){
        leftPos = 2 * currentPos + 1;
        rightPos = 2 * currentPos + 2;
        if(rightPos >= heap->vect->len)
            break;
        current = VECTOR_get_item(heap->vect, currentPos);
        left = VECTOR_get_item(heap->vect, leftPos);
        right = VECTOR_get_item(heap->vect, rightPos);
        if(cmp(left, right) > 0){
            if(cmp(left, current) > 0){
                VECTOR_switch(heap->vect, leftPos, currentPos);
                currentPos = leftPos;
            }
            else
                break;
        }
        else{
            if(cmp(right, current) > 0){
                VECTOR_switch(heap->vect, rightPos, currentPos);
                currentPos = rightPos;
            }
            else
                break;
        }
        
    }
    leftPos = 2 * currentPos + 1;
    current = VECTOR_get_item(heap->vect, currentPos);
    left = VECTOR_get_item(heap->vect, leftPos);
    if(leftPos < heap->vect->len && cmp(left, current) > 0)
        VECTOR_switch(heap->vect, leftPos, currentPos);
}
// Remove heap root node
void HEAP_remove_root(Heap *heap, compare cmp){
    // Switch root with last node
    VECTOR_switch(heap->vect, 0, heap->vect->len - 1);
    // Remove last node
    VECTOR_remove_item(heap->vect, heap->vect->len - 1);
    // Heapify
    HEAP_heapify(heap, cmp);
}
// Free heap allocated memory
void HEAP_free(Heap **heap){
    VECTOR_free(&((*heap)->vect));
    free(*heap);
    *heap = NULL;
}