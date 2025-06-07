#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

typedef pair<int, double> Edge;

vector<int> uniform_cost_search(int start, int goal, unordered_map<int, vector<Edge>> &graph) {
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
    unordered_map<int, double> dist;
    unordered_map<int, int> cameFrom;

    for (auto &node : graph) {
        dist[node.first] = numeric_limits<double>::infinity();
    }

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [cost, u] = pq.top(); pq.pop();
        if (u == goal) break;

        for (auto &[v, weight] : graph[u]) {
            double new_cost = dist[u] + weight;
            if (new_cost < dist[v]) {
                dist[v] = new_cost;
                cameFrom[v] = u;
                pq.push({new_cost, v});
            }
        }
    }

    vector<int> path;
    if (!cameFrom.count(g
