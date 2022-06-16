#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    int findPairs(vector<int> &&nums, int k) {
        map<int, int> m;
        int res = 0;
        if (k < 0) {
            return res;
        }
        for (int n : nums) {
            m[n]++;
        }
        for (auto p : m) {
            if ((k == 0 && p.second > 1) ||
                (k != 0 && m.contains(p.first + k))) {
                res++;
            }
        }
        return res;
    }
};

int main() {
    Solution solution;
    cout << solution.findPairs({3, 1, 4, 1, 5}, 2) << endl;
    cout << solution.findPairs({1, 2, 3, 4, 5}, 1) << endl;
    cout << solution.findPairs({1, 3, 1, 5, 4}, 0) << endl;
}