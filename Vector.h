#ifndef VECTOR
#define VECTOR
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef struct Vector{
        void *arr;
        unsigned int len;
        unsigned int cap;
        size_t itemSize;
    }Vector;
    
    void VECTOR_init(Vector **v ,size_t itemSize);
    void *VECTOR_get_item(Vector *v, unsigned int pos);
    void VECTOR_change_item(Vector *v, void *newItem, unsigned int pos);
    int VECTOR_push_back(Vector *v, void *newItem);
    int VECTOR_push_front(Vector *v, void *newItem);
    void VECTOR_remove_item(Vector*v, unsigned int pos);
    void VECTOR_switch(Vector *v, unsigned int pos1, unsigned int pos2);
    void VECTOR_free(Vector **v);

#endif