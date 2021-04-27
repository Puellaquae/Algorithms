//poj2379 Cleaning Shifts
// Using Greedy
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>

struct C {
    int l, r;
};

bool cmp(C a, C b) { return a.l < b.l; }

using namespace std;
int main() {
    int N, T;
    cin >> N >> T;
    vector<C> cs;
    while (N--) {
        C i;
        scanf("%d%d", &(i.l), &(i.r));
        cs.push_back(i);
    }
    sort(cs.begin(), cs.end(), cmp);
    int lR = 1;
    int ans = 0;
    int i = 0;
    while (i < cs.size() && lR <= T) {
        int farR = -1;
        while (i < cs.size() && cs[i].l <= lR) {
            farR = max(farR, cs[i].r);
            i++;
        }
        if (farR <= lR - 1)
            break;
        lR = farR + 1;
        ans++;
    }
    if (lR <= T) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}