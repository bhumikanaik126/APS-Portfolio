#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<int> tree;
    int size;

public:
    FenwickTree(int n) {
        size = n;
        tree.resize(n + 1, 0); // 1-based indexing
    }

    void update(int index, int delta) {
        index++; // Convert to 1-based
        while (index <= size) {
            tree[index] += delta;
            index += index & -index;
        }
    }

    int prefixSum(int index) {
        index++; // Convert to 1-based
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }
};

int main() {
    FenwickTree clicks(6); // For 6 ads

    clicks.update(0, 2); // Ad 0 gets 2 clicks
    clicks.update(2, 3); // Ad 2 gets 3 clicks
    clicks.update(3, 7); // Ad 3 gets 7 clicks

    cout << "Total clicks for ads 0 to 3: " << clicks.prefixSum(3) << endl; // Should print 12

    return 0;
}
