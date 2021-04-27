#include <vector>
#include <queue>
#include <cstring>
namespace Dinic
{
using namespace std;
const int MAX_V = 50000;
const int INF = 0x7fffffff;
struct edge
{
    int to, cap, rev;
};
vector<edge> G[MAX_V];
int level[MAX_V];
int iter[MAX_V];
void addEdge(int from, int to, int cap)
{
    G[from].push_back((edge){to, cap, G[to].size()});
    G[to].push_back((edge){from, 0, G[from].size() - 1});
}
void bfs(int s)
{
    memset(level, -1, sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while (!que.empty())
    {
        int v = que.front();
        que.pop();
        for (int i = 0; i < (int)G[v].size(); i++)
        {
            edge &e = G[v][i];
            if (e.cap > 0 && level[e.to] < 0)
            {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}
int dfs(int v, int t, int f)
{
    if (v == t)
        return f;
    for (int &i = iter[v]; i < (int)G[v].size(); i++)
    {
        edge &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to])
        {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0)
            {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}
int maxFlow(int s, int t)
{
    int flow = 0;
    for (;;)
    {
        bfs(s);
        if (level[t] < 0)
            return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = dfs(s, t, INF)) > 0)
        {
            flow += f;
        }
    }
}
} // namespace Dinic

namespace MinCostFlow
{
using namespace std;
typedef pair<int, int> P;
struct edge
{
    int to, cap, cost, rev;
};
int V;
const int MAX_V = 50000;
const int INF = 0x7fffffff;
vector<edge> G[MAX_V];
int h[MAX_V];
int dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];
void addEdge(int from, int to, int cap, int cost)
{
    G[from].push_back((edge){to, cap, cost, G[to].size()});
    G[to].push_back((edge){from, 0, -cost, G[from].size() - 1});
}
int minCostFlow(int s, int t, int f)
{
    int res = 0;
    fill(h, h + V, 0);
    while (f > 0)
    {
        priority_queue<P, vector<P>, greater<P>> que;
        fill(dist, dist + V, INF);
        dist[s] = 0;
        que.push(P(0, s));
        while (!que.empty())
        {
            P p = que.top();
            que.pop();
            int v = p.second;
            if (dist[v] < p.first)
                continue;
            for (int i = 0; i < (int)G[v].size(); i++)
            {
                edge &e = G[v][i];
                if (e.cap > 0 &&
                    dist[e.to] > dist[v] + e.cost + h[v] - h[e.to])
                {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    que.push(P(dist[e.to], e.to));
                }
            }
        }
        if (dist[t] == INF)
        {
            return -1;
        }
        for (int v = 0; v < V; v++)
        {
            h[v] += dist[v];
        }
        int d = f;
        for (int v = t; v != s; v = prevv[v])
        {
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d * h[t];
        for (int v = t; v != s; v = prevv[v])
        {
            edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}
} // namespace MinCostFlow

struct Edge {
    int To, Cost;
};

struct Point {
    int Distance, Index;
    bool operator<(const Point &b) const { return Distance > b.Distance; }
};

#ifndef INT_MAX
#define INT_MAX 0x7fffffff
#endif


using namespace std;

vector<int> Dijkstra(int Start, const vector<vector<Edge> > &G) {
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
        for (Edge e : G[Index]) {
            if (Distance[e.To] > Distance[Index] + e.Cost) {
                Distance[e.To] = Distance[Index] + e.Cost;
                Q.push({Distance[e.To], e.To});
            }
        }
    }
    return Distance;
}