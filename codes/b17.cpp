#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// Suppose each app covers some categories (bitmask), and has a score
struct App {
    int mask;
    int score;
};

int minAppsToCoverAll(int n, vector<App>& apps) {
    int full = (1 << n) - 1;
    vector<int> dp(1 << n, INF);
    dp[0] = 0;

    for (auto& app : apps) {
        vector<int> new_dp = dp;
        for (int mask = 0; mask <= full; ++mask) {
            int new_mask = mask | app.mask;
            new_dp[new_mask] = min(new_dp[new_mask], dp[mask] + 1);
        }
        dp = new_dp;
    }

    return (dp[full] == INF) ? -1 : dp[full];
}

int main() {
    // Categories: {Productivity, Social, Finance}
    int n = 3;

    vector<App> apps = {
        {0b001, 5},   // Covers Finance
        {0b010, 3},   // Covers Social
        {0b100, 4},   // Covers Productivity
        {0b110, 6},   // Covers Social + Productivity
    };

    int result = minAppsToCoverAll(n, apps);
    if (result != -1)
        cout << "Minimum apps needed: " << result << endl;
    else
        cout << "Cannot cover all categories.\n";
    return 0;
}
