// Beauty Contest
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
struct p {
    int x, y;
    bool operator<(const p &b)const {
        if (x != b.x)
            return x < b.x;
        return y < b.y;
    }
    p() {}
    p(int _x, int _y) : x(_x), y(_y) {}
    p operator-(p b) { return p(x - b.x, y - b.y); }
    int det(p b) { return x * b.y - y * b.x; }
};
int distS(p a, p b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
vector<p> convexHull(vector<p> &ps) {
    sort(ps.begin(), ps.end());
    int k = 0;
    vector<p> qs(ps.size() * 2);
    for (int i = 0; i < (int)ps.size(); i++) {
        while (k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0)
            k--;
        qs[k++] = ps[i];
    }
    for (int i = ps.size() - 2, t = k; i >= 0; i--) {
        while (k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0)
            k--;
        qs[k++] = ps[i];
    }
    qs.resize(k - 1);
    return qs;
}
void solve(int n) {
    vector<p> ps(n);
    for (int i = 0; i < n; i++) {
        cin >> ps[i].x >> ps[i].y;
    }
    vector<p> qs = convexHull(ps);
    int res = 0;
    for (int i = 0; i < (int)qs.size(); i++) {
        for (int j = 0; j < i; j++) {
            res = max(res, distS(qs[i], qs[j]));
        }
    }
    cout << res << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        solve(n);
    }
}