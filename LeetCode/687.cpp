#include <stack>
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
private:
    int res;

public:
    int longestUnivaluePath(TreeNode *root) {
        res = 0;
        dfs(root);
        return res;
    }

    int dfs(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        int left = dfs(root->left) + 1;
        left = (root->left && root->left->val == root->val) ? left : 0;
        int right = dfs(root->right) + 1;
        right = (root->right && root->right->val == root->val) ? right : 0;
        res = max(res, left + right);
        return max(left, right);
    }
};