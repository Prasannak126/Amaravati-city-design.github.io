int findParent(int node, vector<int>& parent) {
    if (parent[node] == node) return node;
    return parent[node] = findParent(parent[node], parent);
}

void unionNodes(int u, int v, vector<int>& parent, vector<int>& rank) {
    int pu = findParent(u, parent);
    int pv = findParent(v, parent);
    if (pu != pv) {
        if (rank[pu] > rank[pv]) parent[pv] = pu;
        else if (rank[pu] < rank[pv]) parent[pu] = pv;
        else { parent[pv] = pu; rank[pu]++; }
    }
}
