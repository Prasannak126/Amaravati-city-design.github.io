#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& e) const {
        return weight < e.weight;
    }
};

class UnionFind {
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

private:
    vector<int> parent, rank;
};

void kruskalMST(int V, vector<Edge>& edges) {
    UnionFind uf(V);
    sort(edges.begin(), edges.end());

    vector<Edge> mst;
    for (auto& edge : edges) {
        int u = edge.u, v = edge.v;
        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            mst.push_back(edge);
        }
    }

    cout << "Minimum Spanning Tree (MST):\n";
    int totalWeight = 0;
    for (auto& edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    cout << "Total Weight: " << totalWeight << endl;
}

int main() {
    int V = 4;  // Number of vertices (e.g., schools, residential areas)
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, 
        {1, 3, 15}, {2, 3, 4}
    };

    kruskalMST(V, edges);

    return 0;
}
