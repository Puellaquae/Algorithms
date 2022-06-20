#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minimumNumbers(int num, int k) {
        if (num == 0) {
            return 0;
        }
        for (int i = 1; i <= 10; ++i) {
            if ((num - k * i) >= 0 && (num - k * i) % 10 == 0) {
                return i;
            }
        }
        return -1;
    }
};

int main() {
    Solution s;
    cout << s.minimumNumbers(58, 9) << endl;
    cout << s.minimumNumbers(37, 2) << endl;
    cout << s.minimumNumbers(0, 7) << endl;
    cout << s.minimumNumbers(2, 8) << endl;
    cout << s.minimumNumbers(10, 8) << endl;
    cout << s.minimumNumbers(10, 5) << endl;
}