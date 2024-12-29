#include <iostream>
#include <vector>
using namespace std;

const int INF = 100000; 

struct Edge {
    int src, dest, weight;
};

class Graph {
    int V; // Number of vertices
    vector<pair<int, int>>* adjList; 
public:
    Graph(int V) {
        this->V = V;
        adjList = new vector<pair<int, int>>[V];
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
    }

    void dijkstra(int src) {
        vector<int> dist(V, INF); 
        vector<int> parent(V, -1);
        vector<bool> visited(V, false);

        dist[src] = 0;

        for (int i = 0; i < V; ++i) {
            int u = -1;
            for (int j = 0; j < V; ++j) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            if (dist[u] == INF) break;

            visited[u] = true;

            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
        cout << "Vertex   Distance from Source   Parent" << endl;
        for (int i = 0; i < V; ++i) {
            cout << i << " \t\t " << dist[i] << " \t\t " << parent[i] << endl;
        }
    }
};

int main() {
    int V = 6; 
    Graph g(V);

    vector<Edge> edges = {
        {0, 1, 201}, // A-B
        {0, 2, 302}, // A-C
        {1, 3, 153}, // B-D
        {1, 4, 252}, // B-E
        {2, 3, 101}, // C-D
        {2, 5, 402}, // C-F
        {3, 5, 301}  // D-F
    };

    for (const Edge& edge : edges) {
        g.addEdge(edge.src, edge.dest, edge.weight);
    }
    g.dijkstra(0);

    return 0;
}
