#include <iostream>
#include <stack>
using namespace std;

int main() {
    int i, j, k, n, m, l, r, kase = 1;
    char a[101];
    char b[101];
    int vis[101];
    int num[101];
    stack<int> s[101];
    while (scanf("%d", &n), n) {
        for (i = 0; i < n; i++) {
            s[i].push(i);
        }
        scanf("%s", a);
        for (i = 0; i < n; i++) {
            if (a[i] == 'U')
                vis[i] = 1;
            else
                vis[i] = -1;
        }
        l = 0, r = n - 1;
        scanf("%s", b);
        for (i = 0; i < n - 1; i++) {
            if (b[i] == 'L') {
                for (j = 0; j <= l; j++)
                    vis[j] = -1 * vis[j];
                l++;
                while (!s[l - 1].empty()) {
                    s[l].push(s[l - 1].top());
                    s[l - 1].pop();
                }
            } else {
                for (j = n - 1; j >= r; j--)
                    vis[j] = -1 * vis[j];
                r--;
                while (!s[r + 1].empty()) {
                    s[r].push(s[r + 1].top());
                    s[r + 1].pop();
                }
            }
        }
        for (i = 0; i < n; i++) {
            num[i] = s[l].top();
            s[l].pop();
        }
        printf("Pile %d\n", kase++);
        scanf("%d", &m);
        while (m--) {
            scanf("%d", &k);
            printf("Card %d is a face ", k);
            printf(vis[num[k - 1]] == 1 ? "up" : "down");
            printf(" %d.\n", num[k - 1] + 1);
        }
    }
}