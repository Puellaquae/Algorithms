#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
typedef long long i64;

constexpr i64 MOD = 1000000007;

class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        vector<i64> p(forget, 0);
        p[0] = 1;
        while (n-- > 1) {
            for (int i = p.size() - 1; i > 0; i--) {
                p[i] = p[i - 1];
            }
            p[0] = 0;
            i64 pn = 0;
            for (int i = delay; i < forget; i++) {
                pn = (pn + p[i]) % MOD;
            }
            p[0] = pn;
        }
        i64 ans = 0;
        for (int i = 0; i < p.size(); i++) {
            ans = (ans + p[i]) % MOD;
        }
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.peopleAwareOfSecret(6, 2, 4) << endl;
    cout << s.peopleAwareOfSecret(4, 1, 3) << endl;
    cout << s.peopleAwareOfSecret(684, 18, 496) << endl;
}