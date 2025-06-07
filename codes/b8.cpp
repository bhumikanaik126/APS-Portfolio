#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>

using namespace std;

struct Node {
    int id;
    double g; // cost from start
    double f; // total cost = g + h
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

double heuristic(int u, int v) {
    // Example: Euclidean distance or Haversine for GPS
    return abs(u - v); // Replace with actual GPS heuristic
}

vector<int> a_star(int start, int goal, unordered_map<int, vector<pair<int, double>>> &graph) {
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    unordered_map<int, double> gScore;
    unordered_map<int, int> cameFrom;

    gScore[start] = 0;
    openSet.push({start, 0, heuristic(start, goal)});

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.id == goal) {
            vector<int> path;
            while (cameFrom.count(current.id)) {
                path.push_back(current.id);
                current.id = cameFrom[current.id];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto& [neighbor, cost] : graph[current.id]) {
            double tentative_gScore = gScore[current.id] + cost;
            if (!gScore.count(neighbor) || tentative_gScore < gScore[neighbor]) {
                cameFrom[neighbor] = current.id;
                gScore[neighbor] = tentative_gScore;
                double fScore = tentative_gScore + heuristic(neighbor, goal);
                openSet.push({neighbor, tentative_gScore, fScore});
            }
        }
    }

    return {}; // No path found
}
