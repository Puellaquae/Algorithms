// The Teacher’s Side of Math

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 20 + 8

int A, B, N, M;
long long Combine[MAX_N][MAX_N];

void InitCombinatorial() {
    for (int i = 0; i < MAX_N; ++i) {
        Combine[i][0] = Combine[i][i] = 1;
        for (int j = 1; j < i; ++j)
            Combine[i][j] = Combine[i - 1][j - 1] + Combine[i - 1][j];
    }
}

inline int Index(int n, int m) { return n * M + m + 1; }

vector<double> Gauss(vector<vector<double> > &A) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        double maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
                maxRow = k;
            }
        }
        for (int k = i; k < n + 1; ++k) {
            double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }
        for (int k = i + 1; k < n; ++k) {
            double c = -A[k][i] / A[i][i];
            for (int j = i; j < n + 1; ++j) {
                if (i == j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] += c * A[i][j];
                }
            }
        }
    }
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = A[i][n] / A[i][i];
        for (int k = i - 1; k >= 0; --k) {
            A[k][n] -= A[k][i] * x[i];
        }
    }
    return x;
}

inline double Round(double x) {
    return x >= 0.0 ? floor(x + 0.5) : ceil(x - 0.5);
}

void Solve() {
    const int size = N * M + 1;
    vector<vector<double> > mat(size, vector<double>(size + 1, 0.0));
    mat[0][0] = 1.0;
    mat[0][size] = 1.0;
    for (int d = 0; d < size; ++d) {
        for (int k = 0; k <= d; ++k) {
            mat[Index(k % N, (d - k) % M)][d < N * M ? d + 1 : 0] +=
                Combine[d][k] * pow((double)A, k / N) *
                pow((double)B, (d - k) / M);
        }
    }
    vector<double> x = Gauss(mat);
    reverse(x.begin() + 1, x.end());
    for (int i = 0; i < size; ++i) {
        printf("%d%c", int(Round(x[i])), i == N * M ? '\n' : ' ');
    }
}

int main() {
    InitCombinatorial();
    while (~scanf("%d%d%d%d", &A, &N, &B, &M) && A > 0) {
        Solve();
    }
    return 0;
}