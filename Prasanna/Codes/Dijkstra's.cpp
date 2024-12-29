#include <iostream>
#include <vector>
using namespace std;

const int INF = 100000;

struct Edge {
    int src, dest, distance, sensitivity, weight;
};

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
    vector<Edge> edges = {
        {0, 1, 100, 1, 101}, // EA
        {0, 2, 150, 2, 152}, // EB
        {0, 3, 80,  1, 81},  // EC
        {0, 4, 200, 3, 203}, // ED
        {1, 2, 50,  1, 51},  // AB
        {1, 3, 120, 2, 122}, // AC
        {1, 4, 180, 3, 183}, // AD
        {2, 3, 70,  1, 71},  // BC
        {2, 4, 100, 2, 102}, // BD
        {2, 5, 150, 1, 151}, // BE
        {3, 6, 80,  1, 81},  // CF
        {4, 6, 120, 2, 122}  // DF
    };

    int V = 7; // Number of nodes: 0 (Entrance), 1 (A), 2 (B), 3 (C), 4 (D), 5 (E), 6 (F)
    Graph g(V);

    for (const Edge& edge : edges) {
        g.addEdge(edge.src, edge.dest, edge.weight);
    }
    vector<int> distances = g.dijkstra(0);
    char nodes[] = {'E', 'A', 'B', 'C', 'D', 'F'};
    cout << "Shortest paths from Entrance (Dijkstra's Algorithm):" << endl;
    for (int i = 0; i < 6; ++i) {
        cout << "Distance to " << nodes[i] << ": " << distances[i] << endl;
    }

    return 0;
}
