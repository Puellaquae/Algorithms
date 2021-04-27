// Showstopper
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define MAX 1000000
typedef long long i64;
i64 X[MAX], Y[MAX], Z[MAX], C[MAX];
int N;

i64 sum(i64 mid) {
    i64 sum = 0;
    for (int i = 0; i < N; ++i) {
        if (mid >= Y[i]) {
            sum += (Y[i] - X[i]) / Z[i] + 1LL;
        } else if (mid >= X[i]) {
            sum += (mid - X[i]) / Z[i] + 1LL;
        }
    }
    return sum;
}
char buf[1024];
bool input() {
    bool hasinput = false;
    N = 0;
    while ((hasinput = gets(buf) != NULL) && strlen(buf) > 0) {
        sscanf(buf, "%lld%lld%lld", &X[N], &Y[N], &Z[N]);
        N++;
    }
    return hasinput || N != 0;
}
int main() {
    while (input()) {
        if (N) {
            i64 l = 0, r = 0x7fffffff;
            while (r > l) {
                i64 mid = (r + l) / 2LL;
                if (sum(mid) % 2 == 1) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            if (l == 0x7fffffff) {
                printf("no corruption\n");
            } else {
                printf("%lld %lld\n", l, sum(l) - sum(l - 1));
            }
        }
    }
    return 0;
}