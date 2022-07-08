#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minCostToMoveChips(const vector<int> &position) {
        int even = 0;
        int odd = 0;
        for (auto p : position) {
            if (p % 2 == 0) {
                even++;
            } else {
                odd++;
            }
        }
        return min(even, odd);
    }
};

int main() {
    Solution s;
    cout << s.minCostToMoveChips({1, 2, 3}) << endl;
    cout << s.minCostToMoveChips({2, 2, 2, 3, 3}) << endl;
    cout << s.minCostToMoveChips({1, 1000000000}) << endl;
}
