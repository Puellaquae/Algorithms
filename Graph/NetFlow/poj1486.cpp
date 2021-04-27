// Sorting Slides

/**************/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
const int maxn = 100;

typedef pair<int, int> P;
int match[maxn], n, m, V;
bool used[maxn];
vector<int> G[maxn];

struct Slide {
    int xmin, ymin, xmax, ymax;
} slides[maxn];

struct PageId {
    int x, y;
} pid[maxn];

void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

bool dfs(int v) {
    used[v] = true;
    for (size_t i = 0; i < G[v].size(); i++) {
        int u = G[v][i], w = match[u];
        if (w < 0 || !used[w] && dfs(w)) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

int hangary() {
    int res = 0;
    memset(match, -1, sizeof(match));
    for (int v = 0; v < V; v++) {
        if (match[v] < 0) {
            memset(used, 0, sizeof(used));
            if (dfs(v))
                res++;
        }
    }
    return res;
}

bool inside(const PageId &p, const Slide &s) {
    return p.x > s.xmin && p.x < s.xmax && p.y > s.ymin && p.y < s.ymax;
}

void build_graph(const vector<P> &vec) {
    for (int i = 0; i < maxn; i++)
        G[i].clear();
    for (size_t i = 0; i < vec.size(); i++)
        add_edge(vec[i].first, vec[i].second);
}

bool cmp(const P &lhs, const P &rhs) { return lhs.second < rhs.second; }

int main() {
    int kase = 0;
    while (~scanf("%d", &n) && n) {
        for (int i = 0; i < n; i++)
            scanf("%d%d%d%d", &slides[i].xmin, &slides[i].xmax, &slides[i].ymin,
                  &slides[i].ymax);
        for (int i = 0; i < n; i++)
            scanf("%d%d", &pid[i].x, &pid[i].y);

        vector<P> edges;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (inside(pid[i], slides[j]))
                    edges.push_back(make_pair(i, j + n));
            }
        }

        V = 2 * n;
        build_graph(edges);
        int tmp = hangary();

        printf("Heap %d\n", ++kase);
        if (tmp < n)
            printf("none\n\n");
        else {
            vector<P> matches;
            for (int i = 0; i < n; i++) {
                matches.push_back(make_pair(i, match[i]));
            }

            vector<P> tmp_edges, ans;
            for (size_t i = 0; i < matches.size(); i++) {
                for (size_t j = 0; j < edges.size(); j++) {
                    if (edges[j].first == matches[i].first &&
                            edges[j].second == matches[i].second ||
                        edges[j].first == matches[i].second &&
                            edges[j].second == matches[i].first)
                        continue;
                    tmp_edges.push_back(
                        make_pair(edges[j].first, edges[j].second));
                }
                build_graph(tmp_edges);
                if (hangary() != n)
                    ans.push_back(
                        make_pair(matches[i].first, matches[i].second));
                tmp_edges.clear();
            }

            if (ans.size() == 0)
                printf("none\n\n");
            else {
                char ch = 'A';
                sort(ans.begin(), ans.end(), cmp);
                for (size_t i = 0; i < ans.size(); i++)
                    printf("(%c,%d)%c", ch + ans[i].second - n,
                           ans[i].first + 1, i + 1 == ans.size() ? '\n' : ' ');
                printf("\n");
            }
        }
    }
    return 0;
}