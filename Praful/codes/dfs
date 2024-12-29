#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

// Graph representation
class Graph {
public:
    unordered_map<string, vector<string>> adjList; // Adjacency list

    void addEdge(const string& u, const string& v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Assuming an undirected graph
    }

    void dfs(const string& startNode) {
        unordered_map<string, bool> visited;
        stack<string> stack;

        stack.push(startNode);
        cout << "DFS Traversal from " << startNode << ":" << endl;

        while (!stack.empty()) {
            string node = stack.top();
            stack.pop();

            if (!visited[node]) {
                visited[node] = true;
                cout << node << " ";

                for (const auto& neighbor : adjList[node]) {
                    if (!visited[neighbor]) {
                        stack.push(neighbor);
                    }
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Graph cityGraph;

    // Example: Adding energy plants and educational institutions
    cityGraph.addEdge("EnergyPlant1", "EducationCenter1");
    cityGraph.addEdge("EducationCenter1", "Library");
    cityGraph.addEdge("Library", "EnergyPlant2");
    cityGraph.addEdge("EnergyPlant2", "School");
    cityGraph.addEdge("School", "EnergyPlant1");
    cityGraph.addEdge("EducationCenter1", "School");

    // Start DFS from a node (e.g., "EnergyPlant1")
    cityGraph.dfs("EnergyPlant1");

    return 0;
}
