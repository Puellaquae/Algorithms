// Rectangular Covering

#include <cstdio>
#include <cstring>
#include <vector>
struct Rect {
    int coveredMask, area;
};

#define abs(x) ((x) < 0 ? -(x) : (x))

const int MAXN = 16;
const int INF = 0x3f3f3f3f;
int x[MAXN], y[MAXN], dp[1 << MAXN];
using namespace std;
bool inQ(int pi, int pj, int pk) {
    return ((x[pi] - x[pk]) * (x[pj] - x[pk]) <= 0) &&
           ((y[pi] - y[pk]) * (y[pj] - y[pk]) <= 0);
}

int main() {
    int N;
    while (~scanf("%d", &N) && N) {
        for (int i = 0; i < N; i++) {
            scanf("%d%d", x + i, y + i);
        }
        vector<Rect> rects;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                Rect r;
                r.coveredMask = (1 << i) | (1 << j);
                r.area = max(1, abs(x[i] - x[j])) *
                         max(1, abs(y[i] - y[j]));
                for (int k = 0; k < N; k++) {
                    if (inQ(i, j, k)) {
                        r.coveredMask |= 1 << k;
                    }
                }
                rects.push_back(r);
            }
        }
        memset(dp, 0x3f, sizeof dp);
        dp[0] = 0;
        for (vector<Rect>::iterator it = rects.begin();
             it != rects.end(); it++) {
            for (int s = 0; s < 1 << N; s++) {
                int ns = s | it->coveredMask;
                if (dp[s] != INF && ns != s) {
                    dp[ns] =
                        min(dp[ns], dp[s] + it->area);
                }
            }
        }
        printf("%d\n", dp[(1 << N) - 1]);
    }
}