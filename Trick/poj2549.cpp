// Sumsets

#include <algorithm>
#include <iostream>
#include <vector>
typedef long long int64;
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int t;
    while (cin >> t && t) {
        vector<int> Nums(t);
        for (int i = 0; i < t; i++) {
            cin >> Nums[i];
        }
        if (t < 4) {
            cout << "no solution\n";
            continue;
        }
        const int inf = -536870912;
        int maxd = inf;
        sort(Nums.begin(), Nums.end());
        for (int i = t - 1; i >= 0 && maxd == inf; i--) {
            for (int j = t - 1; j >= 0 && maxd == inf; j--) {
                if (i == j)
                    continue;
                int64 sum = Nums[i] - Nums[j];
                int l = 0, r = j - 1;
                while (l < r) {
                    if (Nums[l] + Nums[r] == sum) {
                        maxd = max(maxd, Nums[i]);
                        break;
                    } else if (Nums[l] + Nums[r] > sum) {
                        r--;
                    } else {
                        l++;
                    }
                }
            }
        }
        if (maxd == inf) {
            cout << "no solution\n";
        } else {
            cout << maxd << '\n';
        }
    }
}