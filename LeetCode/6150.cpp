#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string smallestNumber(string pattern) {
        int l = pattern.size();
        string ans = "";
        for (int i = 1; i <= l + 1; i++) {
            ans += to_string(i);
        }
        int last = 0;
        for (int i = 0; i < pattern.size(); i++) {
            if (pattern[i] == 'D' && ((i + 1 >= pattern.size()) || pattern[i + 1] != 'D')) {
                reverse(ans.begin() + last, ans.begin() + i + 2);
                last = i + 2;
            }
            if (pattern[i] == 'I') {
                last = i + 1;
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.smallestNumber("IIIDIDDD") << endl;
    cout << s.smallestNumber("DDDD") << endl;
}