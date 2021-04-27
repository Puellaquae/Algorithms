// Central Heating

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
typedef long long i64;
using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

template <typename T>
vector<vector<T> > mul(vector<vector<T> > &A, vector<vector<T> > &B) {
    vector<vector<T> > C(A.size(), vector<T>(B[0].size()));
    for (int i = 0; i < A.size(); i++) {
        for (int k = 0; k < B.size(); k++) {
            if (A[i][k] != 0) {
                for (int j = 0; j < B[0].size(); j++) {
                    C[i][j] = C[i][j] + A[i][k] * B[k][j];
                }
            }
        }
    }
    return C;
}
template <typename T> vector<vector<T> > pow(vector<vector<T> > &A, i64 n) {
    vector<vector<T> > B(A.size(), vector<T>(A.size()));
    for (int i = 0; i < A.size(); i++) {
        B[i][i] = 1;
    }
    while (n > 0) {
        if (n & 1) {
            B = mul(B, A);
        }
        A = mul(A, A);
        n >>= 1;
    }
    return B;
}

vec gaussJordan(const mat &A, const vec &b) {
    int n = A.size();
    mat B(n, vec(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = A[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        B[i][n] = b[i];
    }
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i; j < n; j++) {
            if (abs(B[j][i]) > abs(B[pivot][i])) {
                pivot = j;
            }
        }
        swap(B[i], B[pivot]);
        if (B[i][i] == 0) {
            return vec();
        }
        for (int j = i + 1; j <= n; j++) {
            B[i][j] /= B[i][i];
        }
        for (int j = 0; j < n; j++) {
            if (i != j) {
                for (int k = i + 1; k <= n; k++) {
                    //
                    B[j][k] ^= B[j][i] * B[i][k];
                }
            }
        }
    }
    vec x(n);
    for (int i = 0; i < n; i++) {
        x[i] = B[i][n];
    }
    return x;
}
int main() {
    int n;
    cin >> n;
    mat fuck(n, vec(n, 0));
    vec damn(n);
    for (int i = 0; i < n; i++) {
        damn[i] = 1;
        int shit;
        while (cin >> shit && shit != -1) {
            fuck[shit - 1][i] = 1;
        }
    }
    vec holy = gaussJordan(fuck, damn);
    bool has = false;
    for (int i = 0; i < n; i++) {
        if (holy[i]) {
            has = true;
            cout << i + 1 << " ";
        }
    }
    if (!has) {
        cout << "No solution\n";
    } else {
        cout << endl;
    }
}