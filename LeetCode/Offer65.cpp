#include <iostream>

using namespace std;

class Solution {
public:
    int add(int a, int b) {
        if (a == 0) {
            return b;
        }
        if (b == 0) {
            return a;
        }
        return add(a ^ b, ((unsigned)(a & b)) << 1);
    }
};

int main() {
    Solution s;
    cout << s.add(1, 1) << endl;
    cout << s.add(-1, 2) << endl;
    cout << s.add(-1, -1) << endl;
    cout << s.add(-1, 0) << endl;
    cout << s.add(1, 0) << endl;
}