#include "Tasks.h"

/* Task 1 */
// Print the minimum cost road src->dest->src
void task1(WGraph *myGraph, int src, int dest, float *cost){
    Heap *myHeap;
    DijNode cItem, nItem;
    Node *aux;
    float *dist1, *dist2;
    int son, father;
    int nr_nodes;
    int *vis;
    int *arr;
    int i;
    int *road1, *road2;
    Vector *road;

    // Save the number of nodes for faster access
    nr_nodes = myGraph->nr_nodes;

    // Initialize road vectors
    VECTOR_init(&road, sizeof(int)); 

    // Initialize visited array
    vis = (int*)malloc((nr_nodes) * sizeof(int));
    for(i = 0; i < nr_nodes; i++)
        vis[i] = 0;

    // Initialize distance arrays
    dist1 = (float*)malloc((nr_nodes) * sizeof(float));
    dist2 = (float*)malloc((nr_nodes) * sizeof(float));
    for(i = 0; i < nr_nodes; i++){
        dist1[i] = INF;
        dist2[i] = INF;
    }
    dist1[src] = 0;
    dist2[dest] = 0;

    // Initialize heap
    HEAP_init(&myHeap, sizeof(DijNode));

    // Initilize roads
    road1 = (int*)malloc(myGraph->nr_nodes * sizeof(int));
    road2 = (int*)malloc(myGraph->nr_nodes * sizeof(int));
    for(i = 0; i < myGraph->nr_nodes; i++){
        road1[i] = -1;
        road2[i] = -1;
    }

    // Dijkstra algorithm for the first road src->dest
    cItem.node = src;
    cItem.weight = dist1[src];
    HEAP_insert(myHeap, &cItem, cmp);
    while(myHeap->vect->len != 0){
        cItem = *((DijNode*)myHeap->vect->arr);
        HEAP_remove_root(myHeap, cmp);
        vis[cItem.node] = 1;
        aux = myGraph->neighbours[cItem.node];
        while(aux != NULL){
            if(dist1[aux->val] > cItem.weight + aux->weight){
                dist1[aux->val] = cItem.weight + aux->weight;
                road1[aux->val] = cItem.node;
            }
            if(vis[aux->val] == 0){
                nItem.node = aux->val;
                nItem.weight = dist1[aux->val];
                HEAP_insert(myHeap, &nItem, cmp);
            }
            aux = aux->next;
        }
    }
    
    // Reinitialize visited array, the heap is already empty
    for(i = 0; i < nr_nodes; i++)
        vis[i] = 0;

    // Dijkstra algorithm for the secound road dest->src
    cItem.node = dest;
    cItem.weight = dist2[dest];
    HEAP_insert(myHeap, &cItem, cmp);
    while(myHeap->vect->len != 0){
        cItem = *((DijNode*)myHeap->vect->arr);
        HEAP_remove_root(myHeap, cmp);
        vis[cItem.node] = 1;
        aux = myGraph->neighbours[cItem.node];
        while(aux != NULL){
            if(dist2[aux->val] > cItem.weight + aux->weight){
                dist2[aux->val] = cItem.weight + aux->weight;
                road2[aux->val] = cItem.node;
            }
            if(vis[aux->val] == 0){
                nItem.node = aux->val;
                nItem.weight = dist2[aux->val];
                HEAP_insert(myHeap, &nItem, cmp);
            }
            aux = aux->next;
        }
    }

    // Save total cost
    (*cost) +=  dist1[dest] + dist2[src];

    // Print store ID
    printf("%d\n", dest);

    // Print min distances src->dest, dest->src
    printf("%.1f %.1f\n", dist1[dest], dist2[src]);
    
    // Generate the first half of the road
    i = dest;
    VECTOR_push_front(road, &dest);
    while(road1[i] != -1){
        VECTOR_push_front(road, &(road1[i]));
        i = road1[i];
    }
    // Print the first half of the road
    arr = road->arr;
    for(i = 0; i < road->len; i++){
        printf("%d ", arr[i]);
    }
    // Empty road
    road->len = 0;

    // Generate the secound half of the road
    i = src;
    VECTOR_push_front(road, &src);
    while(road2[i] != -1){
        VECTOR_push_front(road, &(road2[i]));
        i = road2[i];
    }
    // Print the secound half of the road
    arr = road->arr;
    for(i = 1; i < road->len; i++){
        printf("%d", arr[i]);
        if(i != road->len - 1)
            printf(" ");
    }
    printf("\n");

    // Free memory
    HEAP_free(&myHeap);
    free(road1);
    free(road2);
    free(dist1);
    free(dist2);
    free(vis);
    VECTOR_free(&road);
}

/* Task 2 */
// Save nodes by DFS in SConex matrix
void DFS_Conex(WGraph *myGraph, int cNode, int *visited, int *storage,
               int **SConex, int *order, int k){
    if(visited[cNode] == 1)
        return;
    visited[cNode] = 1;
    Node *aux = myGraph->neighbours[cNode];
    while(aux != NULL){
        if(storage[aux->val] == 0)
            DFS_Conex(myGraph, aux->val, visited, storage, SConex, order, k);
        aux = aux->next;
    }
    SConex[k][cNode] = 1;
    (SConex[k][myGraph->nr_nodes])++;
    order[cNode] = k;
}
// Print Strongly connected components in order
void task2(WGraph *myGraph, int *storage){
    int i, j, k;
    int c1, c2; // counter for new line
    int *topsort = WGRAPH_topsort(myGraph);
    int *visited = (int*)calloc(myGraph->nr_nodes, sizeof(int));
    WGraph *tGraph = WGRAPH_transpose(myGraph);
    int **SConex = (int**)malloc(myGraph->nr_nodes * sizeof(int*));
    int *order = (int*)malloc(myGraph->nr_nodes * sizeof(int));
    
    // Initialize order array
    for(i = 0; i < myGraph->nr_nodes; i++)
        order[i] = -1;
    k = 0;
    
    // Determine and save SSC in SConex to be printed in order
    for(i = 0; i < tGraph->nr_nodes; i++){
        if(visited[topsort[i]] == 0 && storage[topsort[i]] == 0){
            SConex[k] = (int*)calloc(myGraph->nr_nodes + 1, sizeof(int));
            DFS_Conex(tGraph, topsort[i], visited, storage, SConex, order, k);
            k++;
        }
    }
    
    // Print number of strongly connected components
    printf("%d\n", k);
    
    // Print strongly connected components in order
    c1 = 0;
    for(i = 0; i < myGraph->nr_nodes; i++){
        if(order[i] != -1){
            c1++;
            c2 = 0;
            for(j = 0; j < myGraph->nr_nodes; j++){
                if(SConex[order[i]][j] == 1){
                    c2++;
                    if(i != j)
                        order[j] = -1;
                    printf("%d", j);
                    if(c2 != SConex[order[i]][myGraph->nr_nodes])
                        printf(" ");
                }
            }
            if(c1 != k)
                printf("\n");
            order[i] = -1;
        }
    }
    
    // Free memory
    free(order);
    for(i = 0; i < k; i++)
        free(SConex[i]);
    free(SConex);
    WGRAPH_free(&tGraph);
    free(visited);
    free(topsort);
}

/* Task 3 */
// Compare function for min heap with mask
int cmpM(void *x, void *y){
    if(((DijNodeMask*)x)->weight - ((DijNodeMask*)y)->weight > (float)0)
        return -1;
    else
        return 1;
}
// Verify if a node was already visited with the same mask
int visitedM(Vector **vis, int node, unsigned int mask){
    int i;
    unsigned int *arr;
    arr = vis[node]->arr;
    for(i = 0; i < vis[node]->len; i++)
        if(arr[i] == mask)
            return 1;
    return 0;
}
// Verify if all destinations were visited
int passedDest(int *destinations, int nr_nodes, unsigned int mask){
    unsigned int auxMask;
    int i;
    for(i = 0; i < nr_nodes; i++){
        auxMask = 1 << i;
        if(destinations[i] == 1)
            if((int)(mask & auxMask) == 0)
                return 0;
    }
    return 1;
}
// Return minimum distance src->src, passing by all the destinations
float task3(WGraph *myGraph, int *storage, int src, int *destiantions){
    Heap *myHeap;
    Vector **vis;
    DijNodeMask cItem, nItem;
    Node *aux;
    float *dist;
    float minDist;
    int nr_nodes;
    int *allowed;
    unsigned int mask;
    int i;

    // Save the number of nodes for faster access
    nr_nodes = myGraph->nr_nodes;

    // Initialize allowed nodes array
    allowed = (int*)calloc(nr_nodes, sizeof(int));
    for(i = 0; i < nr_nodes; i++)
        if(destiantions[i] || storage[i])
            allowed[i] = 1;

    // Initialize visited array
    vis = (Vector**)malloc(nr_nodes * sizeof(Vector));
    for(i = 0; i < nr_nodes; i++)
        VECTOR_init(&(vis[i]), sizeof(unsigned int));

    // Initialize distance array
    dist = (float*)malloc((nr_nodes) * sizeof(float));
    for(i = 0; i < nr_nodes; i++)
        dist[i] = INF;
    dist[src] = (float)0;
    
    // Initialize heap
    HEAP_init(&myHeap, sizeof(DijNodeMask));
    
    // Initialize minDist
    minDist = (float)INF;
    
    // Dijkstra algorithm
    cItem.node = src;
    cItem.weight = dist[src];
    cItem.mask = 1 << src;
    HEAP_insert(myHeap, &cItem, cmpM);
    while(myHeap->vect->len != 0){
        cItem = *((DijNodeMask*)myHeap->vect->arr);
        HEAP_remove_root(myHeap, cmpM);
        // Check if we returned to the source with all destinations passed
        if(passedDest(destiantions, nr_nodes, cItem.mask))
            if(cItem.node == src)
                if(minDist > cItem.weight)
                    minDist = cItem.weight;
        // Go throught allowed childrens
        aux = myGraph->neighbours[cItem.node];
        while(aux != NULL){
            if(allowed[aux->val]){
                if(visitedM(vis, cItem.node, cItem.mask) == 0){
                    nItem.node = aux->val;
                    nItem.weight = cItem.weight + aux->weight;
                    nItem.mask = cItem.mask | (unsigned int)((1 << cItem.node));
                    HEAP_insert(myHeap, &nItem, cmpM);
                }
            }
            aux = aux->next;
        }
        // Add pair(node, mask) to visied matrix
        VECTOR_push_back(vis[cItem.node], &(cItem.mask));
    }

    // Free memory
    for(i = 0; i < nr_nodes; i++)
        VECTOR_free(&(vis[i]));
    free(vis);
    free(allowed);
    free(dist);
    HEAP_free(&myHeap);
    
    return minDist;
}