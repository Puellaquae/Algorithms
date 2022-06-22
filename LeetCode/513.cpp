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
    int findBottomLeftValue(TreeNode *root) {
        queue<TreeNode *> q;
        q.push(root);
        TreeNode *curL = root;
        while (!q.empty()) {
            int s = q.size();
            while (s-- > 0) {
                TreeNode *top = q.front();
                q.pop();
                curL = top;
                if (top->right != nullptr) {
                    q.push(top->right);
                }
                if (top->left != nullptr) {
                    q.push(top->left);
                }
            }
        }
        return curL->val;
    }
};