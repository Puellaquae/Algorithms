#include <string>

using namespace std;

class Solution {
public:
    int maxScore(string s) {
        int zero = 0;
        int one = 0;
        for (auto c : s) {
            zero += c == '0';
            one += c == '1';
        }
        int ans = 0;
        int lzero = 0;
        int rone = one;
        for (int i = 0; i < s.size() - 1; i++) {
            lzero += s[i] == '0';
            rone -= s[i] == '1';
            ans = max(lzero + rone, ans);
        }
        return ans;
    }
};