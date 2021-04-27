// Aoyun

#include <iostream>
#include <map>
#include <vector>
typedef long long i64;
using namespace std;
i64 mod = 2008;
typedef vector<i64> vec;
typedef vector<vec> mat;

template <typename T>
vector<vector<T>> mul(const vector<vector<T>> &A, const vector<vector<T>> &B) {
    vector<vector<T>> C(A.size(), vector<T>(B[0].size()));
    for (int i = 0; i < A.size(); i++) {
        for (int k = 0; k < B.size(); k++) {
            if (A[i][k] != 0) {
                for (int j = 0; j < B[0].size(); j++) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
                }
            }
        }
    }
    return C;
}
template <typename T> vector<vector<T>> pow(vector<vector<T>> A, i64 n) {
    vector<vector<T>> B(A.size(), vector<T>(A.size()));
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

template <typename T> vector<vector<T>> addE(vector<vector<T>> A) {
    for (int i = 0; i < A.size(); i++) {
        ++A[i][i];
    }
    return A;
}

template <typename T>
vector<vector<T>> add(vector<vector<T>> A, const vector<vector<T>> &B) {
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[0].size(); j++) {
            A[i][j] += B[i][j];
        }
    }
    return A;
}

template <typename T> vector<vector<T>> powsum(vector<vector<T>> A, i64 n) {
    if (n < 1)
        return mat(A.size(), vec(A.size(), 0));
    if (n == 1)
        return A;
    if (n & 1)
        return add(pow(A, n), powsum(A, n - 1));
    return mul(powsum(A, n / 2), addE(pow(A, n / 2)));
}

int main() {
    int n;
    while (cin >> n) {
        map<int, int> mp;
        mat R(35, vec(35, 0));
        int id = 0;
        for (int i = 0, p1, p2; i < n; i++) {
            cin >> p1 >> p2;
            if (mp.find(p1) == mp.end()) {
                mp[p1] = id++;
            }
            if (mp.find(p2) == mp.end()) {
                mp[p2] = id++;
            }
            R[mp[p1]][mp[p2]]++;
        }
        mat R_(id, vec(id));
        for (int i = 0; i < id; i++) {
            for (int j = 0; j < id; j++) {
                R_[i][j] = R[i][j];
            }
        }
        int k;
        cin >> k;
        while (k--) {
            int v1, v2, t1, t2;
            cin >> v1 >> v2 >> t1 >> t2;
            if (mp.find(v1) == mp.end() || mp.find(v2) == mp.end()) {
                cout << 0 << endl;
                continue;
            }
            if (t1 > t2)
                swap(t1, t2);
            int s = mp[v1], t = mp[v2];
            i64 ans = powsum(R_, t2)[s][t] - powsum(R_, t1 - 1)[s][t];
            ans = (ans % mod + mod) % mod;
            cout << ans << endl;
        }
    }
}