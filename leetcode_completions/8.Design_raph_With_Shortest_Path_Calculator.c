#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int n;               // Number of nodes
    int** adjMatrix;     // Adjacency matrix to store edge weights
} Graph;

Graph* graphCreate(int n, int** edges, int edgesSize, int* edgesColSize) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->n = n;
    graph->adjMatrix = (int**) malloc(n * sizeof(int*));
    
    for (int i = 0; i < n; i++) {
        graph->adjMatrix[i] = (int*) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            graph->adjMatrix[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

    for (int i = 0; i < edgesSize; i++) {
        int from = edges[i][0];
        int to = edges[i][1];
        int cost = edges[i][2];
        graph->adjMatrix[from][to] = cost;
    }
    
    return graph;
}

void graphAddEdge(Graph* obj, int* edge, int edgeSize) {
    if (edgeSize == 3) {
        int from = edge[0];
        int to = edge[1];
        int cost = edge[2];
        obj->adjMatrix[from][to] = cost;
    }
}

int graphShortestPath(Graph* obj, int node1, int node2) {
    int n = obj->n;
    int distances[n];
    int visited[n];

    for (int i = 0; i < n; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
    }
    
    distances[node1] = 0;

    for (int count = 0; count < n - 1; count++) {
        int minDistance = INT_MAX, u = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && distances[i] < minDistance) {
                minDistance = distances[i];
                u = i;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && obj->adjMatrix[u][v] != INT_MAX && distances[u] != INT_MAX &&
                distances[u] + obj->adjMatrix[u][v] < distances[v]) {
                distances[v] = distances[u] + obj->adjMatrix[u][v];
            }
        }
    }

    return distances[node2] == INT_MAX ? -1 : distances[node2];
}

void graphFree(Graph* obj) {
    for (int i = 0; i < obj->n; i++) {
        free(obj->adjMatrix[i]);
    }
    free(obj->adjMatrix);
    free(obj);
}
