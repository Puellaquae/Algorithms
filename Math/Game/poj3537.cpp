//Crosses and Crosses

#include <iostream>
using namespace std;

const int MAX_N = 2000 + 16;
int sg[MAX_N];

int dfs(const int &x) {
    if (x < 0)
        return 0;
    int &g = sg[x];
    if (g >= 0)
        return g;
    bool s[MAX_N] = {false};
    for (int i = 1; i <= x; i++) {
        s[dfs(i - 3) ^ dfs(x - i - 2)] = true;
    }
    while (s[++g])
        ;
    return g;
}

int main() {
    int n;
    memset(sg, -1, sizeof(sg));
    while (cin >> n) {
        cout << (dfs(n) ? "1\n" : "2\n");
    }
    return 0;
}