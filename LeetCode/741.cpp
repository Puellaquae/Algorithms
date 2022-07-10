#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
public:
    int dfs(vector<vector<int>> &grid, int x, int y, int x2, int y2,
            map<tuple<int, int, int, int>, int> &mem) {
        int h = grid.size();
        int w = grid.front().size();
        if (0 <= x && x < w && 0 <= y && y < h && 0 <= x2 && x2 < w &&
            0 <= y2 && y2 < h) {
            if (mem.count(make_tuple(x, y, x2, y2)) != 0) {
                return mem[make_tuple(x, y, x2, y2)];
            }
            if (grid[y][x] == -1 || grid[y2][x2] == -1) {
                return -1;
            }
            if (x == w - 1 && y == h - 1) {
                return grid[y][x];
            }
            int w = grid[y][x];
            int w2 = grid[y2][x2];
            int rr = dfs(grid, x + 1, y, x2 + 1, y2, mem);
            int rd = dfs(grid, x + 1, y, x2, y2 + 1, mem);
            int dr = dfs(grid, x, y + 1, x2 + 1, y2, mem);
            int dd = dfs(grid, x, y + 1, x2, y2 + 1, mem);
            int ans = max(rr, max(rd, max(dr, dd)));
            if (ans != -1) {
                ans += ((x == x2 && y == y2) ? w : w + w2);
                ;
            }
            mem[make_tuple(x, y, x2, y2)] = ans;
            return ans;
        }
        return -1;
    }

    int cherryPickup(vector<vector<int>> &&grid) {
        map<tuple<int, int, int, int>, int> mem;
        int ans = dfs(grid, 0, 0, 0, 0, mem);
        if (ans == -1) {
            return 0;
        }
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.cherryPickup({{0, 1, -1}, {1, 0, -1}, {1, 1, 1}}) << endl;
    cout << s.cherryPickup({{1, 1, 1, 1, 0, 0, 0},
                            {0, 0, 0, 1, 0, 0, 0},
                            {0, 0, 0, 1, 0, 0, 1},
                            {1, 0, 0, 1, 0, 0, 0},
                            {0, 0, 0, 1, 0, 0, 0},
                            {0, 0, 0, 1, 0, 0, 0},
                            {0, 0, 0, 1, 1, 1, 1}})
         << endl;
    cout << s.cherryPickup({{1, 1, -1}, {1, -1, 1}, {-1, 1, 1}}) << endl;
}