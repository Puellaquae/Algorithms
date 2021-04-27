// Dropping test
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long int64;
const int MAX_N = 1e3 + 15;
struct S {
    double a, b;
};
S Scores[MAX_N];
double D[MAX_N];
const double E = 1e-7;
int N, K;
double C(double x) {
    double sum = 0;
    for (int i = 0; i < N; i++) {
        D[i] = Scores[i].a - Scores[i].b * x;
    }
    sort(D, D + N);
    for (int i = K; i < N; i++) {
        sum += D[i];
    }
    return sum;
}
int main() {
    while (~scanf("%d %d", &N, &K)) {
        if (!N && !K) {
            break;
        }
        for (int i = 0; i < N; i++) {
            scanf("%lf", &(Scores[i].a));
        }
        for (int i = 0; i < N; i++) {
            scanf("%lf", &(Scores[i].b));
        }
        double lb = 0, ub = 0;
        for (int i = 0; i < N; i++) {
            lb = min(lb, Scores[i].a / Scores[i].b);
            ub = max(ub, Scores[i].a / Scores[i].b);
        }
        while (lb < ub - E) {
            double mid = (lb + ub) / 2;
            if (C(mid) > 0) {
                lb = mid;
            } else {
                ub = mid;
            }
        }
        printf("%.0f\n", lb * 100);
    }
}