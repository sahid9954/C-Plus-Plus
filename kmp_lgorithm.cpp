#include <iostream>
#include <vector>
using namespace std;

// Function to create LPS (Longest Prefix Suffix) array
vector<int> computeLPSArray(const string &pattern) {
    int m = pattern.length();
    vector<int> lps(m);
    int length = 0;  // length of the previous longest prefix suffix
    int i = 1;
    lps[0] = 0;  // lps[0] is always 0
    
    // Build the lps array
    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];  // Try matching with previous lps
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// Function to perform KMP search
void KMPSearch(const string &text, const string &pattern) {
    int n = text.length();
    int m = pattern.length();
    
    // Preprocess the pattern (calculate lps array)
    vector<int> lps = computeLPSArray(pattern);
    
    int i = 0;  // index for text
    int j = 0;  // index for pattern
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        
        if (j == m) {  // found a match
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];  // Reset j using the lps array
        } else if (i < n && pattern[j] != text[i]) {  // mismatch after j matches
            if (j != 0) {
                j = lps[j - 1];  // Use the lps array to skip unnecessary comparisons
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    
    KMPSearch(text, pattern);
    
    return 0;
}
