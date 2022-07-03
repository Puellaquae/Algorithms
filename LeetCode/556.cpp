#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int nextGreaterElement(int n) {
        vector<int> d;
        int rn = n;
        while (n != 0) {
            d.push_back(n % 10);
            n /= 10;
        }
        reverse(d.begin(), d.end());
        next_permutation(d.begin(), d.end());
        long long m = 0;
        for (auto &i : d) {
            m = m * 10 + i;
        }
        if ((int)(m) != m) {
            return -1;
        }
        if (m > rn) {
            return m;
        } else {
            return -1;
        }
    }
};

int main() {
    Solution s;
    cout << s.nextGreaterElement(12) << endl;
    cout << s.nextGreaterElement(21) << endl;
    cout << s.nextGreaterElement(1234) << endl;
}