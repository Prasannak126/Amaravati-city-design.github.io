#include <iostream>
using namespace std;


struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};


int height(Node* node) {
    return node ? node->height : 0;
}


int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

Node* createNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = node->right = nullptr;
    node->height = 1; 
    return node;
}


Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;


    x->right = y;
    y->left = T2;


    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; 
}


Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;


    y->left = x;
    x->right = T2;


    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // New root
}

Node* insert(Node* node, int key) {
   
    if (!node)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);


    if (balance > 1 && key < node->left->key)
        return rightRotate(node);


    if (balance < -1 && key > node->right->key)
        return leftRotate(node);


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


void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}


int main() {
    Node* root = nullptr;

 
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    
    cout << "Inorder traversal of the AVL tree: ";
    inorder(root);

    return 0;
}
