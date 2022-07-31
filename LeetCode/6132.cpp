#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minimumOperations(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        int ans = unique(nums.begin(), nums.end()) - nums.begin();
        if (nums[0] == 0) {
            ans--;
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> a = {0};
    vector<int> b = {1, 5, 0, 3, 5};
    cout << s.minimumOperations(a) << endl;
    cout << s.minimumOperations(b) << endl;
}