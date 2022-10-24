#include "Gen_Utility.h"

// Fast int swap
void swap_int(int *x, int *y){
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}
// Fast int min
int min_int(int x, int y){
    return y ^ ((x ^ y) & -(x < y));
}
// Fast int max
int max_int(int x, int y){
    return y ^ ((x ^ y) & -(x > y));
}
// Generate int matrix
int **genMatrix_int(int lin, int col){
    int **matrix;
    int i;
    matrix = (int**)malloc(lin * sizeof(int*));
    for(i = 0; i < lin; i++)
        matrix[i] = (int*)malloc(col * sizeof(int));
    
    return matrix;
}
// Free int matrix
void *freeMatrix_int(int **matrix, int lin){
    int i;
    for(i = 0; i < lin; i++)
        free(matrix[i]);
    free(matrix);

    return NULL;
}
// Generate float matrix
float **genMatrix_float(int lin, int col){
    float **matrix;
    int i;
    matrix = (float**)malloc(lin * sizeof(float*));
    for(i = 0; i < lin; i++)
        matrix[i] = (float*)malloc(col * sizeof(float));
    
    return matrix;
}
// Free float matrix
void *freeMatrix_float(float **matrix, int lin){
    int i;
    for(i = 0; i < lin; i++)
        free(matrix[i]);
    free(matrix);

    return NULL;
}