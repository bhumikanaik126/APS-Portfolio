#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    int weight;
};

struct DisjointSet {
    vector<int> parent, rank;
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i=0; i<n; i++) parent[i] = i;
    }
    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if(rx != ry) {
            if(rank[rx] < rank[ry]) parent[rx] = ry;
            else if(rank[ry] < rank[rx]) parent[ry] = rx;
            else {
                parent[ry] = rx;
                rank[rx]++;
            }
        }
    }
};

int boruvkaMST(int V, vector<Edge> &edges) {
    DisjointSet ds(V);
    int components = V;
    int mst_weight = 0;

    vector<int> cheapest(V, -1);

    while(components > 1) {
        // Initialize cheapest edges for each component
        fill(cheapest.begin(), cheapest.end(), -1);

        // Find cheapest outgoing edge for each component
        for(int i = 0; i < (int)edges.size(); i++) {
            int u = ds.find(edges[i].u);
            int v = ds.find(edges[i].v);
            if(u == v) continue;

            if(cheapest[u] == -1 || edges[i].weight < edges[cheapest[u]].weight)
                cheapest[u] = i;
            if(cheapest[v] == -1 || edges[i].weight < edges[cheapest[v]].weight)
                cheapest[v] = i;
        }

        // Add the cheapest edges to MST and merge components
        for(int i=0; i<V; i++) {
            int edgeIdx = cheapest[i];
            if(edgeIdx != -1) {
                int u = ds.find(edges[edgeIdx].u);
                int v = ds.find(edges[edgeIdx].v);
                if(u != v) {
                    ds.unite(u, v);
                    mst_weight += edges[edgeIdx].weight;
                    components--;
                }
            }
        }
    }
    return mst_weight;
}

int main() {
    int V = 4; // Number of data centers
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    cout << "Minimum Cable Length to connect all data centers: " << boruvkaMST(V, edges) << endl;

    return 0;
}
