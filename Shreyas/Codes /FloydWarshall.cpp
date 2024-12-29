#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

// Function to implement the Floyd-Warshall Algorithm
void floydWarshall(vector<vector<int>>& graph, int V) {
    // Create a distance matrix initialized to the graph values
    vector<vector<int>> dist = graph;

    // Apply the Floyd-Warshall algorithm
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                // Update the distance if a shorter path is found
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Output the shortest path matrix
    cout << "Fuel-efficient routes (minimized fuel consumption):\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    int V = 4; // Number of locations (nodes)
    
    // Fuel consumption (or distance) between locations represented as a graph (adjacency matrix)
    vector<vector<int>> graph = {
        {0, 3, INF, 7}, // From location 0 to others (INF means no direct route)
        {3, 0, 2, INF}, // From location 1 to others
        {INF, 2, 0, 1}, // From location 2 to others
        {7, INF, 1, 0}  // From location 3 to others
    };

    // Apply the Floyd-Warshall algorithm to find the most fuel-efficient routes
    floydWarshall(graph, V);

    return 0;
}
