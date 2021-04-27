// Transferring Sylla

/********************/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdio>
namespace TriConnectGraph {
using namespace std;

#define MAXN 512

vector<int> G[MAXN];
int V;
bool is_cut_vertex[MAXN];
int status[MAXN];
int lowlink[MAXN];
int index[MAXN];
int root;
bool has_cut_vertex;

void init(const int &v) {
    V = v;
    has_cut_vertex = false;
    for (int i = 0; i <= V; ++i) {
        G[i].clear();
    }
}

void tarjan_dfs(int current, int from, int depth) {
    status[current] = 1;
    lowlink[current] = index[current] = depth;
    int sub_tree = 0;
    int v;
    for (vector<int>::const_iterator it =
             G[current].begin();
         it != G[current].end(); it++) {
        v = *it;
        if (v != from && status[v] == 1) {
            lowlink[current] =
                min(lowlink[current], index[v]);
        }
        if (0 == status[v]) {
            tarjan_dfs(v, current, depth + 1);
            sub_tree++;
            lowlink[current] =
                min(lowlink[current], lowlink[v]);
            if ((current == root && sub_tree > 1) ||
                (current != root &&
                 lowlink[v] >= index[current])) {
                is_cut_vertex[current] = 1;
                has_cut_vertex = true;
            }
        }
    }
    status[current] = 2;
}

void calc(int del) {
    memset(is_cut_vertex, 0, sizeof(is_cut_vertex));
    memset(status, 0, sizeof(status));
    memset(lowlink, 0, sizeof(lowlink));
    memset(index, 0, sizeof(index));

    status[del] = 2;
    root = 0;
    if (del == 0) {
        root = 1;
    }
    tarjan_dfs(root, -1, 1);
}

bool check() {
    for (int i = 0; i < V; ++i) {
        calc(i);
        for (int j = 0; j < V; ++j) {
            if (0 == status[j]) {
                has_cut_vertex = true;
                break;
            }
        }
        if (has_cut_vertex) {
            break;
        }
    }
    return !has_cut_vertex;
}

void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}
} // namespace TriConnectGraph
int main() {
    int N, M;
    while (scanf("%d%d", &N, &M) && N) {
        TriConnectGraph::init(N);
        for (int _ = 0, from, to; _ < M; ++_) {
            scanf("%d%d", &from, &to);
            TriConnectGraph::add_edge(from, to);
        }
        puts(TriConnectGraph::check() ? "YES" : "NO");
    }
    return 0;
}