// DNA Laboratory

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

#define MAX_N 15
#define INF 0x3f3f3f3f

int N;
int cost[MAX_N][MAX_N];
int D[1 << MAX_N][MAX_N];
bool reachable[1 << MAX_N][MAX_N];
string piece[MAX_N];

template <typename T> bool update_min(T &old, const T &val) {
    if (old > val) {
        old = val;
        return true;
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            cin>>piece[i];
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i != j && piece[j].find(piece[i]) != string::npos) {
                    piece[i] = piece[j];
                }
            }
        }
        sort(piece, piece + N);
        N = unique(piece, piece + N) - piece;
        int length[MAX_N];
        for (int i = 0; i < N; i++) {
            length[i] = piece[i].length();
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int l = 0; l <= min(length[i], length[j]); l++) {
                    if (piece[i].substr(length[i] - l) ==
                        piece[j].substr(0, l)) {
                        cost[i][j] = length[j] - l;
                    }
                }
            }
        }

        for (int bit = 0; bit < 1 << N; bit++) {
            memset(D[bit], 0x3f, sizeof(D[bit]));
        }
        for (int i = 0; i < N; i++) {
            D[1 << i][i] = length[i];
        }
        for (int bit = 0; bit < 1 << N; bit++) {
            for (int i = 0; i < N; i++) {
                if (D[bit][i] != INF) {
                    for (int j = 0; j < N; j++) {
                        if (!((bit >> j) & 1)) {
                            update_min(D[bit | (1 << j)][j],
                                       D[bit][i] + cost[i][j]);
                        }
                    }
                }
            }
        }

        int bestLength = INF;
        for (int i = 0; i < N; ++i) {
            update_min(bestLength, D[(1 << N) - 1][i]);
        }

        memset(reachable, false, sizeof(reachable));
        for (int i = 0; i < N; ++i) {
            if (D[(1 << N) - 1][i] == bestLength) {
                reachable[(1 << N) - 1][i] = true;
            }
        }

        for (int bit = (1 << N) - 1; bit >= 0; --bit) {
            for (int i = 0; i < N; ++i) {
                if (reachable[bit][i]) {
                    for (int j = 0; j < N; ++j) {
                        if (i != j && ((bit >> j) & 1)) {
                            reachable[bit & ~(1 << i)][j] |=
                                (D[bit & ~(1 << i)][j] + cost[j][i] ==
                                 D[bit][i]);
                        }
                    }
                }
            }
        }

        string result = string(1, 'z' + 1);
        int appended = 0, last = -1;
        for (int i = 0; i < N; ++i) {
            if (reachable[1 << i][i] && update_min(result, piece[i])) {
                last = i;
            }
        }

        appended |= 1 << last;
        for (int _ = 0; _ < N - 1; ++_) {
            string tail = string(1, 'z' + 1);
            int key = -1;
            for (int i = 0; i < N; ++i) {
                if (!((appended >> i) & 1)) {
                    if (reachable[appended | (1 << i)][i] &&
                        D[appended][last] + cost[last][i] ==
                            D[appended | (1 << i)][i] &&
                        update_min(
                            tail, piece[i].substr(length[i] - cost[last][i]))) {
                        key = i;
                    }
                }
            }
            last = key;
            appended |= 1 << key;
            result += tail;
        }
        printf("Scenario #%d:\n%s\n\n", t + 1, result.c_str());
    }
    return 0;
}