void buildSegmentTree(vector<int>& tree, vector<int>& arr, int node, int start, int end) {
    if (start == end) tree[node] = arr[start];
    else {
        int mid = (start + end) / 2;
        buildSegmentTree(tree, arr, 2 * node, start, mid);
        buildSegmentTree(tree, arr, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}
