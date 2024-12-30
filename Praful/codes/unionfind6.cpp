#include <iostream>
#include <vector>

using namespace std;

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
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            // Union by rank: attach the smaller tree under the root of the larger tree
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

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int main() {
    int n = 10;  // Number of students
    UnionFind uf(n);

    // Example: Students with overlapping interests form groups
    uf.unite(0, 1);  // Student 0 and Student 1 belong to the same group
    uf.unite(1, 2);  // Student 1 and Student 2 belong to the same group
    uf.unite(3, 4);  // Student 3 and Student 4 belong to the same group
    uf.unite(5, 6);  // Student 5 and Student 6 belong to the same group
    uf.unite(7, 8);  // Student 7 and Student 8 belong to the same group

    // Check if students are in the same group
    cout << "Are Student 0 and Student 2 in the same group? " << (uf.connected(0, 2) ? "Yes" : "No") << endl;
    cout << "Are Student 3 and Student 5 in the same group? " << (uf.connected(3, 5) ? "Yes" : "No") << endl;
    cout << "Are Student 7 and Student 8 in the same group? " << (uf.connected(7, 8) ? "Yes" : "No") << endl;
    cout << "Are Student 2 and Student 4 in the same group? " << (uf.connected(2, 4) ? "Yes" : "No") << endl;

    return 0;
}
