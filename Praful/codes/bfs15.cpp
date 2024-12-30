#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph {
public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);  // Undirected graph
    }

    void bfs(int start, vector<bool>& visited) {
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            // Visit all unvisited neighbors
            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    void detectDisconnectedComponents(int failedNode) {
        vector<bool> visited(V, false);

        // Simulate failure by marking the failed node as unvisited
        visited[failedNode] = true;

        int disconnectedComponents = 0;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                // Start BFS from this node to explore its component
                bfs(i, visited);
                disconnectedComponents++;
            }
        }

        cout << "Number of disconnected components after power grid failure at node " << failedNode << ": " 
             << disconnectedComponents << endl;
    }

private:
    int V;
    vector<vector<int>> adjList;
};

int main() {
    Graph g(6);  // Example: 6 nodes (areas in the power grid)

    // Adding edges to represent the connections in the power grid
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);

    // Simulate power grid failure at different nodes and check for disconnections
    g.detectDisconnectedComponents(3);  // Simulate failure at node 3 (a critical node)

    return 0;
}
