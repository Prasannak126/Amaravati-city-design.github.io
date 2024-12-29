#include <iostream>
#include <vector>

using namespace std;

const int INF = 1000000;

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
        pq.push_back({0, 0}); // (weight, node)
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
   
    vector<int> soilQuality = {4, 2, 5, 3, 1, 6};


    SegmentTree segTree(soilQuality);
    segTree.updateRange(1, 3, -1); // Decrease soil quality in range [1, 3] by 1
    cout << "Minimum soil quality in range [1, 4]: " << segTree.queryRange(1, 4) << endl;

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
