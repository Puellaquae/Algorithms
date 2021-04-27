// Prime Path
// BFS

#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct S {
    char w[4];
    int dis;
    int Num() { return w[0] * 1000 + w[1] * 100 + w[2] * 10 + w[3]; }
    S(int d) {
        w[0] = d / 1000;
        w[1] = d / 100 % 10;
        w[2] = d / 10 % 10;
        w[3] = d % 10;
    }
};

const int LPrime = 10001;
bool Prime[LPrime];

void solve(int a, int b) {
    vector<bool> Used(LPrime, false);
    Used[a] = true;
    queue<S> G;
    G.push(S(a));
    while (!G.empty()) {
        S f = G.front();
        G.pop();
        if (f.Num() == b) {
            cout << f.dis << '\n';
            return;
        }
        for (int d = 0; d < 4; d++) {
            for (int i = (d == 0 ? 1 : 0); i < 10; i++) {
                S ff = f;
                ff.w[d] = i;
                if (Prime[ff.Num()] && !Used[ff.Num()]) {
                    ff.dis++;
                    Used[ff.Num()] = true;
                    G.push(ff);
                }
            }
        }
    }
    cout << "-1\n";
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    memset(Prime, true, sizeof(Prime));
    Prime[0] = Prime[1] = false;
    for (int i = 2; i < LPrime; i++) {
        if (Prime[i] == false)
            continue;
        for (int k = 2; i * k < LPrime; k++) {
            Prime[i * k] = false;
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        if (a == b) {
            cout << "0\n";
            continue;
        }
        solve(a, b);
    }
}