// Median
#include <algorithm>
#include <cstdio>
#include <iostream>
typedef long long i64;

const int MAX_N = 1e5 + 10;
const int INF = 1e9 + 10;
int N;
int num[MAX_N];

i64 C(int dist) {
    i64 res = 0;
    for (int i = 1; i <= N; i++) {
        int l = i, r = N;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (num[mid] - num[i] <= dist)
                l = mid;
            else
                r = mid - 1;
        }
        res += r - i;
    }
    return res;
}
int main() {
    while (~scanf("%d", &N)) {
        for (int i = 1; i <= N; i++) {
            scanf("%d", &num[i]);
        }
        std::sort(num + 1, num + 1 + N);
        i64 M = ((N - 1) * N / 2 + 1) / 2;
        int l = 0, r = INF;
        while (l < r) {
            int mid = (l + r) / 2;
            if (C(mid) >= M) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        printf("%d\n", l);
    }
    return 0;
}
