#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;

void dijkstra(int start, vector<vector<pair<int, int>>> &adj, vector<int> &dist) {
    int n = adj.size();
    dist.assign(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto &[v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n = 5;
    vector<vector<pair<int, int>>> adj(n);

    // Add edges: (from, to, weight)
    adj[0].push_back({1, 2}); // A → B
    adj[0].push_back({2, 4}); // A → C
    adj[1].push_back({3, 1}); // B → D
    adj[2].push_back({1, 3}); // C → B

    vector<int> dist;
    dijkstra(0, adj, dist); // Run from A

    for (int i = 0; i < n; ++i)
        cout << "Distance from A to " << char('A' + i) << ": " << dist[i] << "\n";

    return 0;
}
