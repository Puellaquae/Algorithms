#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void wiggleSort(vector<int> &nums) {
        int n = nums.size();
        vector<int> arr = nums;
        sort(arr.begin(), arr.end());
        int x = (n + 1) / 2;
        for (int i = 0, j = x - 1, k = n - 1; i < n; i += 2, j--, k--) {
            nums[i] = arr[j];
            if (i + 1 < n) {
                nums[i + 1] = arr[k];
            }
        }
    }
};

void test(vector<int> num) {
    Solution s;
    s.wiggleSort(num);
    for (auto n : num) {
        cout << n << ", ";
    }
    cout << endl;
}

int main() { 
    test({1, 5, 1, 1, 6, 4});
    test({1, 3, 2, 2, 3, 1});
}