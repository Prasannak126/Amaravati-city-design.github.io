#include <iostream>
#include <vector>

using namespace std;

const int INF = 1000000;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj; 

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int v, int w, int weight) {
        adj[v].push_back({w, weight});
        adj[w].push_back({v, weight});
    }

    void primMST() {
        vector<int> dist(V, INF);
        vector<int> parent(V, -1);
        vector<bool> inMST(V, false);

        vector<pair<int, int>> pq;
        pq.push_back({0, 0}); 
        dist[0] = 0;

        while (!pq.empty()) {
            int minIndex = 0;
            for (int i = 1; i < pq.size(); ++i) {
                if (pq[i].first < pq[minIndex].first) {
                    minIndex = i;
                }
            }
            int u = pq[minIndex].second;
            pq.erase(pq.begin() + minIndex);

            inMST[u] = true;

            for (auto &neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!inMST[v] && dist[v] > weight) {
                    dist[v] = weight;
                    pq.push_back({dist[v], v});
                    parent[v] = u;
                }
            }
        }

        cout << "Edges in the Minimum Spanning Tree (MST):" << endl;
        for (int i = 1; i < V; ++i) {
            cout << parent[i] << " - " << i << " == " << dist[i] << endl;
        }
    }
};

int main() {
    int V = 6;
    Graph g(V);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 4, 4);
    g.addEdge(3, 5, 5);
    g.addEdge(4, 5, 6);
    g.addEdge(2, 3, 2);

    g.primMST();

    return 0;
}
