#ifndef TASKS
#define TASKS
    #include "WGraph.h"

    typedef struct DijNodeMask{
        int node;
        float weight;
        unsigned int mask;
    }DijNodeMask;

    void task1(WGraph *myGraph, int src, int dest, float *cost);
    void task2(WGraph *myGraph, int *storage);
    float task3(WGraph *myGraph, int *storage, int src, int *destiantions);

#endif