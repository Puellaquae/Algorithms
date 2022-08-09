#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string makeLargestSpecial(string s) {
        vector<string> sub;
        string buf;
        int l = 0;
        for (int i = 0; i < s.size(); i++) {
            buf.push_back(s[i]);
            if (s[i] == '1') {
                l++;
            } else {
                l--;
            }
            if (l == 0) {
                sub.push_back(buf);
                buf.clear();
            }
        }
        if (sub.size() == 1) {
            return "1" +
                   makeLargestSpecial(sub[0].substr(1, sub[0].size() - 2)) +
                   "0";
        } else {
            for (auto &str : sub) {
                str = makeLargestSpecial(str);
            }
            sort(sub.begin(), sub.end(), greater<>());
            string ans;
            for (auto &str : sub) {
                ans += str;
            }
            return ans;
        }
    }
};

int main() {
    Solution s;
    cout << s.makeLargestSpecial("11011000") << endl;
    cout << s.makeLargestSpecial("101010") << endl;
    cout << s.makeLargestSpecial("1101001110001101010110010010") << endl;
}