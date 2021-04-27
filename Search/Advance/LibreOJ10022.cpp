// 埃及分数

#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;
typedef long long T;
T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
vector<T> ans;
vector<T> bestans;
T findFirst(T x, T y) {
    for (T i = 1;; i++) {
        if (y < x * i)
            return i;
    }
}
bool dfs(T re, T a, T b) {
    if (re == 1) {
        if (a == 1 && b > ans.back() &&
            (bestans.empty() || b < bestans.back())) {
            ans.push_back(b);
            bestans = ans;
            ans.pop_back();
            return true;
        }
        return false;
    }
    bool found = false;
    for (T i = max(findFirst(a, b), ans.empty() ? 2 : ans.back() + 1);
         a * i < re * b; i++) {
        const T newA = a * i - b;
        const T newB = b * i;
        ans.push_back(i);
        if (dfs(re - 1, newA / gcd(newA, newB), newB / gcd(newA, newB))) {
            found = true;
        }
        ans.pop_back();
    }
    return found;
}

int main() {
    T a, b;
    cin >> a >> b;
    const T gg = gcd(a, b);
    a /= gg;
    b /= gg;
    if (a == 1) {
        cout << b << endl;
        return 0;
    }
    for (int i = 2;; i++) {
        ans.clear();
        if (dfs(i, a, b)) {
            copy(bestans.begin(), bestans.end(),
                 ostream_iterator<int>(cout, " "));
            cout << endl;
            return 0;
        }
    }
}