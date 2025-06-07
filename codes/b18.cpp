#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum Direction { LEFT = -1, RIGHT = 1 };

struct Element {
    int value;
    Direction dir;
};

bool isMobile(const Element &e, const vector<Element> &perm) {
    int pos = find_if(perm.begin(), perm.end(), [&](const Element &x) { return x.value == e.value; }) - perm.begin();
    int next = pos + e.dir;
    return next >= 0 && next < perm.size() && e.value > perm[next].value;
}

int getLargestMobileIndex(const vector<Element> &perm) {
    int index = -1;
    int maxVal = -1;
    for (int i = 0; i < perm.size(); ++i) {
        if (isMobile(perm[i], perm) && perm[i].value > maxVal) {
            maxVal = perm[i].value;
            index = i;
        }
    }
    return index;
}

void printPermutation(const vector<Element> &perm) {
    for (auto &e : perm) cout << e.value << " ";
    cout << endl;
}

void generatePermutations(int n) {
    vector<Element> perm(n);
    for (int i = 0; i < n; ++i)
        perm[i] = {i + 1, LEFT};

    printPermutation(perm);

    while (true) {
        int mobileIndex = getLargestMobileIndex(perm);
        if (mobileIndex == -1) break;

        int swapWith = mobileIndex + perm[mobileIndex].dir;
        swap(perm[mobileIndex], perm[swapWith]);

        for (auto &e : perm)
            if (e.value > perm[swapWith].value)
                e.dir = (Direction)(-e.dir);

        printPermutation(perm);
    }
}
 
int main() {
    int n = 3; // Number of top-N items to permute
    generatePermutations(n);
    return 0;
}
