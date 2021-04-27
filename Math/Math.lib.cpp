typedef long long int64;
int64 mPow(int64 x, int64 n,int64 mod)
{
    int64 res = 1;
    while (n > 0)
    {
        if (n & 1)
            res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}
int64 mCnm(int64 a, int64 b,int64 mod)
{
    int64 i, ans = 1, c = 1;
    for (i = a; i >= a - b + 1; i--)
        ans = ans * i % mod;
    for (i = b; i >= 1; i--)
        c = c * i % mod;
    return ans * mPow(c, mod - 2,mod) % mod;
}

#include<vector>
#include<algorithm>
using namespace std;
int compress(int *p,int N) {
    vector<int> ps(N);
    for (int i = 0; i < N; i++) {
        ps[i] = p[i];
    }
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    for (int i = 0; i < N; i++) {
        p[i] = 1 + lower_bound(ps.begin(), ps.end(), p[i]) - ps.begin();
    }
    return ps.size();
}