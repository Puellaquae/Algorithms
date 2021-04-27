// Tree

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int MAX_N = 10005;
struct Edge {
    int to, len;
};
int N, K;
vector<Edge> G[MAX_N];
bool Centroid[MAX_N];
int SubtreeSize[MAX_N];
int Ans;
int ComputeSubTreeSize(int v, int p) {
    int c = 1;
    for (int i = 0; i < G[v].size(); i++) {
        int w = G[v][i].to;
        if (w == p || Centroid[w])
            continue;
        c += ComputeSubTreeSize(G[v][i].to, v);
    }
    SubtreeSize[v] = c;
    return c;
}

pair<int, int> SearchCentroid(int v, int p, int t) {
    pair<int, int> res = make_pair(INT_MAX, -1);
    int s = 1, m = 0;
    for (int i = 0; i < G[v].size(); i++) {
        int w = G[v][i].to;
        if (w == p || Centroid[w])
            continue;
        res = min(res, SearchCentroid(w, v, t));
        m = max(m, SubtreeSize[w]);
        s += SubtreeSize[w];
    }
    m = max(m, t - s);
    res = min(res, make_pair(m, v));
    return res;
}

void EnumeratePaths(int v, int p, int d, vector<int> &ds) {
    ds.push_back(d);
    for (int i = 0; i < G[v].size(); i++) {
        int w = G[v][i].to;
        if (w == p || Centroid[w])
            continue;
        EnumeratePaths(w, v, d + G[v][i].len, ds);
    }
}

int CountPairs(vector<int> &ds) {
    int res = 0;
    sort(ds.begin(), ds.end());
    size_t j = ds.size();
    for (size_t i = 0; i < ds.size(); i++) {
        while (j > 0 && ds[i] + ds[j - 1] > K)
            --j;
        res += j - (j > i ? 1 : 0);
    }
    return res / 2;
}

void Solve(int v) {
    ComputeSubTreeSize(v, -1);
    int s = SearchCentroid(v, -1, SubtreeSize[v]).second;
    Centroid[s] = true;
    for (int i = 0; i < G[s].size(); i++) {
        if (Centroid[G[s][i].to])
            continue;
        Solve(G[s][i].to);
    }
    vector<int> ds;
    ds.push_back(0);
    for (int i = 0; i < G[s].size(); i++) {
        if (Centroid[G[s][i].to])
            continue;
        vector<int> tds;
        EnumeratePaths(G[s][i].to, s, G[s][i].len, tds);
        Ans -= CountPairs(tds);
        ds.insert(ds.end(), tds.begin(), tds.end());
    }
    Ans += CountPairs(ds);
    Centroid[s] = false;
}
int main() {
    while (scanf("%d%d", &N, &K), N && K) {
        for (int i = 0; i < MAX_N; i++) {
            G[i].clear();
        }
        for (int i = 0, u, v, l; i < N - 1; i++) {
            scanf("%d%d%d", &u, &v, &l);
            Edge e;
            e.to = v;
            e.len = l;
            G[u].push_back(e);
            e.to = u;
            G[v].push_back(e);
        }
        Ans = 0;
        Solve(1);
        printf("%d\n", Ans);
    }
}