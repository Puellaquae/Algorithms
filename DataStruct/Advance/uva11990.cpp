//"Dynmaic" Inversion

#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long i64;
#define MAX_N 200000 + 10
#define SQRT_MAX_N 500
#define MAX_M 100000 + 10

int A[MAX_N], reA[MAX_N], removed[MAX_M];
i64 ans[MAX_M];
i64 preSum[SQRT_MAX_N][SQRT_MAX_N];
bool indexRemovedQ[MAX_N], have[MAX_N];
int bSize, bLen, N, M;

i64 suminver(int index, int val) {
    int tx = index / bSize;
    int ty = val / bSize;
    i64 res = 0;
    if (tx) {
        for (int i = 0; i < ty; i++) {
            res += preSum[tx - 1][i];
        }
    }
    for (int i = tx * bSize; i <= index; i++) {
        if (have[i] && A[i] < ty * bSize) {
            res++;
        }
    }
    for (int i = ty * bSize; i <= val; i++) {
        if (have[reA[i]] && reA[i] <= index) {
            res++;
        }
    }
    return res;
}
i64 add(int index, int val) {
    have[index] = true;
    int tx = index / bSize;
    int ty = val / bSize;
    for (int i = tx; i < bLen; i++) {
        preSum[i][ty]++;
    }
    i64 res = -2 * suminver(index, val);
    res += suminver(N - 1, val);
    res += suminver(index, N - 1);
    return res;
}

int main() {
    while (~scanf("%d %d", &N, &M)) {
        bSize = sqrt(N) + 10;
        bLen = N / bSize + 1;
        memset(A, 0, sizeof A);
        memset(reA, 0, sizeof reA);
        memset(have, 0, sizeof have);
        memset(preSum, 0, sizeof preSum);
        memset(indexRemovedQ, 0, sizeof indexRemovedQ);
        for (int i = 0; i < N; i++) {
            scanf("%d", A + i);
            A[i]--;
            reA[A[i]] = i;
        }
        for (int i = 0; i < M; i++) {
            scanf("%d", removed + i);
            removed[i]--;
            indexRemovedQ[reA[removed[i]]] = true;
        }
        i64 inver = 0;
        for (int i = 0; i < N; i++) {
            if (!indexRemovedQ[i]) {
                inver += add(i, A[i]);
            }
        }
        for (int i = M - 1; i >= 0; i--) {
            inver += add(reA[removed[i]], removed[i]);
            ans[i] = inver;
        }
        for (int i = 0; i < M; i++) {
            printf("%lld\n", ans[i]);
        }
    }
    return 0;
}