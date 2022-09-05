#include <vector>
#include <map>
#include <string>

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
    vector<TreeNode *> findDuplicateSubtrees(TreeNode *root) {
        vector<TreeNode *> ans;
        map<string, int> m;
        dfs(root, ans, m);
        return ans;
    }

    string dfs(TreeNode *node, vector<TreeNode *> &res, map<string, int> &m) {
        if (node == nullptr) {
            return "$";
        }
        string str = to_string(node->val) + ":" + dfs(node->left, res, m) +
                     ":" + dfs(node->right, res, m);
        if (m[str] == 1) {
            res.push_back(node);
        }
        m[str]++;
        return str;
    }
};