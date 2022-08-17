#include <iostream>
#include <queue>

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
    int deepestLeavesSum(TreeNode *root) {
        queue<TreeNode *> q;
        int sum = 0;
        if (root != nullptr) {
            q.emplace(root);
        }
        while (!q.empty()) {
            int len = q.size();
            sum = 0;
            while (len--) {
                auto cur = q.front();
                q.pop();
                sum += cur->val;
                if (cur->left != nullptr) {
                    q.emplace(cur->left);
                }
                if (cur->right != nullptr) {
                    q.emplace(cur->right);
                }
            }
        }
        return sum;
    }
};