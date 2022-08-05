#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> minSubsequence(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        int sum = 0;
        for (auto n : nums) {
            sum += n;
        }
        int sumR = 0;
        vector<int> ans;
        for (auto r = nums.rbegin(); r != nums.rend(); ++r) {
            if (sumR <= sum) {
                sumR += *r;
                sum -= *r;
                ans.push_back(*r);
            } else {
                break;
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> a{4, 4, 7, 6, 7};
    for (auto v : s.minSubsequence(a)) {
        cout << v << ",";
    }
    cout << endl;
}