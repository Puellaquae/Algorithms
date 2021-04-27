#include <climits>

#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

void optimize_cpp_stdio() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(NULL);
    std::cin.tie(NULL);
}

int main() {
    optimize_cpp_stdio();
    int n, c;
    std::cin >> n >> c;
    std::vector<std::pair<int, int>> a(n);
    for (int i = 0; i < n; i++)
        std::cin >> a[i].first >> a[i].second;
    std::sort(a.begin(), a.end());
    int ans = 0;
    for (;;) {
        int need = c;
        std::vector<int> take(n);
        for (int i = n - 1; ~i; i--) {
            take[i] = std::min(need / a[i].first, a[i].second);
            need -= take[i] * a[i].first;
        }
        for (int i = 0; i < n && 0 < need; i++) {
            int extra = std::min((need + a[i].first - 1) / a[i].first, a[i].second - take[i]);
            need -= extra * a[i].first;
            take[i] = take[i] + extra;
        }
        if (0 < need) break;
        int get = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (take[i] != 0)
                get = std::min(get, a[i].second / take[i]);
        }
        for (int i = 0; i < n; i++)
            a[i].second -= get * take[i];
        ans += get;
    }
    std::cout << ans << "\n";
    return 0;
}