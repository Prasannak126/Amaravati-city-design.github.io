#include <stdio.h>
#include <stdlib.h>

// Define a node of the AVL tree
struct AVLNode {
    int zoneId;            // Zone identifier (e.g., district number)
    int temperature;       // Temperature value in that zone
    struct AVLNode *left, *right;
    int height;            // Height of the node
};

// Function to get the height of a node
int height(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get the balance factor of a node
int getBalance(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Right rotation (used to balance the tree)
struct AVLNode* rightRotate(struct AVLNode *y) {
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    // Return the new root
    return x;
}

// Left rotation (used to balance the tree)
struct AVLNode* leftRotate(struct AVLNode *x) {
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    // Return the new root
    return y;
}

// Function to insert a new node in the AVL Tree
struct AVLNode* insert(struct AVLNode* node, int zoneId, int temperature) {
    // Step 1: Perform normal BST insert
    if (node == NULL)
        return (struct AVLNode*)malloc(sizeof(struct AVLNode));

    if (zoneId < node->zoneId)
        node->left = insert(node->left, zoneId, temperature);
    else if (zoneId > node->zoneId)
        node->right = insert(node->right, zoneId, temperature);
    else
        return node;  // Duplicate zoneId, ignore it

    // Step 2: Update the height of this ancestor node
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // Step 3: Get the balance factor to check whether this node became unbalanced
    int balance = getBalance(node);

    // Left-Left case (Right rotation)
    if (balance > 1 && zoneId < node->left->zoneId)
        return rightRotate(node);

    // Right-Right case (Left rotation)
    if (balance < -1 && zoneId > node->right->zoneId)
        return leftRotate(node);

    // Left-Right case (Left rotation followed by Right rotation)
    if (balance > 1 && zoneId > node->left->zoneId) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-Left case (Right rotation followed by Left rotation)
    if (balance < -1 && zoneId < node->right->zoneId) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Function to search for a node by zoneId (to find zones needing cooling)
struct AVLNode* search(struct AVLNode* root, int zoneId) {
    if (root == NULL || root->zoneId == zoneId)
        return root;

    if (zoneId < root->zoneId)
        return search(root->left, zoneId);

    return search(root->right, zoneId);
}

// Function to perform an in-order traversal of the tree
void inOrder(struct AVLNode* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("Zone ID: %d, Temperature: %d\n", root->zoneId, root->temperature);
        inOrder(root->right);
    }
}

// Main function
int main() {
    struct AVLNode* root = NULL;
    int choice, zoneId, temperature;

    while (1) {
        printf("\n1. Insert Zone Data\n");
        printf("2. Search for a Zone\n");
        printf("3. Display All Zones (In-Order Traversal)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Zone ID: ");
                scanf("%d", &zoneId);
                printf("Enter Temperature: ");
                scanf("%d", &temperature);
                root = insert(root, zoneId, temperature);
                break;
            case 2:
                printf("Enter Zone ID to search: ");
                scanf("%d", &zoneId);
                struct AVLNode* result = search(root, zoneId);
                if (result != NULL)
                    printf("Found Zone ID: %d, Temperature: %d\n", result->zoneId, result->temperature);
                else
                    printf("Zone not found!\n");
                break;
            case 3:
                printf("All Zones (In-Order Traversal):\n");
                inOrder(root);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
