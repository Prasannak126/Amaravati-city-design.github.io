#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

void dijkstra(int V, vector<vector<int>>& graph, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] != 0) {
                int weight = graph[u][v];
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    cout << "Shortest distances from the source vertex " << src << ":\n";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX)
            cout << "Vertex " << i << " is unreachable\n";
        else
            cout << "Vertex " << i << " -> Distance: " << dist[i] << endl;
    }
}

int main() {
    int V = 5;
    vector<vector<int>> graph = {
        {0, 10, 0, 30, 0},
        {10, 0, 50, 0, 0},
        {0, 50, 0, 20, 10},
        {30, 0, 20, 0, 60},
        {0, 0, 10, 60, 0}
    };
    int source = 0;
    dijkstra(V, graph, source);
    return 0;
}
