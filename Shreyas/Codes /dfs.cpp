#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Define the structure for the graph
struct Graph {
    int V;              // Number of vertices (zones)
    int adj[MAX][MAX];  // Adjacency matrix to represent edges
};

// Function to initialize the graph
void initGraph(struct Graph *g, int V) {
    g->V = V;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            g->adj[i][j] = 0;  // Initialize all edges to 0 (no edge)
        }
    }
}

// Function to add an edge between two zones (nodes)
void addEdge(struct Graph *g, int u, int v) {
    g->adj[u][v] = 1;  // Add an edge from u to v
    g->adj[v][u] = 1;  // Add an edge from v to u (undirected graph)
}

// DFS function to explore the green infrastructure zones
void DFS(struct Graph *g, int node, int visited[], int criticalAreas[]) {
    visited[node] = 1;  // Mark the current zone as visited

    // Check if this zone is a critical area (e.g., due to proximity to flood zones)
    if (criticalAreas[node] == 1) {
        printf("Critical Area found at Zone %d\n", node);
    }

    // Visit all adjacent zones
    for (int i = 0; i < g->V; i++) {
        if (g->adj[node][i] == 1 && !visited[i]) {
            DFS(g, i, visited, criticalAreas);
        }
    }
}

// Function to start the DFS traversal from the given starting node
void findCriticalAreas(struct Graph *g, int startNode, int criticalAreas[]) {
    int visited[MAX] = {0};  // Array to keep track of visited zones

    // Perform DFS traversal starting from the startNode
    DFS(g, startNode, visited, criticalAreas);
}

// Main function
int main() {
    struct Graph g;
    int V, E, criticalAreas[MAX], u, v, startNode;

    // Input the number of zones and edges (connections between zones)
    printf("Enter the number of zones: ");
    scanf("%d", &V);
    initGraph(&g, V);

    // Input critical areas (e.g., zones prone to floods or storms)
    for (int i = 0; i < V; i++) {
        printf("Enter 1 if Zone %d is critical (e.g., prone to floods/storms), else 0: ", i);
        scanf("%d", &criticalAreas[i]);
    }

    // Input the number of connections (edges) between zones
    printf("Enter the number of connections between zones: ");
    scanf("%d", &E);
    for (int i = 0; i < E; i++) {
        printf("Enter the zones connected by an edge (u v): ");
        scanf("%d %d", &u, &v);
        addEdge(&g, u, v);
    }

    // Input the starting node for the DFS traversal
    printf("Enter the starting node for the DFS traversal: ");
    scanf("%d", &startNode);

    // Find and display critical areas by performing DFS
    printf("\nPerforming DFS to find critical areas...\n");
    findCriticalAreas(&g, startNode, criticalAreas);

    return 0;
}
