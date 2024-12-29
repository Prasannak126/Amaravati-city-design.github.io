#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// Structure to represent a graph
struct Graph {
    int adjMatrix[MAX][MAX]; // Adjacency matrix to represent graph
    int numVertices;         // Number of vertices (locations)
};

// Structure to represent a queue for BFS
struct Queue {
    int items[MAX];
    int front, rear;
};

// Function to initialize a graph with a given number of vertices
void initGraph(struct Graph* g, int vertices) {
    g->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->adjMatrix[i][j] = 0; // No edges initially
        }
    }
}

// Function to add an edge between two vertices
void addEdge(struct Graph* g, int u, int v) {
    g->adjMatrix[u][v] = 1;
    g->adjMatrix[v][u] = 1; // For undirected graph
}

// Function to initialize the queue
void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
bool isQueueEmpty(struct Queue* q) {
    return q->front == -1;
}

// Function to enqueue an element to the queue
void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX - 1) {
        printf("Queue overflow!\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

// Function to dequeue an element from the queue
int dequeue(struct Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue underflow!\n");
        return -1;
    }
    int value = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1; // Reset queue
    }
    return value;
}

// Function to perform BFS on the graph and plan waste collection route
void bfs(struct Graph* g, int start) {
    bool visited[MAX] = {false}; // Array to track visited vertices
    struct Queue q;
    initQueue(&q);

    // Start BFS from the given starting vertex
    visited[start] = true;
    enqueue(&q, start);

    printf("Waste collection route (using BFS):\n");

    while (!isQueueEmpty(&q)) {
        int current = dequeue(&q);
        printf("Collect waste from location %d\n", current);

        // Explore all adjacent vertices of the current vertex
        for (int i = 0; i < g->numVertices; i++) {
            if (g->adjMatrix[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(&q, i);
            }
        }
    }
}

// Main function to execute the program
int main() {
    struct Graph g;

    int n, e;
    printf("Enter the number of locations (vertices): ");
    scanf("%d", &n);

    initGraph(&g, n);

    printf("Enter the number of paths (edges): ");
    scanf("%d", &e);

    printf("Enter the paths (edges) as pairs of locations (u, v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(&g, u, v);
    }

    int start;
    printf("Enter the starting location for waste collection (vertex): ");
    scanf("%d", &start);

    // Perform BFS to plan the waste collection route
    bfs(&g, start);

    return 0;
}
