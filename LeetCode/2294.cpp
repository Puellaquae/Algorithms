#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

class Solution {
public:
    int partitionArray(vector<int> &&nums, int k) {
        sort(nums.begin(), nums.end());
        int c = 1;
        int curS = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (abs(nums[curS] - nums[i]) > k) {
                c++;
                curS = i;
            }
        }
        return c;
    }
};

int main() {
    Solution s;
    cout << s.partitionArray({3, 6, 1, 2, 5}, 2) << endl;
    cout << s.partitionArray({1, 2, 3}, 1) << endl;
    cout << s.partitionArray({1, 2, 3}, 2) << endl;
    cout << s.partitionArray({2, 2, 4, 5}, 0) << endl;
}