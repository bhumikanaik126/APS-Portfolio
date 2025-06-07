#include <iostream>
#include <cmath>

// Function to calculate factorial (can be memoized for performance)
double factorial(int n) {
    if (n == 0) return 1.0;
    double result = 1.0;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

// Function to calculate Poisson PMF
double poissonProbability(int observed, double lambda) {
    return pow(lambda, observed) * exp(-lambda) / factorial(observed);
}

int main() {
    // Expected reviews per hour for a normal user
    double lambda = 1.0;

    // Observed number of reviews in a given hour
    int observed = 15;

    double p = poissonProbability(observed, lambda);

    std::cout << "P(X = " << observed << ") = " << p << std::endl;

    if (p < 0.001) {
        std::cout << "⚠️ Suspicious activity: Possible fake reviewer or bot detected." << std::endl;
    } else {
        std::cout << "✅ Review pattern within normal range." << std::endl;
    }

    return 0;
}
