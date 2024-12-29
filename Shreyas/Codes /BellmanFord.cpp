#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define a structure to represent an edge in the graph
struct Edge {
    int source, destination, weight;
};

// Define a structure to represent the graph
struct Graph {
    int V, E; // Number of vertices (V) and edges (E)
    struct Edge* edge;
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// Function to print the distances from the source
void printDistances(int distance[], int V) {
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, distance[i]);
    }
}

// Bellman-Ford algorithm implementation
void bellmanFord(struct Graph* graph, int source) {
    int V = graph->V;
    int E = graph->E;
    int distance[V];

    // Step 1: Initialize distances from the source to all vertices as infinite
    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
    }
    distance[source] = 0;

    // Step 2: Relax all edges (V - 1) times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].source;
            int v = graph->edge[j].destination;
            int weight = graph->edge[j].weight;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int j = 0; j < E; j++) {
        int u = graph->edge[j].source;
        int v = graph->edge[j].destination;
        int weight = graph->edge[j].weight;
        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            printf("Graph contains a negative weight cycle.\n");
            return;
        }
    }

    // Print the distances
    printDistances(distance, V);
}

int main() {
    int V = 5; // Number of vertices (bus/train stops)
    int E = 8; // Number of edges (routes)

    struct Graph* graph = createGraph(V, E);

    // Define the edges (routes) with weights (time/cost)
    graph->edge[0] = (struct Edge){0, 1, 4};
    graph->edge[1] = (struct Edge){0, 2, 5};
    graph->edge[2] = (struct Edge){1, 3, 3};
    graph->edge[3] = (struct Edge){2, 1, -6};
    graph->edge[4] = (struct Edge){3, 2, 2};
    graph->edge[5] = (struct Edge){1, 4, 2};
    graph->edge[6] = (struct Edge){4, 3, 1};
    graph->edge[7] = (struct Edge){3, 4, -2};

    int source = 0; // Source node (central station)
    bellmanFord(graph, source);

    // Free allocated memory
    free(graph->edge);
    free(graph);

    return 0;
}
