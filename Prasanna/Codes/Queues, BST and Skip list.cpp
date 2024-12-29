#include <iostream>
#include <vector>

using namespace std;

// Define a large value for infinity (INT_MAX equivalent)
const int INF = 1000000; 

// Graph class to represent visitor flow and resources
class Graph {
    int V;
    vector<vector<pair<int, int>>> adj; // Pair of node and weight

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int v, int w, int weight) {
        adj[v].push_back({w, weight});
        adj[w].push_back({v, weight});
    }

    void dijkstra(int src, vector<int>& dist) {
        vector<bool> visited(V, false);
        dist[src] = 0;

        for (int i = 0; i < V - 1; ++i) {
            int u = findMinDistance(dist, visited);
            visited[u] = true;

            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!visited[v] && dist[u] != INF && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

private:
    int findMinDistance(const vector<int>& dist, const vector<bool>& visited) {
        int min = INF, min_index;

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }

        return min_index;
    }
};

int main() {
    int V = 6;  // Number of vertices (zones)
    Graph g(V);

    // Adding edges to the graph
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 4, 4);
    g.addEdge(3, 5, 5);
    g.addEdge(4, 5, 6);
    g.addEdge(2, 3, 2);

    // Distance vector to store the shortest paths from source
    vector<int> dist(V, INF);

    // Run Dijkstra's algorithm from source zone 0
    g.dijkstra(0, dist);

    // Display shortest paths from source zone 0
    cout << "Shortest paths from source zone 0:" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Zone " << i << " : " << dist[i] << endl;
    }

    return 0;
}
