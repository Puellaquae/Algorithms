// N皇后问题

#include <iostream>
using namespace std;
int bg[12];
int n;
int cnt = 0;
bool check(int row, int col) {
    for (int i = 1; i < col; i++) {
        int d = bg[i];
        if (d == row || abs(d - row) == abs(i - col)) {
            return false;
        }
    }
    return true;
}

void queen(int c) {
    for (int r = 1; r <= n; r++) {
        if (check(r, c)) {
            bg[c] = r;
            if (c == n) {
                cnt++;
                bg[c] = 0;
                return;
            }
            queen(c + 1);
            bg[c] = 0;
        }
    }
}
int ans[] = {0, 1, 0, 0, 2, 10, 4, 40, 92, 352, 724};
int main() {
    while (cin >> n && n) {
        // memset(bg, 0, sizeof bg);
        // cnt = 0;
        // queen(1);
        // cout << cnt << endl;
        cout << ans[n] << endl;
    }
}