#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } NodeColor;

typedef struct Node {
    int data;
    NodeColor color;
    struct Node *left, *right, *parent;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED; // New nodes are always red initially
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Left Rotation
Node* leftRotate(Node* root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;

    return root;
}

// Right Rotation
Node* rightRotate(Node* root, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;

    return root;
}

// Fix violations after insertion
Node* fixInsertion(Node* root, Node* node) {
    while (node != root && node->parent->color == RED) {
        Node* grandparent = node->parent->parent;

        // Case 1: Parent is the left child of the grandparent
        if (node->parent == grandparent->left) {
            Node* uncle = grandparent->right;

            // Case 1.1: Uncle is red (recoloring)
            if (uncle != NULL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                // Case 1.2: Node is a right child (left rotation)
                if (node == node->parent->right) {
                    node = node->parent;
                    root = leftRotate(root, node);
                }
                // Case 1.3: Node is a left child (right rotation)
                node->parent->color = BLACK;
                grandparent->color = RED;
                root = rightRotate(root, grandparent);
            }
        }
        // Case 2: Parent is the right child of the grandparent
        else {
            Node* uncle = grandparent->left;

            // Case 2.1: Uncle is red (recoloring)
            if (uncle != NULL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                // Case 2.2: Node is a left child (right rotation)
                if (node == node->parent->left) {
                    node = node->parent;
                    root = rightRotate(root, node);
                }
                // Case 2.3: Node is a right child (left rotation)
                node->parent->color = BLACK;
                grandparent->color = RED;
                root = leftRotate(root, grandparent);
            }
        }
    }
    root->color = BLACK; // Ensure the root is always black
    return root;
}

// Insert a new node into the Red-Black Tree
Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    Node* parent = NULL;
    Node* current = root;

    // Perform standard BST insertion
    while (current != NULL) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parent;
    if (parent == NULL) {
        root = newNode; // Tree was empty
    } else if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    // Fix Red-Black Tree violations
    root = fixInsertion(root, newNode);
    return root;
}

// In-order traversal to display the tree
void inorderTraversal(Node* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d (%s) ", root->data, root->color == RED ? "RED" : "BLACK");
    inorderTraversal(root->right);
}

int main() {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 15);
    root = insert(root, 25);

    printf("In-order Traversal of Red-Black Tree:\n");
    inorderTraversal(root);

    return 0;
}
