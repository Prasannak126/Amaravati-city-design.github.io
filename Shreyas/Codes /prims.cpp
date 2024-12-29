#include <stdio.h>
#include <limits.h>

#define MAX_NODES 10
#define INF INT_MAX

// Graph represented as an adjacency matrix
int graph[MAX_NODES][MAX_NODES];

// Function to find the vertex with the minimum key value
int minKey(int key[], int mstSet[], int n) {
    int min = INF, minIndex;
    for (int v = 0; v < n; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to implement Prim's Algorithm to find MST
void primMST(int n) {
    int parent[MAX_NODES];  // Array to store constructed MST
    int key[MAX_NODES];     // Key values used to pick the minimum weight edge
    int mstSet[MAX_NODES];  // To represent the set of vertices not yet included in MST

    // Initialize all keys as infinite and MST set as false
    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }

    // Start with the first node (arbitrary choice)
    key[0] = 0;  // Set key value of the first node to 0 to pick it first
    parent[0] = -1;  // First node is the root of MST

    // Construct MST for all nodes
    for (int count = 0; count < n - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet processed
        int u = minKey(key, mstSet, n);
        mstSet[u] = 1;  // Include this vertex in MST

        // Update key and parent values for the adjacent vertices of the picked vertex
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the MST constructed
    printf("Edge \t Weight\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d \t %d\n", parent[i], i, graph[i][parent[i]]);
    }
}

int main() {
    int n;

    // Get the number of nodes (regions for parks or forests)
    printf("Enter number of regions: ");
    scanf("%d", &n);

    // Get the adjacency matrix (graph representation)
    printf("Enter the adjacency matrix (enter 0 for no direct connection):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Run Prim's algorithm to find the optimal placement of urban forests
    primMST(n);

    return 0;
}
