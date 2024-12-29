
#include <iostream>
#include <vector>
using namespace std;

// Define a large number for infinity
const int INF = 100000;

// Graph structure for Dijkstra's algorithm
class Graph {
    int V;
    vector<pair<int, int>>* adjList;
public:
    Graph(int V) {
        this->V = V;
        adjList = new vector<pair<int, int>>[V];
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Because the graph is undirected
    }

    vector<int> dijkstra(int src) {
        vector<int> dist(V, INF);
        vector<bool> visited(V, false);

        dist[src] = 0;

        for (int i = 0; i < V; ++i) {
            int u = -1;
            for (int j = 0; j < V; ++j) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            if (dist[u] == INF)
                break;

            visited[u] = true;
            for (auto neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }

        return dist;
    }
};

int main() {
    // Node definition
    char nodes[] = {'E', 'A', 'B', 'C', 'D', 'F'};
    int V = sizeof(nodes) / sizeof(nodes[0]);

    // Create a graph
    Graph g(V);

    // Edge creation and weighting
    g.addEdge(0, 1, 101); // EA
    g.addEdge(0, 2, 152); // EB
    g.addEdge(0, 3, 81);  // EC
    g.addEdge(0, 4, 203); // ED
    g.addEdge(1, 2, 51);  // AB
    g.addEdge(1, 3, 122); // AC
    g.addEdge(1, 4, 183); // AD
    g.addEdge(2, 3, 71);  // BC
    g.addEdge(2, 4, 102); // BD
    g.addEdge(2, 0, 151); // BE
    g.addEdge(3, 5, 81);  // CF
    g.addEdge(4, 5, 122); // DF

    // Apply Dijkstra's algorithm from the Entrance ('E' or node 0)
    vector<int> distances = g.dijkstra(0);

    // Output distances from the Entrance to all other nodes
    cout << "Shortest paths from Entrance (Dijkstra's Algorithm):" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Distance to " << nodes[i] << ": " << distances[i] << endl;
    }

    return 0;
}
