#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
using namespace std;

// Graph representation: video/user nodes and their connections
unordered_map<string, vector<string>> graph;

// BFS to suggest nearby videos
vector<string> suggestVideos(string startVideo, int maxDepth) {
    queue<pair<string, int>> q;
    set<string> visited;
    vector<string> suggestions;

    q.push({startVideo, 0});
    visited.insert(startVideo);

    while (!q.empty()) {
        auto [node, depth] = q.front(); q.pop();

        if (depth > 0 && node.find("Video") != string::npos)
            suggestions.push_back(node);

        if (depth >= maxDepth) continue;

        for (string neighbor : graph[node]) {
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                q.push({neighbor, depth + 1});
            }
        }
    }

    return suggestions;
}

int main() {
    // Sample graph setup
    graph["VideoA"] = {"User1", "User2"};
    graph["User1"] = {"VideoA", "VideoB"};
    graph["User2"] = {"VideoA", "VideoC"};

    vector<string> result = suggestVideos("VideoA", 2);

    cout << "Suggested videos:\n";
    for (string v : result)
        cout << v << endl;

    return 0;
}