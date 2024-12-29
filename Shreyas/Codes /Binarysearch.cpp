#include <stdio.h>
#include <stdlib.h>

// Define a node of the Binary Search Tree
struct BSTNode {
    int location;        // Location identifier (e.g., a grid or area code)
    int capacity;        // Energy generation capacity (e.g., kW)
    struct BSTNode *left, *right;
};

// Function to create a new node with given location and capacity
struct BSTNode* newNode(int location, int capacity) {
    struct BSTNode* node = (struct BSTNode*)malloc(sizeof(struct BSTNode));
    node->location = location;
    node->capacity = capacity;
    node->left = node->right = NULL;
    return node;
}

// Function to insert a new energy source into the BST
struct BSTNode* insert(struct BSTNode* root, int location, int capacity) {
    // If the tree is empty, create a new node
    if (root == NULL)
        return newNode(location, capacity);

    // Otherwise, recur down the tree
    if (location < root->location)
        root->left = insert(root->left, location, capacity);
    else if (location > root->location)
        root->right = insert(root->right, location, capacity);

    // Return the (unchanged) node pointer
    return root;
}

// Function to search for a renewable energy source by location
struct BSTNode* search(struct BSTNode* root, int location) {
    // Base cases: root is null or location is present at the root
    if (root == NULL || root->location == location)
        return root;

    // Location is greater than root's location
    if (location > root->location)
        return search(root->right, location);

    // Location is smaller than root's location
    return search(root->left, location);
}

// Function to perform an in-order traversal of the tree
void inOrder(struct BSTNode* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("Location: %d, Capacity: %d kW\n", root->location, root->capacity);
        inOrder(root->right);
    }
}

// Function to find the node with the minimum value (smallest location)
struct BSTNode* minValueNode(struct BSTNode* node) {
    struct BSTNode* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node from the BST
struct BSTNode* deleteNode(struct BSTNode* root, int location) {
    // Base case: If the tree is empty
    if (root == NULL)
        return root;

    // Recur down the tree to find the node to be deleted
    if (location < root->location)
        root->left = deleteNode(root->left, location);
    else if (location > root->location)
        root->right = deleteNode(root->right, location);

    // If the location is the same as the root's location, this is the node to be deleted
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct BSTNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct BSTNode* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct BSTNode* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->location = temp->location;
        root->capacity = temp->capacity;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->location);
    }
    return root;
}

// Main function
int main() {
    struct BSTNode* root = NULL;
    int choice, location, capacity;

    while (1) {
        printf("\n1. Insert Renewable Energy Source\n");
        printf("2. Search for an Energy Source by Location\n");
        printf("3. Display All Energy Sources (In-Order Traversal)\n");
        printf("4. Delete an Energy Source by Location\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Location ID: ");
                scanf("%d", &location);
                printf("Enter Capacity (in kW): ");
                scanf("%d", &capacity);
                root = insert(root, location, capacity);
                break;
            case 2:
                printf("Enter Location ID to search: ");
                scanf("%d", &location);
                struct BSTNode* result = search(root, location);
                if (result != NULL)
                    printf("Found Energy Source at Location: %d, Capacity: %d kW\n", result->location, result->capacity);
                else
                    printf("Energy Source not found at the given location!\n");
                break;
            case 3:
                printf("All Energy Sources (In-Order Traversal):\n");
                inOrder(root);
                break;
            case 4:
                printf("Enter Location ID to delete: ");
                scanf("%d", &location);
                root = deleteNode(root, location);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
