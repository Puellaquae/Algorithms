#include <vector>
#include <queue>
using namespace std;

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
    vector<int> largestValues(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> q;
        if (root != nullptr) {
            q.push(root);
        }
        while (!q.empty()) {
            int len = q.size();
            int max = -2147483648;
            while (len-- > 0) {
                TreeNode* cur = q.front();
                q.pop();
                max = cur->val > max ? cur->val : max;
                if (cur->left != nullptr) {
                    q.push(cur->left);
                }
                if (cur->right != nullptr) {
                    q.push(cur->right);
                }
            }
            res.push_back(max);
        }
        return res;
    }
};