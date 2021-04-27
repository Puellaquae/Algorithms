// Sticks

#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 70;
int Strick[MAXN];
int N, NowCheckLen;
bool Vis[MAXN];
bool IsEnd = false;
bool dfs(const int usedN, const int nowLen, int nowIndex) {
    if (nowLen == NowCheckLen) {
        if (usedN == N)
            return true;
        return dfs(usedN, 0, 0);
    }
    if (nowLen == 0) {
        while (Vis[nowIndex])
            nowIndex++;
        Vis[nowIndex] = true;
        if (dfs(usedN + 1, Strick[nowIndex], nowIndex + 1))
            return true;
        Vis[nowIndex] = false;
    } else {
        for (int i = nowIndex; i < N; i++) {
            if (!Vis[i] && nowLen + Strick[i] <= NowCheckLen) {
                if (!Vis[i - 1] && Strick[i] == Strick[i - 1])
                    continue;
                Vis[i] = true;
                if (dfs(usedN + 1, nowLen + Strick[i], i + 1))
                    return true;
                Vis[i] = false;
            }
        }
    }
    return false;
}

int main() {
    while (cin >> N, N) {
        int sumLen = 0, maxLen = 0;
        for (int i = 0; i < N; i++) {
            cin >> Strick[i];
            maxLen = max(Strick[i], maxLen);
            sumLen += Strick[i];
        }
        sort(Strick, Strick + N, greater<int>());
        for (NowCheckLen = maxLen; NowCheckLen <= sumLen; NowCheckLen++) {
            if (sumLen % NowCheckLen == 0) {
                memset(Vis, false, sizeof Vis);
                if (dfs(0, 0, 0)) {
                    cout << NowCheckLen << endl;
                    break;
                }
            }
        }
    }
}