#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int to, weight;
    bool operator>(const Edge& other) const {
        return weight > other.weight;  // Min-heap (priority queue)
    }
};

class Graph {
public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    void primMST() {
        vector<int> minWeight(V, INT_MAX);  // Stores the minimum weight to connect to the MST
        vector<bool> inMST(V, false);       // Marks nodes that are in the MST
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

        minWeight[0] = 0;  // Start with the first node
        pq.push({0, 0});    // Push the first node to the priority queue

        int totalCost = 0;

        while (!pq.empty()) {
            int u = pq.top().to;
            int weight = pq.top().weight;
            pq.pop();

            if (inMST[u]) continue;  // Skip if the node is already in MST

            inMST[u] = true;
            totalCost += weight;

            // Traverse all the neighbors of the node
            for (auto& edge : adjList[u]) {
                int v = edge.to;
                int w = edge.weight;

                if (!inMST[v] && w < minWeight[v]) {
                    minWeight[v] = w;
                    pq.push({v, w});
                }
            }
        }

        cout << "Minimum cost to connect the city power grid (MST): " << totalCost << endl;
    }

private:
    int V;
    vector<vector<Edge>> adjList;
};

int main() {
    Graph g(6);  // Example: 6 nodes in the city (schools, residential areas)
    
    // Adding edges (u, v, weight) representing connections between areas
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 3, 3);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 4, 6);
    g.addEdge(3, 5, 8);
    g.addEdge(4, 5, 9);

    g.primMST();  // Find the MST and print the total cost

    return 0;
}
