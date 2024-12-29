#include <iostream>
#include <vector>

using namespace std;

const int INF = 1000000;

class UnionFind {
    vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV])
                parent[rootV] = rootU;
            else if (rank[rootU] < rank[rootV])
                parent[rootU] = rootV;
            else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

class SegmentTree {
    vector<int> tree, lazy;
    int size;

    void build(vector<int>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(arr, v * 2, tl, tm);
            build(arr, v * 2 + 1, tm + 1, tr);
            tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    void updateRange(int v, int tl, int tr, int l, int r, int addend) {
        if (l > r)
            return;
        if (l == tl && r == tr) {
            tree[v] += addend;
            lazy[v] += addend;
        } else {
            int tm = (tl + tr) / 2;
            updateRange(v * 2, tl, tm, l, min(r, tm), addend);
            updateRange(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
            tree[v] = min(tree[v * 2], tree[v * 2 + 1]) + lazy[v];
        }
    }

    int queryRange(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return INF;
        if (l <= tl && tr <= r)
            return tree[v];
        int tm = (tl + tr) / 2;
        return min(queryRange(v * 2, tl, tm, l, min(r, tm)),
                   queryRange(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r)) + lazy[v];
    }

public:
    SegmentTree(vector<int>& arr) {
        size = arr.size();
        tree.resize(size * 4);
        lazy.resize(size * 4, 0);
        build(arr, 1, 0, size - 1);
    }

    void updateRange(int l, int r, int addend) {
        updateRange(1, 0, size - 1, l, r, addend);
    }

    int queryRange(int l, int r) {
        return queryRange(1, 0, size - 1, l, r);
    }
};

class Queue {
    vector<int> data;
    int frontIndex;

public:
    Queue() : frontIndex(0) {}

    void push(int value) {
        data.push_back(value);
    }

    void pop() {
        if (!empty()) {
            frontIndex++;
        }
    }

    int front() {
        return data[frontIndex];
    }

    bool empty() {
        return frontIndex >= data.size();
    }
};

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    void BFS(int s, vector<bool>& visited) {
        Queue q;
        visited[s] = true;
        q.push(s);

        while (!q.empty()) {
            s = q.front();
            q.pop();
            cout << "Monitoring zone: " << s << endl;

            for (auto adjacent : adj[s]) {
                if (!visited[adjacent]) {
                    visited[adjacent] = true;
                    q.push(adjacent);
                }
            }
        }
    }
};

int main() {
    int V = 6;
    Graph g(V);

    // Adding edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    // Monitor zones using BFS
    vector<bool> visited(V, false);
    g.BFS(0, visited);

    return 0;
}
