#include <stdio.h>
#include <limits.h>

#define MAX_NODES 100  // Maximum number of intersections (nodes)

int graph[MAX_NODES][MAX_NODES];  // Adjacency matrix for the graph
int dist[MAX_NODES];              // Distance array to store shortest path values
int visited[MAX_NODES];           // Visited array to mark nodes as processed

// Function to find the node with the minimum distance that hasn't been visited yet
int minDistance(int n) {
    int min = INT_MAX, min_index;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    
    return min_index;
}

// Dijkstra's Algorithm for finding shortest paths from the source node
void dijkstra(int n, int source) {
    // Initialize distances to all nodes as infinity
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    
    // Distance to source is 0
    dist[source] = 0;
    
    // Find shortest paths for all nodes
    for (int count = 0; count < n - 1; count++) {
        // Get the vertex with the minimum distance from the set of unvisited vertices
        int u = minDistance(n);
        
        // Mark the node as visited
        visited[u] = 1;
        
        // Update dist[] of the adjacent nodes of the picked node
        for (int v = 0; v < n; v++) {
            // Update the distance if there's a shorter path from u to v
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

// Function to print the shortest path distances from source to all other nodes
void printSolution(int n) {
    printf("Intersection\tShortest Time/Distance\n");
    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX) {
            printf("%d\t\tUnreachable\n", i);
        } else {
            printf("%d\t\t%d\n", i, dist[i]);
        }
    }
}

int main() {
    int n, m;
    
    // Input the number of intersections (nodes) and roads (edges)
    printf("Enter the number of intersections: ");
    scanf("%d", &n);
    
    printf("Enter the number of roads (edges): ");
    scanf("%d", &m);
    
    // Initialize the graph (adjacency matrix) with no roads initially
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;  // No road
        }
    }
    
    // Input the roads (edges) with their weights (time or congestion)
    printf("Enter the roads (start, end, time/congestion):\n");
    for (int i = 0; i < m; i++) {
        int u, v, w;
        printf("Road %d: ", i+1);
        scanf("%d %d %d", &u, &v, &w);
        
        // Since the graph is undirected, update both directions
        graph[u][v] = w;
        graph[v][u] = w;
    }
    
    // Input the source intersection (the point where we start calculating shortest paths)
    int source;
    printf("Enter the source intersection (start point): ");
    scanf("%d", &source);
    
    // Run Dijkstra's Algorithm from the source intersection
    dijkstra(n, source);
    
    // Print the shortest path distances from the source to all other intersections
    printSolution(n);
    
    return 0;
}
