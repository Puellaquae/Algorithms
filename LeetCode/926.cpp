#include <iostream>
using namespace std;

class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int oneCnt = 0;
        int n = s.size();
        for (char c : s) {
            if (c == '1') {
                oneCnt++;
            }
        }
        int minC = n;
        int oneBeforeCnt = 0;
        for (int i = 0; i <= n; i++) {
            if (i != 0 && s[i - 1] == '1') {
                oneBeforeCnt++;
            }
            int needC = oneBeforeCnt + (n - i - (oneCnt - oneBeforeCnt));
            minC = minC > needC ? needC : minC;
        }
        return minC;
    }
};

int main() {
    Solution solution;
    cout << solution.minFlipsMonoIncr("00110") << "\n";
    cout << solution.minFlipsMonoIncr("010110") << "\n";
    cout << solution.minFlipsMonoIncr("00011000") << "\n";
}