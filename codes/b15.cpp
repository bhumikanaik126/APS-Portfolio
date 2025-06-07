#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

const double DAMPING = 0.85;
const int MAX_ITER = 100;
const double EPSILON = 1e-6;

vector<double> computePageRank(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<double> rank(n, 1.0 / n);
    vector<double> newRank(n, 0.0);

    for (int iter = 0; iter < MAX_ITER; ++iter) {
        for (int i = 0; i < n; ++i) {
            newRank[i] = (1 - DAMPING) / n;
        }

        for (int i = 0; i < n; ++i) {
            int outDegree = graph[i].size();
            if (outDegree == 0) {
                // Distribute rank evenly if no out-links
                for (int j = 0; j < n; ++j)
                    newRank[j] += DAMPING * rank[i] / n;
            } else {
                for (int neighbor : graph[i]) {
                    newRank[neighbor] += DAMPING * rank[i] / outDegree;
                }
            }
        }

        double diff = 0;
        for (int i = 0; i < n; ++i) {
            diff += abs(newRank[i] - rank[i]);
            rank[i] = newRank[i];
        }
        if (diff < EPSILON) break;
    }
    return rank;
}

int main() {
    // Example graph: 3 pages
    // 0 -> 1, 2
    // 1 -> 2
    // 2 -> 0
    vector<vector<int>> graph = {{1, 2}, {2}, {0}};

    vector<double> ranks = computePageRank(graph);

    cout << "PageRank scores:\n";
    for (int i = 0; i < (int)ranks.size(); ++i)
        cout << "Page " << i << ": " << ranks[i] << "\n";

    return 0;
}
