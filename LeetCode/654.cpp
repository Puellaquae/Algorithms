#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode *constructMaximumBinaryTree(const vector<int> &nums, int begin = 0,
                                         int end = -1) {
        int maxI = 0;
        int maxV = -1;
        if (end == -1) {
            end = nums.size();
        }
        cout << begin << "-" << end << endl;
        if (begin >= end) {
            return nullptr;
        }
        for (int i = begin; i < end; i++) {
            if (nums[i] > maxV) {
                maxI = i;
                maxV = nums[i];
            }
        }
        cout << maxI << ": " << maxV << endl;
        return new TreeNode(maxV, constructMaximumBinaryTree(nums, begin, maxI),
                            constructMaximumBinaryTree(nums, maxI + 1, end));
    }
};

int main() {
    Solution s;
    s.constructMaximumBinaryTree({3, 2});
}