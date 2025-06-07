#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int sum;
    Node *left, *right;

    Node(int val = 0) : sum(val), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r) : left(l), right(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

class PersistentSegmentTree {
private:
    int n;
    vector<Node*> versions;

    Node* build(int start, int end) {
        if (start == end) return new Node(0);
        int mid = (start + end) / 2;
        return new Node(build(start, mid), build(mid + 1, end));
    }

    Node* update(Node* node, int start, int end, int idx, int val) {
        if (start == end) return new Node(node->sum + val);
        int mid = (start + end) / 2;
        if (idx <= mid) {
            return new Node(update(node->left, start, mid, idx, val), node->right);
        } else {
            return new Node(node->left, update(node->right, mid + 1, end, idx, val));
        }
    }

    int query(Node* node, int start, int end, int l, int r) {
        if (r < start || end < l || !node) return 0;
        if (l <= start && end <= r) return node->sum;
        int mid = (start + end) / 2;
        return query(node->left, start, mid, l, r) + query(node->right, mid + 1, end, l, r);
    }

public:
    PersistentSegmentTree(int size) : n(size) {
        versions.push_back(build(0, n - 1));  // version 0, all zeros initially
    }

    // Create a new version with update at idx by val
    void update(int versionIdx, int idx, int val) {
        Node* newVersion = update(versions[versionIdx], 0, n - 1, idx, val);
        versions.push_back(newVersion);
    }

    // Query sum in range [l, r] for version ver
    int query(int ver, int l, int r) {
        return query(versions[ver], 0, n - 1, l, r);
    }

    int getVersionCount() {
        return (int)versions.size();
    }
};

int main() {
    int n = 6;  // number of road segments or ads, for example
    PersistentSegmentTree pst(n);

    // Initial traffic speeds at time 0
    pst.update(0, 0, 5);  // Segment 0 speed = 5
    pst.update(1, 3, 7);  // Segment 3 speed = 7 (new version)
    pst.update(2, 5, 3);  // Segment 5 speed = 3 (new version)

    // Query segment speed sums at different versions (times)
    cout << "Version 0, sum [0..5]: " << pst.query(0, 0, 5) << "\n"; // Output traffic speed sum at initial time
    cout << "Version 1, sum [0..5]: " << pst.query(1, 0, 5) << "\n";
    cout << "Version 2, sum [0..5]: " << pst.query(2, 0, 5) << "\n";

    // Query specific segment range at version 2
    cout << "Version 2, sum [3..5]: " << pst.query(2, 3, 5) << "\n";

    return 0;
}
