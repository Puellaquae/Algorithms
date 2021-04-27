// Going Home

/**************/
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
const int MAXN = 100000;
const int INF = 0x7fffffff;
#define SZ(v) (int)v.size()

struct MCMF {
    struct Edge {
        int v, cap, cost, rev;
    };

    int flow, cost, s, t, n;
    int dist[MAXN], H[MAXN], pv[MAXN], pe[MAXN];
    std::vector<Edge> G[MAXN];

    bool dijkstra() {
        typedef std::pair<int, int> pii;
        std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
        std::fill(dist, dist + n + 1, INF);
        dist[s] = 0;
        q.push({0, s});
        while (!q.empty()) {
            pii x = q.top();
            q.pop();
            int &u = x.second;
            if (dist[u] < x.first)
                continue;
            for (int i = 0; i < SZ(G[u]); ++i) {
                Edge &e = G[u][i];
                int &v = e.v;
                pii y(dist[u] + e.cost + H[u] - H[v], v);
                if (e.cap > 0 && dist[v] > y.first) {
                    dist[v] = y.first;
                    pe[v] = i, pv[v] = u;
                    q.push(y);
                }
            }
        }

        if (dist[t] == INF)
            return false;
        for (int i = 0; i <= n; ++i)
            H[i] += dist[i];

        int f = INF;
        for (int v = t; v != s; v = pv[v])
            f = std::min(f, G[pv[v]][pe[v]].cap);

        flow += f;
        cost += f * H[t];

        for (int v = t; v != s; v = pv[v]) {
            Edge &e = G[pv[v]][pe[v]];
            e.cap -= f;
            G[v][e.rev].cap += f;
        }

        return true;
    }

    void solve(int s, int t) {
        this->s = s, this->t = t;
        flow = cost = 0;
        std::fill(H, H + n + 1, 0);
        while (dijkstra())
            ;
    }

    void init(int n) {
        this->n = n;
        for (int i = 0; i <= n; ++i)
            G[i].clear();
    }

    void addEdge(int u, int v, int cap, int cost) {
        G[u].push_back({v, cap, cost, SZ(G[v])});
        G[v].push_back({u, 0, -cost, SZ(G[u]) - 1});
    }

} mcmf;
/****************/
using namespace std;
struct Point {
    int x, y;
};
vector<Point> house;
vector<Point> man;
int main() {
    int N, M;
    char buf[255];
    while (scanf("%d%d", &N, &M)) {
        house.clear();
        man.clear();
        if (N == 0 && M == 0) {
            break;
        }
        for (int _x = 0; _x < N; _x++) {
            scanf("%s", buf);
            for (int _y = 0; _y < M; _y++) {
                if (buf[_y] == 'H') {
                    house.push_back(Point{_x, _y + 1});
                } else if (buf[_y] == 'm') {
                    man.push_back(Point{_x, _y + 1});
                }
            }
        }
        int housec = SZ(house);
        int manc = SZ(man);
        mcmf.init(N * M + 3);
        int start = N * M + 1, target = start + 1;
        for (int i = 0; i < manc; i++) {
            mcmf.addEdge(start, man[i].x * M + man[i].y, 1, 0);
        }
        for (int i = 0; i < housec; i++) {
            mcmf.addEdge(house[i].x * M + house[i].y, target, 1, 0);
        }
        for (int i = 0; i < manc; i++) {
            for (int j = 0; j < housec; j++) {
                mcmf.addEdge(
                    man[i].x * M + man[i].y, house[j].x * M + house[j].y, 1,
                    abs(man[i].x - house[j].x) + abs(man[i].y - house[j].y));
            }
        }
        mcmf.solve(start, target);
        printf("%d\n", mcmf.cost);
    }
}