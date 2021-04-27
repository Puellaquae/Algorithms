// Cow Sorting

#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long i64;
const int N = 10005;
const int INF = 0x7fffffff;
struct Node {
    int val;
    int id;
} node[N];
int m1, m2, loop, n;
bool vis[N];
i64 solve() {
    i64 res = 0, sum;
    for (int i = 1; i <= n; i++) {
        m2 = INF;
        sum = loop = 0;
        int t = i;
        while (!vis[t]) {
            vis[t] = true;
            loop++;
            m2 = min(m2, node[t].val);
            sum += node[t].val;
            t = node[t].id;
        }
        if (loop) {
            res = res +
                  min(sum - m2 + (loop - 1) * m2, sum + m2 + (loop + 1) * m1);
        }
    }
    return res;
}
int cmp(Node a, Node b) { return a.val < b.val; }
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    while (cin >> n) {
        m1 = INF;
        memset(vis, false, sizeof(vis));
        for (int i = 1; i <= n; i++) {
            cin >> node[i].val;
            node[i].id = i;
            m1 = min(m1, node[i].val);
        }
        sort(node + 1, node + 1 + n, cmp);
        cout << solve() << '\n';
    }
    return 0;
}