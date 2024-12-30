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
        cout << "Visiting node: " << node << endl;

        for (int i = 0; i < V; ++i) {
            if (graph[node][i] != 0 && !visited[i]) {
                visited[i] = true;
                s.push(i);
            }
        }
    }
}

void detectFaults(int V, vector<vector<int>>& graph) {
    vector<bool> visited(V, false);
    int startNode = 0; // Starting node for DFS (root node of the connected component)

    cout << "Performing DFS to detect network faults...\n";
    dfs(V, graph, startNode, visited);

    // Detect disconnected nodes (faults)
    cout << "\nUnreachable nodes (network faults detected):\n";
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            cout << "Node " << i << " is disconnected (fault)\n";
        }
    }
}

int main() {
    int V = 5;
    vector<vector<int>> graph = {
        {0, 10, 0, 0, 0},
        {10, 0, 5, 0, 0},
        {0, 5, 0, 10, 0},
        {0, 0, 10, 0, 20},
        {0, 0, 0, 20, 0}
    };

    detectFaults(V, graph);
    return 0;
}
