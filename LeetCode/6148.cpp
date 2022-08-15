#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int max3(int a, int b, int c) { return max(a, max(b, c)); }

    int max3x3(const vector<vector<int>> &grid, int x, int y) {
        return max3(
            max3(grid[x][y], grid[x][y + 1], grid[x][y + 2]),
            max3(grid[x + 1][y], grid[x + 1][y + 1], grid[x + 1][y + 2]),
            max3(grid[x + 2][y], grid[x + 2][y + 1], grid[x + 2][y + 2]));
    }

    vector<vector<int>> largestLocal(const vector<vector<int>> &grid) {
        int h = grid.size();
        int w = grid[0].size();
        vector<vector<int>> ans(h - 2, vector<int>(w - 2));
        for (int i = 0; i < h - 2; i++) {
            for (int j = 0; j < w - 2; j++) {
                ans[i][j] = max3x3(grid, i, j);
            }
        }
        return ans;
    }
};