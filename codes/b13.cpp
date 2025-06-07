#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Check if a given review has a valid balanced structure
bool isBalanced(const string& review) {
    stack<char> s;
    for (char ch : review) {
        if (ch == '(') s.push(ch);
        else if (ch == ')') {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

// Catalan Number calculator (n-th Catalan number)
long long catalan(int n) {
    if (n == 0) return 1;
    long long res = 0;
    for (int i = 0; i < n; ++i)
        res += catalan(i) * catalan(n - 1 - i);
    return res;
}

int main() {
    string review1 = "(good (food and service))";  // Balanced
    string review2 = "((great (value) and friendly)";  // Unbalanced

    cout << "Review 1 is " << (isBalanced(review1) ? "Balanced" : "Unbalanced") << endl;
    cout << "Review 2 is " << (isBalanced(review2) ? "Balanced" : "Unbalanced") << endl;

    // Show Catalan numbers for insight
    cout << "\nCatalan numbers for parse tree possibilities (0–5):\n";
    for (int i = 0; i <= 5; ++i)
        cout << "C(" << i << ") = " << catalan(i) << endl;

    return 0;
}
