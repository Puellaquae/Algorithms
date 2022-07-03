#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxArea(const vector<int> &height) {
        int l = 0, p = height.size() - 1;
        auto calc = [&height](int lidx, int pidx) {
            return min(height[lidx], height[pidx]) * (pidx - lidx);
        };
        int res = 0;
        while (l < p) {
            res = max(res, calc(l, p));
            if (height[l] > height[p]) {
                p--;
            } else {
                l++;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7}) << endl;
    cout << s.maxArea({1, 1}) << endl;
    cout << s.maxArea({1, 2, 1}) << endl;
    cout << s.maxArea({2, 3, 4, 5, 18, 17, 6}) << endl;
}