#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    long long minimumReplacement(const vector<int> &nums) {
        long long cnt = 0;
        int up = nums.back();
        for (int i = nums.size() - 2; i >= 0; i--) {
            int cur = nums[i];
            cout << up << endl;
            long long z = (cur + up - 1) / up;
            cnt += z - 1;
            up = cur / z;
        }
        return cnt;
    }
};

int main() {
    Solution s;
    cout << s.minimumReplacement({1, 2, 3, 4, 5}) << endl;
    cout << s.minimumReplacement({3, 9, 3}) << endl;
    cout << s.minimumReplacement({12, 9, 7, 6, 17, 19, 21}) << endl;
    cout << s.minimumReplacement(
                {368, 112, 2,   282, 349, 127, 36,  98,  371, 79,  309, 221,
                 175, 262, 224, 215, 230, 250, 84,  269, 384, 328, 118, 97,
                 17,  105, 342, 344, 242, 160, 394, 17,  120, 335, 76,  101,
                 260, 244, 378, 375, 164, 190, 320, 376, 197, 398, 353, 138,
                 362, 38,  54,  172, 3,   300, 264, 165, 251, 24,  312, 355,
                 237, 314, 397, 101, 117, 268, 36,  165, 373, 269, 351, 67,
                 263, 332, 296, 13,  118, 294, 159, 137, 82,  288, 250, 131,
                 354, 261, 192, 111, 16,  139, 261, 295, 112, 121, 234, 335,
                 256, 303, 328, 242, 260, 346, 22,  277, 179, 223})
         << endl;
}