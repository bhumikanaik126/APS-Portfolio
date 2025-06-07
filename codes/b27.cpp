#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;

    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node + 1, mid+1, end);
            tree[node] = tree[2*node] + tree[2*node + 1];  // Sum operation
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return 0;  // Outside range
        if (l <= start && end <= r) return tree[node];  // Fully inside
        int mid = (start + end) / 2;
        int p1 = query(2*node, start, mid, l, r);
        int p2 = query(2*node + 1, mid+1, end, l, r);
        return p1 + p2;
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) update(2*node, start, mid, idx, val);
            else update(2*node + 1, mid+1, end, idx, val);
            tree[node] = tree[2*node] + tree[2*node + 1];
        }
    }

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4*n);
        build(arr, 1, 0, n-1);
    }

    int query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }

    void update(int idx, int val) {
        update(1, 0, n-1, idx, val);
    }
};

int main() {
    vector<int> data = {2, 5, 1, 4, 9, 3};
    SegmentTree segTree(data);

    cout << "Sum of values in range [1, 4]: " << segTree.query(1, 4) << endl;

    segTree.update(3, 6); // Update index 3 to value 6
    cout << "After update, sum of values in range [1, 4]: " << segTree.query(1, 4) << endl;

    return 0;
}
