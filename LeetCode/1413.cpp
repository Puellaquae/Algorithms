#include <vector>
using namespace std;

class Solution {
public:
    int minStartValue(vector<int>& nums) {
        int i = 0;
        int s = 0;
        for (auto n : nums) {
            s += n;
            i = min(i, s);
        }
        return 1 - i;
    }
};