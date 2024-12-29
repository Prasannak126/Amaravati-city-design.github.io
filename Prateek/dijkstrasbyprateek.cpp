#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int to;
    int weight;
};

struct Vertex {
    int id;
    int dist;
    int prev;

    bool operator>(const Vertex& other) const {
        return dist > other.dist;
    }
};

class Graph {
public:
    int V; 
    vector<vector<Edge>> adj;

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
    }


    void dijkstra(int s) {
      
        vector<int> dist(V, numeric_limits<int>::infinity());
        vector<int> prev(V, -1); // To keep track of the penultimate vertex
        dist[s] = 0;

        priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
        pq.push({s, 0, -1});

        while (!pq.empty()) {
        
            Vertex u = pq.top();
            pq.pop();

          
            for (const auto& edge : adj[u.id]) {
                int v = edge.to;
                int weight = edge.weight;

                if (dist[u.id] + weight < dist[v]) {
                    dist[v] = dist[u.id] + weight;
                    prev[v] = u.id;

                  
                    pq.push({v, dist[v], u.id});
                }
            }
        }

        // Output the results
        for (int i = 0; i < V; ++i) {
            cout << "Vertex " << i << ": Distance = " << dist[i]
                 << ", Penultimate Vertex = " << prev[i] << endl;
        }
    }
};

int main() {

    Graph g(5);

   
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 0, 7);
    g.addEdge(3, 2, 6);
    g.addEdge(4, 1, 3);
    g.addEdge(4, 2, 9);

   
    g.dijkstra(0);

    return 0;
}
