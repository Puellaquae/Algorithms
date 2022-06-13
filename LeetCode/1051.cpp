#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int heightChecker(vector<int> &&heights) {
        vector<int> actual(heights);
        sort(heights.begin(), heights.end());
        int cnt = 0;
        for (int i = 0; i < actual.size(); i++) {
            if (actual[i] != heights[i]) {
                cnt++;
            }
        }
        return cnt;
    }
};

int main() {
    Solution solution;
    cout << solution.heightChecker({1, 1, 4, 2, 1, 3}) << endl;
    cout << solution.heightChecker({5, 1, 2, 3, 4}) << endl;
    cout << solution.heightChecker({1, 2, 3, 4, 5}) << endl;
}