// Bound Found
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int n, k;
    while (cin >> n >> k && (n || k)) {
        vector<pair<int, int> > p(n + 1);
        p[0] = pair<int, int>(0, 0);
        for (int i = 1, x; i <= n; i++) {
            cin >> x;
            p[i].first = p[i - 1].first + x;
            p[i].second = i;
        }
        sort(p.begin(), p.end());
        for (int i = 0, q; i < k; i++) {
            cin >> q;
            int l = 0, r = 1, sum, ansl, ansr, anssum, minabs = 0x7fffffff;
            while (r <= n) {
                sum = p[r].first - p[l].first;
                if (abs(sum - q) < minabs) {
                    minabs = abs(sum - q);
                    anssum = sum;
                    ansl = min(p[l].second, p[r].second) + 1;
                    ansr = max(p[l].second, p[r].second);
                }
                if (sum < q) {
                    r++;
                } else if (sum > q) {
                    l++;
                } else {
                    break;
                }
                if (l == r) {
                    r++;
                }
            }
            cout << anssum << " " << ansl << " " << ansr << '\n';
        }
    }
}