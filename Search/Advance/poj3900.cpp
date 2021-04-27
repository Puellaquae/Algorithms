// The Robbery

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Diamond {
    long long weight, cost;
    int num;
};
const int MAXN = 16;
bool operator<(const Diamond &a, const Diamond &b) {
    return b.weight * a.cost > a.weight * b.cost;
}
long long maxcost = 0;
long long costsum[MAXN];
int T, N, M;
void dfs(const vector<Diamond> &diamonds, int pos, long long lastM,
         long long hadCost) {
    maxcost = std::max(maxcost, hadCost);
    if (pos == N)
        return;
    if (hadCost + costsum[pos] < maxcost)
        return;
    if (diamonds[pos].cost * lastM < (maxcost - hadCost) * diamonds[pos].weight)
        return;
    const Diamond &d = diamonds[pos];
    for (int i = d.num; i >= 0; i--) {
        if (lastM >= d.weight * i) {
            dfs(diamonds, pos + 1, lastM - d.weight * i, hadCost + d.cost * i);
        }
    }
}

int main() {
    cin >> T;
    while (T--) {
        maxcost = 0;
        cin >> N >> M;
        long long sumw = 0, sumc = 0;
        vector<Diamond> diamonds(N);
        for (int i = 0; i < N; i++) {
            cin >> diamonds[i].weight;
            sumw += diamonds[i].weight * (i + 1ll);
            diamonds[i].num = i + 1;
        }
        for (int i = 0; i < N; i++) {
            cin >> diamonds[i].cost;
            sumc += diamonds[i].cost * (i + 1ll);
        }
        if (sumw <= M) {
            cout << sumc << endl;
            continue;
        }
        sort(diamonds.begin(), diamonds.end());
        costsum[N] = 0;
        for (int i = N - 1; i >= 0; i--) {
            costsum[i] = costsum[i + 1] + diamonds[i].cost * diamonds[i].num;
        }
        dfs(diamonds, 0, M, 0);
        cout << maxcost << endl;
    }
}