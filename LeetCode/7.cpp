#include <iostream>
using namespace std;

class Solution {
public:
    int reverse(int x) {
        long long n = 0;
        while (x != 0) {
            n = n * 10 + x % 10;
            x /= 10;
        }

    }
};

int main() {
    Solution s;
    cout << s.reverse(-123) << endl;
    cout << s.reverse(12300) << endl;
    cout << s.reverse(1534236469) << endl;
}