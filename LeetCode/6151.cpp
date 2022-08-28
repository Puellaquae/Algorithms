#include <iostream>
#include <set>
#include <string>
using namespace std;

class Solution {
public:
    int countSpecialNumbers(string n, set<bool> &aN) {
        if (n.size() == 1) {
            return aN.size();
        }
        int cnt = 0;
        int x = n[0] - '0';
        for (int i = 0; i < x; i++) {
            aN.erase(i);
            cnt += countSpecialNumbers(n.substr(1), aN);
            aN.insert(i);
        }
        if (n.size() == 2) {
            cnt += n.back() - '0' + 1;
        } else {
            aN.erase(i);
            cnt += countSpecialNumbers(n.substr(1), aN);
            aN.insert(i);
        }
        return cnt;
    }
};

int main() {
    Solution s;
    set<int> n;
    for (int i = 0; i < 10; i++) {
        n.insert(i);
    }
    cout << s.countSpecialNumbers("135", n) << endl;
}