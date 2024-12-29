#include <iostream>
#include <vector>
#include <string>

using namespace std;
struct Reservation {
    int priority;
    string visitorName;
    int groupSize;
    string contactInfo;
    string timeSlot;
    string preferredArea;
    string activity;

    bool operator<(const Reservation& other) const {
        return priority < other.priority;
    }
};

struct TreeNode {
    Reservation reservation;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Reservation res) : reservation(res), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, Reservation res);
void inorder(TreeNode* root);
TreeNode* search(TreeNode* root, string visitorName);
void sortReservations(vector<Reservation>& reservations);
void swap(Reservation& a, Reservation& b);

TreeNode* insert(TreeNode* root, Reservation res) {
    if (!root) return new TreeNode(res);
    if (res.visitorName < root->reservation.visitorName) {
        root->left = insert(root->left, res);
    } else {
        root->right = insert(root->right, res);
    }
    return root;
}

void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << "Visitor: " << root->reservation.visitorName << " | Activity: " << root->reservation.activity << endl;
    inorder(root->right);
}

TreeNode* search(TreeNode* root, string visitorName) {
    if (!root || root->reservation.visitorName == visitorName) return root;
    if (visitorName < root->reservation.visitorName) {
        return search(root->left, visitorName);
    } else {
        return search(root->right, visitorName);
    }
}

void sortReservations(vector<Reservation>& reservations) {
    int n = reservations.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (reservations[j] < reservations[minIndex]) {
                minIndex = j;
            }
        }
        swap(reservations[i], reservations[minIndex]);
    }
}

void swap(Reservation& a, Reservation& b) {
    Reservation temp = a;
    a = b;
    b = temp;
}

int main() {
    vector<Reservation> reservations = {
        {10, "John Doe", 2, "johndoe@example.com", "10 AM - 11 AM", "Meditation Zone 1", "Yoga"},
        {20, "Jane Smith", 4, "janesmith@example.com", "1 PM - 2 PM", "Meditation Zone 2", "Spiritual Counseling"},
        {15, "Alice Brown", 3, "alicebrown@example.com", "3 PM - 4 PM", "Meditation Zone 3", "Meditation"}
    };

    TreeNode* root = nullptr;
    for (const auto& res : reservations) {
        root = insert(root, res);
    }

    cout << "Reservations in BST:" << endl;
    inorder(root);

    vector<Reservation> reservationQueue;
    reservationQueue.push_back({5, "Charlie Green", 1, "charliegreen@example.com", "4 PM - 5 PM", "Meditation Zone 1", "Yoga"});
    reservationQueue.push_back({25, "Diana White", 2, "dianawhite@example.com", "2 PM - 3 PM", "Meditation Zone 2", "Meditation"});

   
    vector<Reservation> heap;
    for (const auto& res : reservationQueue) {
        heap.push_back(res);
    }

    sortReservations(heap);

    cout << "\nProcessing reservations based on priority:" << endl;
    while (!heap.empty()) {
        Reservation res = heap.back();
        heap.pop_back();
        cout << "Visitor: " << res.visitorName << " | Activity: " << res.activity << " | Priority: " << res.priority << endl;
    }

    return 0;
}
