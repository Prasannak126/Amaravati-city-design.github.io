void computeLPSArray(string pattern, vector<int>& lps) {
    int len = 0, i = 1;
    lps[0] = 0;

    while (i < pattern.size()) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else if (len) {
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }
}
