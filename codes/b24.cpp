#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v, weight;
};

bool bellmanFord(int V, int E, vector<Edge> &edges, int src, vector<int> &dist) {
    dist.assign(V, 1e9);
    dist[src] = 0;

    for(int i = 0; i < V - 1; i++) {
        for(auto &edge : edges) {
            if(dist[edge.u] != 1e9 && dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
            }
        }
    }

    // Check for negative weight cycles
    for(auto &edge : edges) {
        if(dist[edge.u] != 1e9 && dist[edge.u] + edge.weight < dist[edge.v]) {
            return false; // Negative cycle detected
        }
    }
    return true;
}

int main() {
    int V = 5, E = 8;
    vector<Edge> edges = {
        {0,1,6},{0,3,7},{1,2,5},{1,3,8},{1,4,-4},
        {2,1,-2},{3,2,-3},{4,2,7},{4,0,2}
    };

    vector<int> dist;
    bool noNegativeCycle = bellmanFord(V, E, edges, 0, dist);

    if(noNegativeCycle) {
        cout << "Shortest distances from source 0:\n";
        for(int i = 0; i < V; i++) {
            cout << "Vertex " << i << ": " << dist[i] << "\n";
        }
    } else {
        cout << "Graph contains a negative weight cycle\n";
    }
    return 0;
}
