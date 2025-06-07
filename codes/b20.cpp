#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct Point {
    double x, y; // latitude, longitude
    int id; // place ID
};

struct Node {
    Point point;
    Node *left, *right;
    Node(Point pt) : point(pt), left(nullptr), right(nullptr) {}
};

bool cmpX(const Point &a, const Point &b) { return a.x < b.x; }
bool cmpY(const Point &a, const Point &b) { return a.y < b.y; }

Node* buildKDTree(vector<Point> &points, int depth = 0) {
    if (points.empty()) return nullptr;

    int axis = depth % 2; // 0 for x, 1 for y
    int mid = points.size() / 2;

    if (axis == 0)
        nth_element(points.begin(), points.begin() + mid, points.end(), cmpX);
    else
        nth_element(points.begin(), points.begin() + mid, points.end(), cmpY);

    Node* root = new Node(points[mid]);

    vector<Point> leftPoints(points.begin(), points.begin() + mid);
    vector<Point> rightPoints(points.begin() + mid + 1, points.end());

    root->left = buildKDTree(leftPoints, depth + 1);
    root->right = buildKDTree(rightPoints, depth + 1);

    return root;
}

double distance(const Point &a, const Point &b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

void nearestNeighbor(Node* root, const Point &target, int depth, Point &best, double &bestDist) {
    if (!root) return;

    double d = distance(root->point, target);
    if (d < bestDist) {
        bestDist = d;
        best = root->point;
    }

    int axis = depth % 2;
    Node* nextBranch = nullptr;
    Node* otherBranch = nullptr;

    if ((axis == 0 && target.x < root->point.x) || (axis == 1 && target.y < root->point.y)) {
        nextBranch = root->left;
        otherBranch = root->right;
    } else {
        nextBranch = root->right;
        otherBranch = root->left;
    }

    nearestNeighbor(nextBranch, target, depth + 1, best, bestDist);

    double diff = (axis == 0) ? abs(target.x - root->point.x) : abs(target.y - root->point.y);
    if (diff < bestDist) {
        nearestNeighbor(otherBranch, target, depth + 1, best, bestDist);
    }
}

int main() {
    vector<Point> places = {
        {37.7749, -122.4194, 1}, // San Francisco
        {34.0522, -118.2437, 2}, // Los Angeles
        {40.7128, -74.0060, 3},  // New York
        {47.6062, -122.3321, 4}  // Seattle
    };

    Node* root = buildKDTree(places);

    Point userLoc = {36.0, -121.0, -1};
    Point best = {0,0,-1};
    double bestDist = numeric_limits<double>::max();

    nearestNeighbor(root, userLoc, 0, best, bestDist);

    cout << "Nearest place ID: " << best.id << " at distance " << bestDist << "\n";
    return 0;
}
