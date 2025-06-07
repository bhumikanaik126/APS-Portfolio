#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string string1 = "AGGTAB";
    string string2 = "GXTXAYB";
    int m = string1.size();
    int n = string2.size();

    // Create DP table
    vector<vector<int>> A(m + 1, vector<int>(n + 1, 0));

    // Build the memo table in bottom-up manner
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                A[i][j] = 0;
            } else if (string1[i - 1] == string2[j - 1]) {
                A[i][j] = A[i - 1][j - 1] + 1;
            } else {
                A[i][j] = max(A[i - 1][j], A[i][j - 1]);
            }
        }
    }

    // Reconstruct the LCS string from the DP table
    int i = m, j = n;
    string finalString = "";
    while (i > 0 && j > 0) {
        if (string1[i - 1] == string2[j - 1]) {
            finalString = string1[i - 1] + finalString;
            i--;
            j--;
        } else if (A[i - 1][j] > A[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Output the results
    cout << "Longest Common Subsequence Length is " << A[m][n] << endl;
    cout << "Longest Common Subsequence is " << finalString << endl;

    return 0;
}
