#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

// Segment Tree structure
int tree[4 * MAX]; // Segment tree array

// Build the segment tree
void build(int arr[], int node, int start, int end) {
    if (start == end) {
        // Leaf node: store the traffic density of a single zone
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        
        // Recursively build the left and right subtrees
        build(arr, left_child, start, mid);
        build(arr, right_child, mid + 1, end);
        
        // Internal node stores the sum of its children
        tree[node] = tree[left_child] + tree[right_child];
    }
}

// Range Query: Get the sum of traffic densities in the range [l, r]
int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        // The range is completely outside the node's range
        return 0;
    }
    if (l <= start && end <= r) {
        // The range is completely inside the node's range
        return tree[node];
    }
    // Partially inside and partially outside
    int mid = (start + end) / 2;
    int left_child = 2 * node + 1;
    int right_child = 2 * node + 2;
    
    int left_sum = query(left_child, start, mid, l, r);
    int right_sum = query(right_child, mid + 1, end, l, r);
    
    return left_sum + right_sum;
}

// Point Update: Set the traffic density in zone `idx` to `value`
void update(int node, int start, int end, int idx, int value) {
    if (start == end) {
        // Leaf node: update the traffic density of a specific zone
        tree[node] = value;
    } else {
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        
        if (start <= idx && idx <= mid) {
            // Update the left subtree
            update(left_child, start, mid, idx, value);
        } else {
            // Update the right subtree
            update(right_child, mid + 1, end, idx, value);
        }
        
        // After the update, recalculate the value of the internal node
        tree[node] = tree[left_child] + tree[right_child];
    }
}

int main() {
    int n, m, i, choice, l, r, idx, value;
    
    // Read the number of zones
    printf("Enter the number of zones: ");
    scanf("%d", &n);
    
    int arr[n];
    
    // Read the traffic densities for each zone
    printf("Enter the traffic densities for each zone:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Build the segment tree
    build(arr, 0, 0, n - 1);
    
    printf("\nMenu:\n");
    printf("1. Query the total traffic density in a range [l, r]\n");
    printf("2. Update the traffic density in zone idx\n");
    printf("3. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Query operation
                printf("Enter the range [l, r]: ");
                scanf("%d %d", &l, &r);
                printf("Total traffic density in range [%d, %d]: %d\n", l, r, query(0, 0, n - 1, l, r));
                break;
            
            case 2:
                // Update operation
                printf("Enter the zone index and new traffic density: ");
                scanf("%d %d", &idx, &value);
                update(0, 0, n - 1, idx, value);
                printf("Traffic density in zone %d updated to %d\n", idx, value);
                break;
            
            case 3:
                // Exit the program
                printf("Exiting...\n");
                exit(0);
            
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

