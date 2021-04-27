// ROADS

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct Content {
    int had_length, last_coin, cur_pos;
};
struct Road {
    int dest, length, cost;
};
int main() {
    int K, N, R;
    cin >> K >> N >> R;
    vector<vector<Road> > roads(N);
    for (int i = 0, S, D, L, T; i < R; i++) {
        cin >> S >> D >> L >> T;
        roads[S - 1].push_back(Road{D - 1, L, T});
    }
    queue<Content> Q;
    int min_length = 0x7fffffff;
    bool achieved = false;
    Q.push(Content{0, K, 0});
    while (!Q.empty()) {
        Content c = Q.front();
        Q.pop();
        if (c.last_coin < 0) {
            continue;
        }
        if (c.cur_pos == N - 1) {
            achieved = true;
            min_length = min(c.had_length, min_length);
        }
        if (c.had_length >= min_length) {
            continue;
        }
        for (vector<Road>::iterator r = roads[c.cur_pos].begin();
             r != roads[c.cur_pos].end(); ++r) {
            Q.push(Content{c.had_length + r->length, c.last_coin - r->cost,
                              r->dest});
        }
    }
    if (achieved && min_length != 0x7fffffff) {
        cout << min_length << endl;
    } else {
        cout << -1 << endl;
    }
}