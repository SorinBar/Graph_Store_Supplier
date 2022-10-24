#include "WGraph.h"

// Initialize cost graph
void WGRAPH_init(WGraph **myGraph, int nr_nodes){
    *myGraph = (WGraph*)malloc(sizeof(WGraph));
    (*myGraph)->nr_nodes = nr_nodes;
    (*myGraph)->neighbours = (Node**)malloc((nr_nodes) * sizeof(Node*));
    int i;
    for(i = 0; i < nr_nodes; i++)
        (*myGraph)->neighbours[i] = NULL;
}
// Add link to the cost graph
int WGRAPH_add_link(WGraph *myGraph, int src, int dest, float weight){
    if(myGraph->neighbours[src] == NULL){
        myGraph->neighbours[src] = (Node*)malloc(sizeof(Node));
        if(myGraph->neighbours[src] == NULL)
            return -1;
        myGraph->neighbours[src]->val = dest;
        myGraph->neighbours[src]->weight = weight;
        myGraph->neighbours[src]->next = NULL;
        return 0;
    }
    Node *aux = myGraph->neighbours[src];
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = (Node*)malloc(sizeof(Node));
    if(aux->next == NULL)
        return -1;
    aux->next->val = dest;
    aux->next->weight = weight;
    aux->next->next = NULL;
    return 0;
}
// Print all links in the graph
void WGRAPH_print_links(WGraph *myGraph){
    Node *aux;
    int i;
    for(i = 0; i < myGraph->nr_nodes; i++){
        printf("%d-> ", i);
        aux = myGraph->neighbours[i];
        while(aux != NULL){
            printf("%d weight: %.1f\n    ", aux->val, aux->weight);
            aux = aux->next;
        }
        printf("\n");
    }
}
// Return minimum distance matrix
float **WGRAPH_Roy_Floyd(WGraph *myGraph){
    int k, i, j;
    int nr_nodes;
    float **dist;
    Node *aux;
    nr_nodes = myGraph->nr_nodes;
    // Initialize distance matrix
    dist = genMatrix_float(nr_nodes, nr_nodes);
    for(i = 0; i < nr_nodes; i++)
        for(j = 0; j < nr_nodes; j++)
            dist[i][j] = INF;
    for(i = 0; i < nr_nodes; i++)
        dist[i][i] = 0;
    for(i = 0; i < nr_nodes; i++){
        aux = myGraph->neighbours[i];
        while(aux != NULL){
            dist[i][aux->val] = aux->weight;
            aux = aux->next;
        }
    }
    // Roy-Floyd algorithm
    for(k = 0; k < nr_nodes; k++)
        for(i = 0; i < nr_nodes; i++)
            for(j = 0; j < nr_nodes; j++)
                if(dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    
    return dist;
}
// Compare function for min heap
int cmp(void *x, void *y){
    if(((DijNode*)x)->weight - ((DijNode*)y)->weight > (float)0)
        return -1;
    else
        return 1;
}
// Return minimum distance from source array
float *WGRAPH_Dijkstra(WGraph *myGraph, int src){
    Heap *myHeap;
    DijNode cItem, nItem;
    Node *aux;
    float *dist;
    int nr_nodes;
    int *vis;
    int i;
    nr_nodes = myGraph->nr_nodes;
    // Initialize visited array
    vis = (int*)malloc((nr_nodes) * sizeof(int));
    for(i = 0; i < nr_nodes; i++)
        vis[i] = 0;
    // Initialize distance array
    dist = (float*)malloc((nr_nodes) * sizeof(float));
    for(i = 0; i < nr_nodes; i++)
        dist[i] = INF;
    dist[src] = 0;
    // Initialize heap
    HEAP_init(&myHeap, sizeof(DijNode));
    // Dijkstra algorithm
    cItem.node = src;
    cItem.weight = dist[src];
    HEAP_insert(myHeap, &cItem, cmp);
    while(myHeap->vect->len != 0){
        cItem = *((DijNode*)myHeap->vect->arr);
        HEAP_remove_root(myHeap, cmp);
        vis[cItem.node] = 1;
        aux = myGraph->neighbours[cItem.node];
        while(aux != NULL){
            if(dist[aux->val] > cItem.weight + aux->weight)
                dist[aux->val] = cItem.weight + aux->weight;
            if(vis[aux->val] == 0){
                nItem.node = aux->val;
                nItem.weight = dist[aux->val];
                HEAP_insert(myHeap, &nItem, cmp);
            }
            aux = aux->next;
        }
    }
    // Free memory
    HEAP_free(&myHeap);
    free(vis);

    return dist;
}
// Generate topological order array
void DFS_topsort(WGraph *graph, int cNode, int *visited, int *topsort, int *k){
    if(visited[cNode] == 1)
        return;
    visited[cNode] = 1;
    Node *aux = graph->neighbours[cNode];
    while(aux != NULL){
       DFS_topsort(graph, aux->val, visited, topsort, k);
       aux = aux->next;
    }
    topsort[*k] = cNode;
    (*k)--;
}
// Return array with topological order of graph
int *WGRAPH_topsort(WGraph *myGraph){
    int *topsort;
    int *visited;
    int i;
    int k;
    topsort = (int*)malloc(myGraph->nr_nodes * sizeof(int));
    visited = (int*)calloc(myGraph->nr_nodes, sizeof(int));
    k = myGraph->nr_nodes - 1;
    for(i = 0; i < myGraph->nr_nodes; i++)
        if(visited[i] == 0)
            DFS_topsort(myGraph, i, visited, topsort, &k);

    free(visited);
    return topsort;
}
// Return transpose graph
WGraph *WGRAPH_transpose(WGraph *myGraph){
    WGraph *tGraph;
    Node *aux;
    int i;
    WGRAPH_init(&tGraph, myGraph->nr_nodes);
    tGraph->nr_nodes = myGraph->nr_nodes;
    for(i = 0; i < myGraph->nr_nodes; i++){
        aux = myGraph->neighbours[i];
        while(aux != NULL){
            WGRAPH_add_link(tGraph, aux->val, i, aux->weight);
            aux = aux->next;
        }
    }
    return tGraph;
}
// free node list
void free_list(Node *root){
    if(root == NULL)
        return;
    free_list(root->next);
    free(root);
}
// Free cost graph memory
void WGRAPH_free(WGraph **myGraph){
    int nr_nodes;
    int i;
    nr_nodes = (*myGraph)->nr_nodes;
    for(i = 0; i < nr_nodes; i++)
        free_list((*myGraph)->neighbours[i]);
    free((*myGraph)->neighbours);
    free(*myGraph);
    *myGraph = NULL;
}