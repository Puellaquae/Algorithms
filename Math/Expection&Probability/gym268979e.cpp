// Stones Merging Plus(Hard Version)

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
constexpr ll mod = 1e9 + 7;
ll qpow(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto &i : x)
        cin >> i;
    int ans = 0;
    for (int i = 1, j = 0; i < n; ++i) {
        j = (j + qpow(i, mod - 2)) % mod;
        ans = (ans + 1ll * j * (x[i] - x[i - 1])) % mod;
    }
    for (int i = 1; i < n; ++i)
        ans = 1ll * ans * i % mod;
    cout << ans;
    return 0;
}