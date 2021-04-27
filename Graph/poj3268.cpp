// Sliver Cow Party
// Using Dijkstra
#include <iostream>
#include <queue>
#include <vector>

struct edge {
    int To, Cost;
};

struct P {
    int Distance, Index;
    bool operator<(const P &b) const { return Distance > b.Distance; }
};

const int INF = 0x3f3f3f3f;

using namespace std;

vector<int> Dijkstra(int Start, const vector<vector<edge> > &G) {
    vector<int> D(G.size(), INF);
    D[Start] = 0;
    priority_queue<P> Q;
    Q.push({0, Start});
    while (!Q.empty()) {
        P p = Q.top();
        Q.pop();
        int v = p.Index;
        if (D[v] < p.Distance) {
            continue;
        }
        for (int i = 0; i < G[v].size(); i++) {
            edge e = G[v][i];
            if (D[e.To] > D[v] + e.Cost) {
                D[e.To] = D[v] + e.Cost;
                Q.push({D[e.To], e.To});
            }
        }
    }
    return D;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int N, M, X;
    cin >> N >> M >> X;
    X--;
    vector<vector<edge> > Go(N, vector<edge>());
    vector<vector<edge> > Back(N, vector<edge>());
    for (int i = 0; i < M; i++) {
        int A, B, T;
        cin >> A >> B >> T;
        A--;
        B--;
        Go[A].push_back({B, T});
        Back[B].push_back({A, T});
    }
    vector<int> GD = Dijkstra(X, Go);
    vector<int> BD = Dijkstra(X, Back);
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (i != X && ans < GD[i] + BD[i]) {
            ans = GD[i] + BD[i];
        }
    }
    cout << ans << endl;
}