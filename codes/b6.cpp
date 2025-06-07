#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct AdBid {
    int id;
    double bidAmount;
    double relevance;
    
    double score() const {
        return bidAmount * relevance;
    }

    bool operator<(const AdBid& other) const {
        return score() < other.score(); // Max-heap
    }
};

int main() {
    priority_queue<AdBid> pq;

    pq.push({1, 5.0, 0.7});
    pq.push({2, 4.0, 1.0});
    pq.push({3, 6.0, 0.5});

    AdBid winner = pq.top(); pq.pop();
    AdBid second = pq.top(); // For second-price

    cout << "Ad " << winner.id << " wins and pays: " << second.score() << endl;
    return 0;
}
