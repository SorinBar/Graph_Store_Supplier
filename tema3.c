#include "Tasks.h"

int main(){
    int n, m;
    int src, dest;
    float weight;
    int nr_storages;
    int *storage;
    int *destiantions;
    int nr_tasks;
    char task[3];
    int i, j, k, val;
    float cost;
    float minCost;

    // Read number of nodes, links and storages
    scanf("%d%d%d", &n, &m, &nr_storages);
    // Initialize Graph
    WGraph *myGraph;
    WGRAPH_init(&myGraph, n);
    // Fill Graph
    for(i = 0; i < m; i++){
        scanf("%d%d%f", &src, &dest, &weight);
        if(WGRAPH_add_link(myGraph, src, dest, weight) == -1){
            WGRAPH_free(&myGraph);
            exit(2);
        }
    }
    // Initilize storages array
    storage = (int*)calloc(n, sizeof(int));
    // Read storages
    for(i = 0; i < nr_storages; i++){
        scanf("%d", &val);
        storage[val] = 1;
    }
    // Initialize destiantions array
    destiantions = (int*)malloc(n * sizeof(int));
    // Read number of tasks to be solved
    scanf("%d", &nr_tasks);
    for(i = 0; i < nr_tasks; i++){
        scanf("%s", task);
        if(strcmp(task, "e1") == 0){
            cost = 0;
            scanf("%d", &src);
            scanf("%d", &val);
            for(j = 0; j < val; j++){
                scanf("%d", &dest);
                task1(myGraph, src, dest, &cost);
            }
            printf("%.1f", cost);
        }
        if(strcmp(task, "e2") == 0){
            task2(myGraph, storage);
        }
        if(strcmp(task, "e3") == 0){
            scanf("%d", &val);
            for(j = 0; j < val ; j++){
                // Reinitilize destinations array
                for(k = 0; k < n; k++)
                    destiantions[k] = 0;
                // Read current destination array
                scanf("%d", &k);
                while(k > 0){
                    scanf("%d", &dest);
                    destiantions[dest] = 1;
                    k--;
                }
                // Check the minimum cost from every storage, save minimum
                minCost = (float)INF;
                for(k = 0; k < n; k++)
                    if(storage[k] == 1){
                        cost = task3(myGraph, storage, k, destiantions);
                        if(cost < minCost)
                            minCost = cost;
                    }
                printf("%.1f", minCost);
                if(j != val -1)
                    printf("\n");
            }

        }
        if(i != nr_tasks - 1)
            printf("\n");  
    }

    // Free memory
    free(destiantions);
    free(storage);
    WGRAPH_free(&myGraph);

    return 0;
}