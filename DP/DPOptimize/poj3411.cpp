// Paid Roads

#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
const int MAXN = 12;
struct Road {
    int a, b, c, P, R;
};
vector<Road> roads[MAXN];
bool vis[MAXN][1 << MAXN];
struct State {
    int curPos, cost, visCityMask;
    bool operator>(const State &o) const {
        return cost > o.cost;
    }
};
int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i = 0, a, b, c, P, R; i < M; i++) {
        scanf("%d%d%d%d%d", &a, &b, &c, &P, &R);
        roads[a].push_back(Road{a, b, c, P, R});
    }
    priority_queue<State, vector<State>,
                   greater<State> >
        q;
    q.push(State{1, 0, 1 << 1});
    memset(vis, 0, sizeof vis);
    State res{-1, -1, -1};
    while (!q.empty()) {
        State p = q.top();
        q.pop();
        if (vis[p.curPos][p.visCityMask])
            continue;
        vis[p.curPos][p.visCityMask] = true;
        if (p.curPos == N) {
            res = p;
            break;
        }
        for (vector<Road>::iterator it =
                 roads[p.curPos].begin();
             it != roads[p.curPos].end(); it++) {
            int cost = p.cost;
            if (p.visCityMask & (1 << it->c)) {
                cost += min(it->P, it->R);
            } else {
                cost += it->R;
            }
            q.push(
                State{it->b, cost,
                      p.visCityMask | (1 << it->b)});
        }
    }
    if (res.curPos == -1) {
        printf("impossible\n");
    } else {
        printf("%d\n", res.cost);
    }
    return 0;
}