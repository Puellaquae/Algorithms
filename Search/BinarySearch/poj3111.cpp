// K Best

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAX_N = 100000 + 100;
double v[MAX_N];
double w[MAX_N];
const double E = 1e-6;
struct P {
    double val;
    int index;
    bool operator<(const P &B) const { return val > B.val; }
};
bool cmp(P A,P B){
    return A.val>B.val;
}
int N, K;
P D[MAX_N];
bool C(double e) {
    for (int i = 0; i < N; i++) {
        D[i].val = v[i] - w[i] * e;
        D[i].index = i;
    }
    sort(D, D + N);
    double sum = 0;
    for (int i = 0; i < K; i++) {
        sum += D[i].val;
    }
    return sum >= 0;
}
int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", v + i, w + i);
    }
    double lb = 0, ub = 1e7, mid = 0;
    while (E < ub - lb) {
        mid = (lb + ub) / 2;
        if (C(mid)) {
            lb = mid;
        } else {
            ub = mid;
        }
    }
    for (int i = 0; i < K; i++) {
        if (i) {
            printf(" ");
        }
        printf("%d", D[i].index + 1);
    }
    printf("\n");
    return 0;
}