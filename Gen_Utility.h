#ifndef GEN_UTILITY
#define GEN_UTILITY
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <inttypes.h>
    
    /* Generic */
    // Swap
    #define swap(a, b) { __typeof__ (a) _SWAP = (a); (a) = (b); (b) = _SWAP; }
    // Min
    #define min(a,b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
    // Max
    #define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
    
    /* Specific */
    void swap_int(int *x, int *y);
    int min_int(int x, int y);
    int max_int(int x, int y);
    int **genMatrix_int(int lin, int col);
    void *freeMatrix_int(int **matrix, int lin);
    float **genMatrix_float(int lin, int col);
    void *freeMatrix_float(float **matrix, int lin);


#endif