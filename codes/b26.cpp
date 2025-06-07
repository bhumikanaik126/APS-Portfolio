#include <iostream>
using namespace std;

// Fast modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) 
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Using Fermat's Little Theorem to reduce exponent
long long fermatModExp(long long a, long long b, long long p) {
    // p must be prime
    long long reducedExp = b % (p - 1);
    return modExp(a, reducedExp, p);
}

int main() {
    long long a = 3, b = 1000, p = 7;
    cout << fermatModExp(a, b, p) << endl; // Output: 4
    return 0;
}
