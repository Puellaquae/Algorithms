// Roadblocks
// Using A Variety of Dijkstra, a algorithm of Second Shortest Path Problem
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct E {
    int End, Cost;
};

struct P {
    int first, second;
    bool operator<(const P &b) const { return first > b.first; }
};
const int INF = 0x0fffffff;

int D[5100];
int D2[5100];
vector<E> G[5100];
priority_queue<P> Q;
int main() {
    int N;
    cin >> N;
    int R;
    cin >> R;
    for (int i = 0; i < R; i++) {
        int Start, End, Cost;
        cin >> Start >> End >> Cost;
        G[Start - 1].push_back({End - 1, Cost});
        G[End - 1].push_back({Start - 1, Cost});
    }
    fill(D,D+N,INF);
    fill(D2,D2+N,INF);
    
    D[0] = 0;
    Q.push({0, 0});
    while (!Q.empty()) {
        P p = Q.top();
        Q.pop();
        int v = p.second, d = p.first;
        if (D2[v] < d) {
            continue;
        }
        for (int i = 0; i < G[v].size(); i++) {
            E &e = G[v][i];
            int d2 = d + e.Cost;
            if (D[e.End] > d2) {
                swap(D[e.End], d2);
                Q.push({D[e.End], e.End});
            }
            if (D2[e.End] > d2 && D[e.End] < d2) {
                D2[e.End] = d2;
                Q.push({D2[e.End], e.End});
            }
        }
    }
    cout << D2[N-1] << endl;
}