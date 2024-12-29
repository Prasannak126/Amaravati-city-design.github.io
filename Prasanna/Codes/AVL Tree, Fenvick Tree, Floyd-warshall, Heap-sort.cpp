#include <iostream>
#include <vector>

using namespace std;

const int INF = 1000000;

struct AVLNode {
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
    AVLNode* root;

    int height(AVLNode* N) {
        return N ? N->height : 0;
    }

    int getBalance(AVLNode* N) {
        return N ? height(N->left) - height(N->right) : 0;
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    AVLNode* insert(AVLNode* node, int key) {
        if (!node) return new AVLNode(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node;
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);
        if (balance > 1 && key < node->left->key) return rightRotate(node);
        if (balance < -1 && key > node->right->key) return leftRotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

public:
    AVLTree() : root(nullptr) {}
    void insert(int key) { root = insert(root, key); }
};

class FenwickTree {
    vector<int> tree;
    int size;

public:
    FenwickTree(int n) : size(n) {
        tree.resize(n + 1, 0);
    }

    void update(int index, int value) {
        while (index <= size) {
            tree[index] += value;
            index += index & -index;
        }
    }

    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }
};

void floydWarshall(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<vector<int>> dist = graph;

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    cout << "Shortest distances between every pair of vertices:" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

void heapify(vector<pair<int, int>>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].second > arr[largest].second)
        largest = left;

    if (right < n && arr[right].second > arr[largest].second)
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<pair<int, int>>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    vector<int> waterUsage = {50, 30, 70, 40, 60, 80};

    // Create an AVL Tree and insert water usage data
    AVLTree avlTree;
    for (int usage : waterUsage) {
        avlTree.insert(usage);
    }

    FenwickTree fenwickTree(waterUsage.size());
    for (int i = 0; i < waterUsage.size(); ++i) {
        fenwickTree.update(i + 1, waterUsage[i]);
    }
    cout << "Cumulative water usage up to index 4: " << fenwickTree.query(4) << endl;

    vector<vector<int>> graph = {
        {0, 2, INF, 1},
        {2, 0, 3, 2},
        {INF, 3, 0, 4},
        {1, 2, 4, 0}
    };
    floydWarshall(graph);

    vector<pair<int, int>> waterNeeds = {
        {1, 50}, {2, 30}, {3, 70}, {4, 40}, {5, 60}, {6, 80}
    };
    heapSort(waterNeeds);
    cout << "Prioritized water allocation:" << endl;
    for (auto& need : waterNeeds) {
        cout << "Area " << need.first << " needs " << need.second << " units of water" << endl;
    }

    return 0;
}
