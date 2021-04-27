// Matrix

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define N 1005
#define lowbit(x) (x & -x)

int c[N][N], n, m;

int sum(int x, int y) {
    int ret = 0;
    for (int i = x; i >= 1; i -= lowbit(i)) {
        for (int j = y; j >= 1; j -= lowbit(j)) {
            ret += c[i][j];
        }
    }
    return ret;
}

void add(int x, int y) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= n; j += lowbit(j)) {
            c[i][j]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int x1, x2, y1, y2, t;
    char op;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        memset(c, 0, sizeof c);
        while (m--) {
            cin >> op;
            if (op == 'C') {
                cin >> x1 >> y1 >> x2 >> y2;
                add(x1, y1);
                add(x2 + 1, y1);
                add(x1, y2 + 1);
                add(x2 + 1, y2 + 1);
            } else {
                cin >> x1 >> y1;
                cout << (sum(x1, y1) & 1) << '\n';
            }
        }
        cout << "\n";
    }
    return 0;
}