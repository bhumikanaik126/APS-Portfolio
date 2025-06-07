#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

struct Query {
    int L, R, idx;
};

int BLOCK_SIZE;

bool compare(Query a, Query b) {
    int block_a = a.L / BLOCK_SIZE;
    int block_b = b.L / BLOCK_SIZE;
    if (block_a == block_b)
        return a.R < b.R;
    return block_a < block_b;
}

vector<int> processQueries(vector<int>& reviews, vector<Query>& queries, int targetRating) {
    BLOCK_SIZE = sqrt(reviews.size());
    sort(queries.begin(), queries.end(), compare);

    vector<int> answers(queries.size());
    unordered_map<int, int> freq;

    int currentL = 0, currentR = -1;
    int count = 0;

    for (Query q : queries) {
        while (currentL > q.L) {
            currentL--;
            freq[reviews[currentL]]++;
            if (reviews[currentL] == targetRating) count++;
        }
        while (currentR < q.R) {
            currentR++;
            freq[reviews[currentR]]++;
            if (reviews[currentR] == targetRating) count++;
        }
        while (currentL < q.L) {
            if (reviews[currentL] == targetRating) count--;
            freq[reviews[currentL]]--;
            currentL++;
        }
        while (currentR > q.R) {
            if (reviews[currentR] == targetRating) count--;
            freq[reviews[currentR]]--;
            currentR--;
        }

        answers[q.idx] = count;
    }

    return answers;
}

int main() {
    vector<int> reviews = {5, 4, 5, 1, 5, 2, 5, 3, 5, 5};  // 1-min spaced reviews
    vector<Query> queries = {
        {0, 4, 0},  // Query 1: time 0–4
        {3, 8, 1},  // Query 2: time 3–8
        {2, 9, 2}   // Query 3: time 2–9
    };

    int targetRating = 5;  // looking for suspicious 5-star floods

    vector<int> results = processQueries(reviews, queries, targetRating);

    for (int i = 0; i < results.size(); ++i)
        cout << "Query " << i + 1 << " → " << results[i] << " suspicious reviews" << endl;

    return 0;
}
