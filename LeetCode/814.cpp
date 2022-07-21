struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        auto left = pruneTree(root->left);
        auto right = pruneTree(root->right);
        if (left == nullptr && right == nullptr && root->val == 0) {
            return nullptr;
        }
        return new TreeNode(root->val, left, right);
    }
};