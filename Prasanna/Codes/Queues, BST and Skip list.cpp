#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

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

struct SkipNode {
    string visitorName;
    string regulation;
    vector<SkipNode*> forward;

    SkipNode(int level, string visitorName, string regulation) : visitorName(visitorName), regulation(regulation), forward(level + 1, nullptr) {}
};

class SkipList {
private:
    int maxLevel;
    float probability;
    SkipNode* header;
    int currentLevel;

public:
    SkipList(int maxLevel, float probability) : maxLevel(maxLevel), probability(probability) {
        currentLevel = 0;
        header = new SkipNode(maxLevel, "", "");
        srand(42); 
    }

    int randomLevel() {
        int level = 0;
        while (level < maxLevel && ((float) rand() / RAND_MAX) < probability) {
            level++;
        }
        return level;
    }

    void insert(string visitorName, string regulation) {
        vector<SkipNode*> update(maxLevel + 1);
        SkipNode* current = header;

        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->visitorName < visitorName) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if (current == nullptr || current->visitorName != visitorName) {
            int newLevel = randomLevel();
            if (newLevel > currentLevel) {
                for (int i = currentLevel + 1; i <= newLevel; i++) {
                    update[i] = header;
                }
                currentLevel = newLevel;
            }
            SkipNode* newNode = new SkipNode(newLevel, visitorName, regulation);
            for (int i = 0; i <= newLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }

    string search(string visitorName) {
        SkipNode* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->visitorName < visitorName) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];
        if (current && current->visitorName == visitorName) {
            return current->regulation;
        }
        return "Regulation not found";
    }
};

TreeNode* insert(TreeNode* root, Reservation res);
void inorder(TreeNode* root);

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

int main() {
    
    vector<Reservation> reservations = {
        {10, "John Doe", 2, "johndoe@example.com", "10 AM - 11 AM", "Tourist Attraction 1", "Sightseeing"},
        {20, "Jane Smith", 4, "janesmith@example.com", "1 PM - 2 PM", "Tourist Attraction 2", "Cultural Event"}
    };

    TreeNode* root = nullptr;
    for (const auto& res : reservations) {
        root = insert(root, res);
    }

    cout << "Reservations in BST:" << endl;
    inorder(root);

    SkipList skipList(4, 0.5);
    skipList.insert("John Doe", "No photography allowed.");
    skipList.insert("Jane Smith", "Follow the tour guide.");

    cout << "\nVisitor Regulations:" << endl;
    cout << "John Doe: " << skipList.search("John Doe") << endl;
    cout << "Jane Smith: " << skipList.search("Jane Smith") << endl;

    return 0;
}
