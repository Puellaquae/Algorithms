// Telephone Lines
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct Edge {
    int To, Cost;
};
struct Point {
    int Distance, Index;
    bool operator<(const Point &b) const { return Distance > b.Distance; }
};
#ifndef INT_MAX
#    define INT_MAX 0x7fffffff
#endif
int Dijkstra(int Start, int Free, const vector<vector<Edge> > &G) {
    vector<int> Distance(G.size(), INT_MAX);
    Distance[Start] = 0;
    priority_queue<Point> Q;
    Q.push({0, Start});
    while (!Q.empty()) {
        Point p = Q.top();
        Q.pop();
        int Index = p.Index;
        if (Distance[Index] < p.Distance) {
            continue;
        }
        for (int i = 0; i < G[Index].size(); i++) {
            Edge e = G[Index][i];
            if (Distance[e.To] > Distance[Index] + (e.Cost >= Free ? 1 : 0)) {
                Distance[e.To] = Distance[Index] + (e.Cost >= Free ? 1 : 0);
                Q.push({Distance[e.To], e.To});
            }
        }
    }
    return Distance[Distance.size() - 1];
}
int main() {
    const int MAX_L = 1e6;
    int K, V, E;
    cin >> V >> E >> K;
    vector<vector<Edge> > G(V);
    for (int i = 0; i < E; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        G[from - 1].push_back({to - 1, cost});
        G[to - 1].push_back({from - 1, cost});
    }
    int lb = 0, ub = MAX_L + 2;
    while (ub - lb > 1) {
        int mid = (ub + lb) / 2;
        if (Dijkstra(0, mid, G) > K) {
            lb = mid;
        } else {
            ub = mid;
        }
    }
    cout << (lb > MAX_L ? -1 : lb) << endl;
}