#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>> &grid, int k) {
        auto grid2 = grid;
        int m = grid.size();
        int n = grid[0].size();
        for (int t = 0; t < k; t++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == m - 1 && j == n - 1) {
                        grid2[0][0] = grid[i][j];
                    } else if (j == n - 1) {
                        grid2[i + 1][0] = grid[i][j];
                    } else {
                        grid2[i][j + 1] = grid[i][j];    
                    }
                }
            }
            grid = grid2;
        }
        return grid;
    }
};