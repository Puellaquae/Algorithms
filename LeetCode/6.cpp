#include <iostream>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        int mod = numRows * 2 - 2;
        if (mod == 0) {
            return s;
        }
        string res = "";
        for (int line = 0; line < numRows; line++) {
            for (int i = 0; i < s.size(); i++) {
                if (i % mod == line || i % mod == (mod - line)) {
                    res += s[i];
                }
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.convert("PAYPALISHIRING", 3) << endl;
    cout << s.convert("PAYPALISHIRING", 4) << endl;
    cout << s.convert("A", 1) << endl;
}