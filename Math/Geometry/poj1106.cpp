// Transmitters
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
double distS(double x1, double y1, double x2, double y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
int main() {
    double tx, ty, tr;
    while (cin >> tx >> ty >> tr && tr > 0) {
        int n;
        cin >> n;
        vector<double> ps;
        double x, y;
        const double pi = 3.1415926535897932;
        for (int i = 0; i < n; i++) {
            cin >> x >> y;
            if (distS(x, y, tx, ty) <= tr * tr) {
                ps.push_back(atan2(ty - y, tx - x));
            }
        }

        sort(ps.begin(), ps.end());
        int num = (int)ps.size();
        int ans = 0;
        for (int i = 0; i < num; i++) {
            int cnt = 0;
            for (int j = 0; j < num; j++) {
                if (ps[i] < 0 && (ps[j] >= ps[i] && ps[j] <= ps[i] + pi)) {
                    cnt++;
                } else if (ps[i] > 0 &&
                           (ps[j] >= ps[i] || ps[j] + pi <= ps[i])) {
                    cnt++;
                } else if (ps[j] >= ps[i] && ps[j] <= ps[i] + pi) {
                    cnt++;
                }
            }
            ans = max(ans, cnt);
        }
        cout << ans << endl;
    }
}