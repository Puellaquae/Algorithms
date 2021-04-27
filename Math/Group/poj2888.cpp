// Magic Bracelet

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
const int mod = 9973;
typedef long long i64;

typedef vector<i64> vec;
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

template <typename T>
vector<vector<T> > operator*(const vector<vector<T> > &a,
                             const vector<vector<T> > &b) {
    int size = a.size();
    mat r(size, vec(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                r[i][j] += a[i][k] * b[k][j];
            }
            r[i][j] %= mod;
        }
    }
    return r;
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

i64 pow(i64 x, i64 n) {
    x %= mod;
    int res = 1;
    while (n) {
        if (n & 1)
            res = res * x % mod;
        x = x + x % mod;
        n >>= 1;
    }
    return res % mod;
}

i64 euler(int x) {
    i64 r = x;
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            r -= r / i;
            while (x % i == 0)
                x /= i;
        }
    }
    if (x > 1)
        r -= r / x;
    return r % mod;
}

i64 calc(const mat &a) {
    i64 r = 0;
    for (int i = 0; i < a.size(); i++) {
        r += a[i][i];
    }
    return r % mod;
}

i64 inv(i64 x) { return pow(x, mod - 2); }

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, k, ans = 0;
        cin >> m >> n >> k;
        mat move(n, vec(n));
        for (int i = 0, x, y; i < k; i++) {
            cin >> x >> y;
            move[x][y] = move[y][x] = false;
        }
        int lim = sqrt(n);
        for (int i = 1; i <= lim; i++) {
            if (n % i == 0) {
                ans = (ans + calc(pow(move, i)) * euler(n / i)) % mod;
                if (i * i != n)
                    ans = (ans + calc(pow(move, n / i)) * euler(i)) % mod;
            }
        }
        cout << ans * inv(n) % mod << endl;
    }
}