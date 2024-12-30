#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int V, vector<vector<int>>& graph, int start, vector<bool>& visited) {
    stack<int> s;
    s.push(start);
    visited[start] = true;

    while (!s.empty()) {
        int node = s.top();
        s.pop();
        cout << "Visiting building: " << node << endl;

        for (int i = 0; i < V; ++i) {
            if (graph[node][i] != 0 && !visited[i]) {
                visited[i] = true;
                s.push(i);
            }
        }
    }
}

void optimizeCampusConnections(int V, vector<vector<int>>& graph) {
    vector<bool> visited(V, false);
    int startNode = 0; // Start DFS from the first building (node)

    cout << "Optimizing campus IoT network...\n";
    dfs(V, graph, startNode, visited);

    // Detect disconnected buildings (unreachable nodes)
    cout << "\nDisconnected buildings (requires additional connections):\n";
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            cout << "Building " << i << " is disconnected.\n";
        }
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

    optimizeCampusConnections(V, graph);
    return 0;
}
