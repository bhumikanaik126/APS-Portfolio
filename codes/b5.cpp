#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(int budget, vector<int>& cost, vector<int>& value) {
    int n = cost.size();
    vector<vector<int>> dp(n+1, vector<int>(budget+1, 0));

    for (int i = 1; i <= n; i++) {
        for (int b = 0; b <= budget; b++) {
            if (cost[i-1] <= b)
                dp[i][b] = max(dp[i-1][b], value[i-1] + dp[i-1][b - cost[i-1]]);
            else
                dp[i][b] = dp[i-1][b];
        }
    }
    return dp[n][budget];
}

int main() {
    vector<int> cost = {4, 2, 3};      // Cost to show each ad
    vector<int> value = {10, 4, 7};    // Expected revenue/CTR
    int budget = 5;

    cout << "Max Revenue: " << knapsack(budget, cost, value) << endl;
    return 0;
}
