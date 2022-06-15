#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>> &&mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<int> out;
        out.reserve(m * n);
        int x = 0;
        int y = 0;
        bool s = true;
        while (x != m - 1 || y != n - 1) {
            if (0 <= x && x < m && 0 <= y && y < n) {
                out.push_back(mat[x][y]);
            }
            if (s) {
                x--;
                y++;
            } else {
                x++;
                y--;
            }
            if (x < 0) {
                y = x + y + 1;
                x = 0;
                s = !s;
            } else if (y < 0) {
                x = x + y + 1;
                y = 0;
                s = !s;
            }
        }
        out.push_back(mat[x][y]);
        return out;
    }
};

void print(ranges::range auto &&vec) {
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << "\n";
}

int main() {
    Solution solution;
    print(solution.findDiagonalOrder({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    print(solution.findDiagonalOrder({{1, 2}, {3, 4}}));
}