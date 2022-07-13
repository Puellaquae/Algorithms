#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int oddCells(int m, int n, const vector<vector<int>> &indices) {
        vector<vector<int>> mat(m, vector<int>(n, 0));
        for (auto &idx : indices) {
            for (int i = 0; i < n; i++) {
                mat[idx[0]][i]++;
            }
            for (int i = 0; i < m; i++) {
                mat[i][idx[1]]++;
            }
        }
        int ans = 0;
        for (auto &r : mat) {
            for (auto &v : r) {
                ans += v % 2;
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.oddCells(2, 3, {{0, 1}, {1, 1}}) << endl;
    cout << s.oddCells(2, 2, {{1, 1}, {0, 0}}) << endl;
}