#ifndef WGRAPH
#define WGRAPH

    #include "Gen_Utility.h"
    #include "Generic_Heap.h"

    #define INF 1000000

    typedef struct Node{
        int val;
        float weight;
        struct Node* next;
    }Node;
    typedef struct WGraph{
        int nr_nodes;
        struct Node** neighbours;
    }WGraph;
    typedef struct DijNode{
        int node;
        float weight;
    }DijNode;

    void WGRAPH_init(WGraph **myGraph, int nr_nodes);
    int WGRAPH_add_link(WGraph *myGraph, int src, int dest, float weight);
    void WGRAPH_print_links(WGraph *myGraph);
    float **WGRAPH_Roy_Floyd(WGraph *myGraph);
    int cmp(void *x, void *y);
    float *WGRAPH_Dijkstra(WGraph *myGraph, int src);
    int *WGRAPH_topsort(WGraph *myGraph);
    WGraph *WGRAPH_transpose(WGraph *myGraph);

    void WGRAPH_free(WGraph **myGraph);

#endif