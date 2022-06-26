#include <iostream>
using namespace std;

class Solution {
public:
    int countAsterisks(string s) {
        int cnt = 0;
        bool in = false;
        for (char c: s) {
            if (c == '*' && !in) {
                cnt++;
            } else if (c == '|') {
                in = !in;
            }
        }
        return cnt;
    }
};

int main() {
    Solution s;
    cout << s.countAsterisks("l|*e*et|c**o|*de|") << endl;
    cout << s.countAsterisks("iamprogrammer") << endl;
    cout << s.countAsterisks("yo|uar|e**|b|e***au|tifu|l") << endl;
}