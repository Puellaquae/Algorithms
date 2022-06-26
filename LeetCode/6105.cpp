#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maximumXOR(const vector<int> &nums) {
        int x = 0;
        for (int n : nums) {
            x |= n;
        }
        return x;
    }
};

int main() {
    Solution s;
    cout << s.maximumXOR({3, 2, 4, 6}) << endl;
    cout << s.maximumXOR({1, 2, 3, 9, 2}) << endl;
}