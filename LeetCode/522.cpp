#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findLUSlength(const vector<string> &strs) {
        int n = strs.size();
        int maxL = -1;
        auto subQ = [](const string &a, const string &b) {
            int aI = 0, bI = 0;
            for (; aI < a.size() && bI < b.size();) {
                if (a[aI] == b[bI]) {
                    aI++;
                }
                bI++;
            }
            return aI == a.size();
        };
        for (int i = 0; i < n; i++) {
            bool un = true;
            for (int j = 0; j < n; j++) {
                if (i != j && subQ(strs[i], strs[j])) {
                    un = false;
                    break;
                }
            }
            if (un) {
                maxL = max((int)strs[i].size(), maxL);
            }
        }
        return maxL;
    }
};

int main() {
    Solution s;
    cout << s.findLUSlength({"aba", "cdc", "eae"}) << endl;
    cout << s.findLUSlength({"aaa", "aaa", "aa"}) << endl;
}