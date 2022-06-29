#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int maxProfit(const vector<int>& prices) {
        int minP = INT_MAX;
        int maxB = 0;
        for (auto p : prices) {
            minP = min(minP, p);
            maxB = max(maxB, p - minP);
        }
        return maxB;
    }
};

int main() {
    Solution s;
    cout << s.maxProfit({7, 1, 5, 3, 6, 4}) << endl;
    cout << s.maxProfit({7, 6, 4, 3, 1}) << endl;
}