#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int maxSubArray(const vector<int>& nums) {
        int pre = 0, maxAns = nums[0];
        for (const auto &x: nums) {
            pre = max(pre + x, x);
            maxAns = max(maxAns, pre);
        }
        return maxAns;
    }
};

int main() {
    Solution s;
    cout << s.maxSubArray({-2, 1, -3, 4, -1, 2, 1, -5, 4}) << endl;
}