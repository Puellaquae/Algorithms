#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
    bool check(vector<int> &nums, int m, int k) {
        int c = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            c += lower_bound(nums.begin() + i, nums.end(), nums[i] + m) - nums.begin() - i - 1;
        }
        return k < c;
    }

public:
    int smallestDistancePair(vector<int> &&nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int l = 0;
        int r = 1000007;
        while (l < r - 1) {
            int m = (l + r) / 2;
            if (check(nums, m, k - 1)) {
                r = m;
            } else {
                l = m;
            }
        }
        return l;
    }
};

int main() {
    Solution solution;
    cout << solution.smallestDistancePair({1, 3, 1}, 1) << "\n";
    cout << solution.smallestDistancePair({1, 1, 1}, 2) << "\n";
    cout << solution.smallestDistancePair({1, 6, 1}, 3) << "\n";
}