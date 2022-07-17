#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int maxLen = 0;
        for (auto& i : nums) {
            if (i == -1) {
                continue;
            }
            int len = 0;
            int n = i;
            i = -1;
            while (n != -1) {
                len++;
                int ni = nums[n];
                nums[n] = -1;
                n = ni;
            }
            maxLen = max(maxLen, len);
        }
        return maxLen;
    }
};