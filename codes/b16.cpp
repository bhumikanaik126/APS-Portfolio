#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> contentGraph;
unordered_set<string> visited;

void dfs(string node, int depth = 0) {
    if (visited.count(node)) return;
    visited.insert(node);

    // Indentation to visualize depth
    cout << string(depth * 2, '-') << node << endl;

    for (auto& neighbor : contentGraph[node]) {
        dfs(neighbor, depth + 1);
    }
}

int main() {
    // Sample content graph (related articles or videos)
    contentGraph["ML"] = {"Deep Learning", "NLP"};
    contentGraph["Deep Learning"] = {"CNNs", "RNNs"};
    contentGraph["NLP"] = {"Transformers", "BERT"};
    contentGraph["CNNs"] = {"ImageNet"};

    string start = "ML";
    cout << "Personalized content from: " << start << "\n";
    dfs(start);

    return 0;
}