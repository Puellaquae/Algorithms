#include <iostream>
#include <map>
#include <vector>
using namespace std;

constexpr int MOD = 1000000007;

class Solution {
public:
    int get(const vector<vector<int>> &grid, int x, int y) {
        if (0 <= x && x < grid.size() && 0 <= y && y < grid[0].size()) {
            return grid[x][y];
        }
        return -1;
    }

    int dfs(const vector<vector<int>> &grid, int x, int y,
            map<pair<int, int>, int> &mem) {
        int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int ans = 1;
        auto p = make_pair(x, y);
        if (mem.count(p) != 0) {
            return mem[p];
        }
        for (auto &d : dir) {
            if (get(grid, x + d[0], y + d[1]) > get(grid, x, y)) {
                ans = (ans + dfs(grid, x + d[0], y + d[1], mem)) % MOD;
            }
        }
        mem[p] = ans;
        return ans;
    }

    int countPaths(const vector<vector<int>> &grid) {
        int ans = 0;
        map<pair<int, int>, int> mem;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                ans = (ans + dfs(grid, i, j, mem)) % MOD;
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.countPaths({{1, 1}, {3, 4}}) << endl;
    cout << s.countPaths({{1}, {2}}) << endl;
}