// Six Degrees of Cowvin Bacon
// Using Floyd-Warshall, a algorithm of Shortest Path Problem
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int INF = 0x3f3f3f3f;

int main() {
    int n, m, x;
    cin >> n >> m;
    vector<vector<int> > d(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i < n + 1; i++) {
        d[i][i] = 0;
    }
    while (m--) {
        cin >> x;
        vector<int> b(x);
        for (int i = 0; i < x; i++) {
            cin >> b[i];
        }
        for (int i = 0; i < x - 1; i++) {
            for (int j = i + 1; j < x; j++) {
                d[b[i]][b[j]] = d[b[j]][b[i]] = 1;
            }
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    
    int ans = INF;
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = 1; j <= n; j++) {
            sum += d[i][j];
        }
        ans = min(ans, 100 * sum / (n - 1));
    }
    cout << ans << endl;
    return 0;
}