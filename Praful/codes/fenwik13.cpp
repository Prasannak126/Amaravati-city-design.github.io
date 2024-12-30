#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
public:
    FenwickTree(int size) {
        this->size = size;
        tree.resize(size + 1, 0);
    }

    void update(int index, int delta) {
        while (index <= size) {
            tree[index] += delta;
            index += index & (-index);
        }
    }

    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & (-index);
        }
        return sum;
    }

    int queryRange(int left, int right) {
        return query(right) - query(left - 1);
    }

private:
    vector<int> tree;
    int size;
};

int main() {
    vector<int> energyFlow = {10, 20, 30, 40, 50, 60, 70};

    FenwickTree fenwick(energyFlow.size());

    // Initialize Fenwick Tree with energy flow values
    for (int i = 0; i < energyFlow.size(); i++) {
        fenwick.update(i + 1, energyFlow[i]);  // Fenwick Tree is 1-based index
    }

    cout << "Total energy flow from index 2 to 5: " << fenwick.queryRange(2, 5) << endl;

    // Update energy flow at index 3
    fenwick.update(3, 15);  // Increase the energy flow at index 3 by 15

    cout << "Total energy flow from index 2 to 5 after update: " << fenwick.queryRange(2, 5) << endl;

    return 0;
}
