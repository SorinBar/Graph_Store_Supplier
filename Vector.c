#include "Vector.h"
// Initialize vector
void VECTOR_init(Vector **v ,size_t itemSize){
    (*v) = (Vector*)malloc(sizeof(Vector));
    (*v)->arr = malloc(4 * itemSize);
    (*v)->cap = 4;
    (*v)->len = 0;
    (*v)->itemSize = itemSize;
}
// Double the vector capacity
int VECTOR_double_cap(Vector *v){
    v->arr = realloc(v->arr, v->cap * 2 * v->itemSize);
    v->cap *= 2;
    if(v->arr == NULL)
        return -1;
    return 0;
}
// Return adress of item at given position
void *VECTOR_get_item(Vector *v, unsigned int pos){
    if(pos >= v->cap)
        return NULL;
    char *arr = v->arr;
    return arr + pos * v->itemSize;
}
// Change item at given position
void VECTOR_change_item(Vector *v, void *newItem, unsigned int pos){
    void *oldItem = VECTOR_get_item(v, pos);
    if(oldItem == NULL)
        return;
    memcpy(oldItem, newItem, v->itemSize);
}
// Add item to the end of the array
int VECTOR_push_back(Vector *v, void *newItem){
    if(v->len == v->cap)
        if(VECTOR_double_cap(v) == -1)
            return -1;
    VECTOR_change_item(v, newItem, v->len);
    v->len++;
    return 0;
}
// Add item to the front of the array
int VECTOR_push_front(Vector *v, void *newItem){
    if(v->len == v->cap)
        if(VECTOR_double_cap(v) == -1)
            return -1;
    memmove(v->arr + v->itemSize, v->arr, v->len * v->itemSize);
    VECTOR_change_item(v, newItem, 0);
    v->len++;
    return 0;
}
// Remove item at given position in array
void VECTOR_remove_item(Vector*v, unsigned int pos){
    if(v->len == 0 || pos >= v->len)
        return;
    if(v->len == 1 || pos == v->len - 1){
        v->len--;
        return;
    }
    char *delItem = VECTOR_get_item(v, pos);
    memmove(delItem, delItem + v->itemSize, (v->len - pos - 1) * v->itemSize);
    v->len--;
}
// Switch items from the given positions
void VECTOR_switch(Vector *v, unsigned int pos1, unsigned int pos2){
    void *item1 = VECTOR_get_item(v, pos1);
    void *item2 = VECTOR_get_item(v, pos2);
    if(item1 == NULL || item2 == NULL)
        return;
    void *auxItem = malloc(v->itemSize);
    memcpy(auxItem, item1, v->itemSize);
    memmove(item1, item2, v->itemSize);
    memcpy(item2, auxItem, v->itemSize);
    free(auxItem);
}
// Free vector allocated memory
void VECTOR_free(Vector **v){
    free((*v)->arr);
    free(*v);
    *v = NULL;
}
