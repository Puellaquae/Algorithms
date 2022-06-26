#include <algorithm>
#include <iostream>
#include <stack>
#include <tuple>
#include <vector>
using namespace std;

template <class T> T gcd(T a, T b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

class Solution {
public:
    int sQ(int pp, int p, int n) {
        if (n <= 0) {
            return 1;
        }
        int cnt = 0;
        for (int i = 1; i <= 6; i++) {
            if ((p == 0 || gcd(i, p) == 1) && p != i && pp != i) {
                cnt += sQ(p, i, n - 1);
            }
        }
        return cnt;
    }
    int sQM(vector<vector<vector<int>>>& mem, int pp, int p, int n) {
        if (mem[pp][p][n] != -1) {
            return mem[pp][p][n];
        }
        int cnt = 0;
        if (n <= 0) {
            return 1;
        }
        for (int i = 1; i <= 6; i++) {
            if ((p == 0 || gcd(i, p) == 1) && p != i && pp != i) {
                cnt = (cnt + sQM(mem, p, i, n - 1)) % 1000000007;
            }
        }
        mem[pp][p][n] = cnt;
        return cnt;
    }
    int distinctSequences(int n) {
        vector<vector<vector<int>>> mem(
            7, vector<vector<int>>(7, vector<int>(n + 1, -1)));
        return sQM(mem, 0, 0, n);
    }
};

int main() {
    Solution s;
    for (int i = 1; i <= 100; i++) {
        // int i = 3;
        cout << i << ": " << s.distinctSequences(i) << endl;
        // cout << i << "T: " << s.sQ(0, 0, i) << endl;
    }
}