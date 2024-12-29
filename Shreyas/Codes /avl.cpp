#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the AVL tree
struct AVLNode {
    int key;            // Key to store traffic data, e.g., vehicle count at a location
    int height;         // Height of the node for balance calculation
    struct AVLNode* left;  // Pointer to left child
    struct AVLNode* right; // Pointer to right child
};

// Function to calculate the height of a node
int height(struct AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Function to get the balance factor of a node
int getBalance(struct AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Function to perform a right rotation
struct AVLNode* rightRotate(struct AVLNode* y) {
    struct AVLNode* x = y->left;
    struct AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + ((height(y->left) > height(y->right)) ? height(y->left) : height(y->right));
    x->height = 1 + ((height(x->left) > height(x->right)) ? height(x->left) : height(x->right));

    return x;  // New root
}

// Function to perform a left rotation
struct AVLNode* leftRotate(struct AVLNode* x) {
    struct AVLNode* y = x->right;
    struct AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + ((height(x->left) > height(x->right)) ? height(x->left) : height(x->right));
    y->height = 1 + ((height(y->left) > height(y->right)) ? height(y->left) : height(y->right));

    return y;  // New root
}

// Function to insert a new key into the AVL tree
struct AVLNode* insert(struct AVLNode* node, int key) {
    if (node == NULL) {
        // Create a new node if tree is empty
        struct AVLNode* newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    // Recursively insert the key
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;  // Duplicate keys are not allowed
    }

    // Update the height of the ancestor node
    node->height = 1 + ((height(node->left) > height(node->right)) ? height(node->left) : height(node->right));

    // Get the balance factor to check whether this node became unbalanced
    int balance = getBalance(node);

    // Left-Left case (Right rotation)
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // Right-Right case (Left rotation)
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // Left-Right case (Left rotation on left child, then right rotation)
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-Left case (Right rotation on right child, then left rotation)
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;  // Return the (unchanged) node pointer
}

// Function to perform an in-order traversal of the tree
void inorder(struct AVLNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);  // Print the key (traffic data)
        inorder(root->right);
    }
}

// Main function
int main() {
    struct AVLNode* root = NULL;

    int n, trafficData;

    printf("Enter the number of traffic data points to insert: ");
    scanf("%d", &n);

    printf("Enter the traffic data (e.g., vehicle counts at different locations):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &trafficData);
        root = insert(root, trafficData);  // Insert traffic data into the AVL tree
    }

    printf("Traffic data in balanced AVL tree (in-order traversal):\n");
    inorder(root);  // Display the traffic data in sorted order

    return 0;
}
