#include <iostream>

using namespace std;

class Solution {
public:
    string reformat(string s) {
        string dig = "", letter = "";
        for (char c : s) {
            if ('0' <= c && c <= '9') {
                dig.push_back(c);
            } else {
                letter.push_back(c);
            }
        }
        if (dig.size() < letter.size()) {
            swap(dig, letter);
        }
        if (dig.size() - letter.size() > 1) {
            return "";
        }
        string ans;
        int i = 0;
        for (; i < letter.size(); i++) {
            ans.push_back(dig[i]);
            ans.push_back(letter[i]);
        }
        if (i < dig.size()) {
            ans.push_back(dig[i]);
        }
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.reformat("a0b1c2") << endl;
}