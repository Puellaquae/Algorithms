// POJ-1328 Radar Installation
// Using Greedy

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
struct P {
    int x, y;
    double aL, aR;
};

bool cmp(P a, P b) { return a.aR < b.aR; }

int main() {
    int nP, dx, id = 0;
    while (cin >> nP >> dx && nP && dx) {
        id++;
        bool flag = true;
        vector<P> ps;
        for (int index = 0; index < nP; index++) {
            P i;
            int xp, yp;
            cin >> xp >> yp;
            if (yp > dx) {
                flag = false;
            } else {
                i.x = xp;
                i.y = yp;
                double adx = sqrt(dx * dx - yp * yp);
                i.aL = xp - adx;
                i.aR = xp + adx;
                ps.push_back(i);
            }
        }
        if (!flag) {
            printf("Case %d: -1\n", id);
            continue;
        }
        sort(ps.begin(), ps.end(), cmp);
        int ans = 1;
        double pLr = ps[0].aR;
        for (int i = 1; i < ps.size(); i++) {
            if (!(ps[i].aL <= pLr && pLr <= ps[i].aR)) {
                ans++;
                pLr = ps[i].aR;
            }
        }
        printf("Case %d: %d\n", id, ans);
    }
    return 0;
}