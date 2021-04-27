// Superset

#include <algorithm>
#include <iostream>
#include <set>
using namespace std;
const int MAX_N = 100010;
typedef pair<int, int> point;
point Ps[MAX_N];
set<point> Ans;
void Solve(const int l, const int r) {
    if (l + 1>= r) {
        return;
    }
    const int mid = (l + r) / 2;
    for (int i = l; i < r; i++) {
        if (i != mid) {
            Ans.insert(point{Ps[mid].first, Ps[i].second});
        }
    }
    Solve(l, mid);
    Solve(mid + 1, r);
}
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> Ps[i].first >> Ps[i].second;
        Ans.insert(Ps[i]);
    }
    sort(Ps, Ps + n);
    Solve(0, n);
    cout << Ans.size() << endl;
    for (const auto &p : Ans) {
        cout << p.first << " " << p.second << endl;
    }
}