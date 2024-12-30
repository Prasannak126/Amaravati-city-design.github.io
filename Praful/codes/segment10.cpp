#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    void update(int idx, int val) {
        update(0, 0, n - 1, idx, val);
    }

private:
    int n;
    vector<int> tree;

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0;  // No overlap
        }
        if (l <= start && end <= r) {
            return tree[node];  // Total overlap
        }
        // Partial overlap
        int mid = (start + end) / 2;
        int leftQuery = query(2 * node + 1, start, mid, l, r);
        int rightQuery = query(2 * node + 2, mid + 1, end, l, r);
        return leftQuery + rightQuery;
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node + 1, start, mid, idx, val);
            } else {
                update(2 * node + 2, mid + 1, end, idx, val);
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }
};

int main() {
    vector<int> energyResources = {10, 20, 30, 40, 50, 60, 70};
    SegmentTree segTree(energyResources);

    // Query the sum of energy resources in the range [1, 4]
    cout << "Energy resources from index 1 to 4: " << segTree.query(1, 4) << endl;

    // Update the energy resource at index 3 to 100
    segTree.update(3, 100);

    // Query again after the update
    cout << "Energy resources from index 1 to 4 after update: " << segTree.query(1, 4) << endl;

    return 0;
}
