#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    string decodeMessage(string key, string message) {
        vector<char> m(26, -1);
        int idx = 0;
        for (char c : key) {
            if (c != ' ' && m[c - 'a'] == -1) {
                m[c - 'a'] = ('a' + idx++);
            }
        }
        string ans;
        for (char c : message) {
            if (c != ' ') {
                ans += m[c - 'a'];
            } else {
                ans += ' ';
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.decodeMessage("the quick brown fox jumps over the lazy dog",
                            "vkbs bs t suepuv")
         << endl;
    cout << s.decodeMessage("eljuxhpwnyrdgtqkviszcfmabo",
                            "zwx hnfx lqantp mnoeius ycgk vcnjrdb")
         << endl;
}