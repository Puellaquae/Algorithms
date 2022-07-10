#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
    int lenLongestFibSubseq(const vector<int>& arr) {
        unordered_map<int, int> indices;
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            indices[arr[i]] = i;
        }
        vector<vector<int>> dp(n, vector<int>(n));
        int ans = 0;
        for (int i = 1; i < n; i++) {
            for (int j = i - 1; j >= 0 && arr[j] * 2 > arr[i]; j--) {
                int k = -1;
                if (indices.count(arr[i] - arr[j])) {
                    k = indices[arr[i] - arr[j]];
                }
                if (k >= 0) {
                    dp[j][i] = max(dp[k][j] + 1, 3);
                }
                ans = max(ans, dp[j][i]);
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.lenLongestFibSubseq({1, 2, 3, 4, 5, 6, 7, 8}) << endl;
    cout << s.lenLongestFibSubseq({1, 3, 7, 11, 12, 14, 18}) << endl;
}