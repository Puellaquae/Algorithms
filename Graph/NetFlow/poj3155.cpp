// Hard Life

/**********/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
namespace Dinic {
using namespace std;
const int MAXN = 305;
const int MAXM = 10005;
const double DINF = 1e18;
const double EPS = 1e-8;
const int INF = 0x7fffffff;

int n, s, t, tot;
struct Node {
    int u, v;
    double cap, flow;
} node[MAXM << 1];
vector<int> E[MAXN];

void init(int _n) {
    for (int i = 0; i <= _n; i++) {
        E[i].clear();
    }
    tot = 0;
}

void addEdge(int u, int v, double w) {
    node[tot++] = Node{u, v, w, 0};
    node[tot++] = Node{v, u, 0, 0};
    E[u].push_back(tot - 2);
    E[v].push_back(tot - 1);
}

bool vis[MAXN];
int step[MAXN];
bool bfs(int _s, int _t) {
    queue<int> q;
    memset(vis, 0, sizeof vis);
    q.push(_s);
    vis[_s] = true;
    step[_s] = 0;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0; i < (int)E[now].size(); i++) {
            int it = E[now][i];
            if (vis[node[it].v])
                continue;
            if (node[it].cap <= node[it].flow + EPS)
                continue;
            q.push(node[it].v);
            vis[node[it].v] = true;
            step[node[it].v] = step[now] + 1;
        }
    }
    return vis[_t];
}

int cur[MAXN];
double dfs(int now, double limit) {
    if (limit < EPS || now == t)
        return limit;
    double res = 0.;
    for (int &i = cur[now]; i < (int)E[now].size();
         i++) {
        Node &it = node[E[now][i]];
        if (step[it.v] != step[now] + 1)
            continue;
        double flow =
            dfs(it.v, min(limit, it.cap - it.flow));
        if (flow < EPS) {
            continue;
        }
        it.flow += flow;
        node[E[now][i] ^ 1].flow -= flow;
        res += flow;
        limit -= flow;
        if (limit < EPS)
            break;
    }
    return res;
}

double dinic() {
    double ans = 0.;
    while (bfs(s, t)) {
        memset(cur, 0, sizeof cur);
        ans += dfs(s, DINF);
    }
    return ans;
}

vector<int> cnt;
void cnt_dfs(int now) {
    vis[now] = true;
    for (int i = 0; i < (int)E[now].size(); i++) {
        if (node[E[now][i]].flow <
                node[E[now][i]].cap &&
            !vis[node[E[now][i]].v]) {
            cnt_dfs(node[E[now][i]].v);
            cnt.push_back(node[E[now][i]].v);
        }
    }
}

void search() {
    memset(vis, 0, sizeof vis);
    cnt.clear();
    cnt_dfs(s);
    printf("%d\n", (int)cnt.size());
    sort(cnt.begin(), cnt.end());
    for (int i = 0; i < (int)cnt.size(); i++) {
        printf("%d\n", cnt[i]);
    }
}
} // namespace Dinic

/**********/

const int MAXN = 1005;
int u[MAXN], v[MAXN], du[MAXN];
void graph(int n, int m, double mid) {
    Dinic::init(n + 2);
    int s = Dinic::s = n + 1;
    int t = Dinic::t = n + 2;

    for (int i = 1; i <= n; i++) {
        Dinic::addEdge(s, i, m);
    }
    for (int i = 1; i <= n; i++) {
        Dinic::addEdge(i, t, m + (2 * mid - du[i]));
    }
    for (int i = 1; i <= m; i++) {
        Dinic::addEdge(u[i], v[i], 1);
        Dinic::addEdge(v[i], u[i], 1);
    }
}

int main() {
    int N, M;
    while (~scanf("%d%d", &N, &M)) {
        memset(du, 0, sizeof du);
        for (int i = 1; i <= M; i++) {
            scanf("%d%d", u + i, v + i);
            du[v[i]]++;
            du[u[i]]++;
        }
        if (M == 0) {
            printf("1\n1\n");
            return 0;
        }

        double left = 1. / N, right = M, mid;
        double eps = 1. / N / M;
        while (left + eps < right) {
            mid = (left + right) / 2.;
            graph(N, M, mid);
            double res = (N * M - Dinic::dinic()) / 2.;
            if (res > eps)
                left = mid;
            else
                right = mid;
        }
        graph(N, M, left);
        Dinic::dinic();
        Dinic::search();
    }
}