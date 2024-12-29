#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int src, dest, weight;
};
struct Subset {
    int parent;
    int rank;
};

int find(Subset subsets[], int i);
void Union(Subset subsets[], int x, int y);
void sortEdges(vector<Edge>& edges);

vector<Edge> kruskalMST(vector<Edge>& edges, int V) {
    vector<Edge> ET;  
    sortEdges(edges);  

    Subset* subsets = new Subset[V];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int ecounter = 0;
    int k = 0;

    while (ecounter < V - 1 && k < edges.size()) {
        k++;
        Edge nextEdge = edges[k - 1];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            ET.push_back(nextEdge);
            Union(subsets, x, y);
            ecounter++;
        }
    }

    delete[] subsets;
    return ET;
}

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

void sortEdges(vector<Edge>& edges) {
    int n = edges.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (edges[j].weight > edges[j + 1].weight) {
                swap(edges[j], edges[j + 1]);
            }
        }
    }
}

int main() {
    int V = 6; 
    vector<Edge> edges = {
        {0, 1, 2}, {0, 2, 3}, {1, 3, 1}, {2, 4, 4}, {3, 5, 5}, {4, 5, 6}, {2, 3, 2}
    };

    vector<Edge> mst = kruskalMST(edges, V);

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (Edge e : mst) {
        cout << e.src << " -- " << e.dest << " == " << e.weight << endl;
    }

    return 0;
}
