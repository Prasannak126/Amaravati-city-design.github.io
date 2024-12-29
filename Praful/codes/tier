#include <iostream>
#include <unordered_map>
using namespace std;

// Node structure for Trie
class TrieNode {
public:
    unordered_map<char, TrieNode*> children; // Stores child nodes
    bool isEndOfWord; // Marks the end of a word

    TrieNode() {
        isEndOfWord = false;
    }
};

// Trie class
class Trie {
private:
    TrieNode* root;

public:
    // Constructor
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    void insert(string word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }

    // Search for a word in the Trie
    bool search(string word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return node->isEndOfWord;
    }

    // Check if a prefix exists in the Trie
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return true;
    }
};

// Example Usage
int main() {
    Trie trie;

    // Insert words into the Trie
    trie.insert("physics");
    trie.insert("physical");
    trie.insert("physical education");
    trie.insert("chemistry");
    trie.insert("math");

    // Search for words
    cout << "Search for 'physics': " << (trie.search("physics") ? "Found" : "Not Found") << endl;
    cout << "Search for 'biology': " << (trie.search("biology") ? "Found" : "Not Found") << endl;

    // Check for prefixes
    cout << "Prefix 'phy': " << (trie.startsWith("phy") ? "Exists" : "Doesn't Exist") << endl;
    cout << "Prefix 'bio': " << (trie.startsWith("bio") ? "Exists" : "Doesn't Exist") << endl;

    return 0;
}

