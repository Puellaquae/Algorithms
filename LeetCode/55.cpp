#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool canJump(const vector<int> &nums) {
        int rightest = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i <= rightest) {
                rightest = max(rightest, nums[i] + i);
            }
        }
        return rightest >= nums.size() - 1;
    }
};

int main() {
    Solution s;
    cout << s.canJump({2, 3, 1, 1, 4}) << endl;
    cout << s.canJump({3, 2, 1, 0, 4}) << endl;
    cout << s.canJump({0}) << endl;
}