// Cow Relays

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
typedef long long i64;
typedef int T;
using namespace std;
#define INF 0x3f3f3f3f

typedef vector<T> vec;
typedef vector<vec> mat;

template <typename T>
vector<vector<T> > operator*(const vector<vector<T> > &a,
                             const vector<vector<T> > &b) {
    mat res(a.size(), vec(a.size(), INF));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a.size(); j++) {
            for (int k = 0; k < a.size(); k++) {
                res[i][j] = min(res[i][j], a[i][k] + b[k][j]);
            }
        }
    }
    return res;
}

int main() {
    int n, t, s, e;
    cin >> n >> t >> s >> e;
    int len, u, v, idx = 0;
    mat A(110, vec(110, INF));
    map<int, int> mp;
    for (int i = 0; i < t; i++) {
        cin >> len >> u >> v;
        if (mp.count(u) == 0)
            mp[u] = idx++;
        u = mp[u];
        if (mp.count(v) == 0)
            mp[v] = idx++;
        v = mp[v];
        A[u][v] = min(A[u][v], len);
        A[v][u] = min(A[v][u], len);
    }
    A.resize(idx);
    for (int i = 0; i < A.size(); i++) {
        A[i].resize(idx);
    }
    mat ans = A;
    n--;
    while (n) {
        if (n & 1)
            ans = ans * A;
        A = A * A;
        n >>= 1;
    }
    cout << ans[mp[s]][mp[e]] << endl;
}