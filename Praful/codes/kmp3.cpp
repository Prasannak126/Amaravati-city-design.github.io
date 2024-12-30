#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> computeLPSArray(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0); // Longest Prefix Suffix array
    int len = 0;  // Length of the previous longest prefix suffix
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];  // Use the previous prefix suffix
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

void KMPSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    vector<int> lps = computeLPSArray(pattern);
    int i = 0;  // Index for text
    int j = 0;  // Index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text = "This is a simple digital library system. It contains books and papers on various topics.";
    string pattern = "digital";

    cout << "Searching for the pattern: " << pattern << endl;
    KMPSearch(text, pattern);
    
    return 0;
}
