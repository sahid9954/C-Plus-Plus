/**
 * @file
 * @brief Implementation of the [Knuth-Morris-Pratt (KMP) String Matching Algorithm](https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm).
 * @details
 * The KMP algorithm searches for occurrences of a word (pattern) within a main text string. 
 * It preprocesses the pattern to create a Longest Prefix Suffix (LPS) array that helps avoid unnecessary character comparisons.
 * The time complexity is O(n + m), where `n` is the length of the text and `m` is the length of the pattern.
 *
 * @author [Your Name](https://github.com/your_handle)
 * @see other_algorithms.cpp
 */

#include <iostream>   /// for IO operations
#include <vector>     /// for std::vector
#include <cassert>    /// for assert

/**
 * @namespace string_search
 * @brief String search algorithms
 */
namespace string_search {

/**
 * @brief Preprocesses the pattern to create the LPS array.
 * @param pattern The pattern for which the LPS array is calculated.
 * @returns The LPS array.
 */
std::vector<int> computeLPSArray(const std::string &pattern) {
    int m = pattern.size();
    std::vector<int> lps(m, 0);  ///< Initialize LPS array
    int length = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

/**
 * @brief KMP Algorithm to search for a pattern in a given text.
 * @param text The main text string in which the pattern is searched.
 * @param pattern The pattern to search for within the text.
 * @returns `true` if the pattern is found in the text, otherwise `false`.
 */
bool KMP_Search(const std::string &text, const std::string &pattern) {
    int n = text.size();
    int m = pattern.size();

    if (m == 0) return false;  ///< Return false if pattern is empty

    std::vector<int> lps = computeLPSArray(pattern);

    int i = 0;  // index for text[]
    int j = 0;  // index for pattern[]

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            return true;  ///< Pattern found in text
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return false;  ///< Pattern not found
}
}  // namespace string_search

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // Test cases
    std::string text1 = "ababcabcabababd";
    std::string pattern1 = "ababd";
    assert(string_search::KMP_Search(text1, pattern1) == true);  // Expected: true

    std::string text2 = "hello_world";
    std::string pattern2 = "planet";
    assert(string_search::KMP_Search(text2, pattern2) == false);  // Expected: false

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    return 0;
}
