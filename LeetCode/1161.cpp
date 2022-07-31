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
    int maxLevelSum(TreeNode *root) {
        queue<TreeNode *> q;
        int maxL = 0;
        int maxS = INT_MIN;
        int l = 0;
        q.push(root);
        while (!q.empty()) {
            l++;
            int len = q.size();
            int s = 0;
            while (len-- > 0) {
                auto node = q.front();
                q.pop();
                s += node->val;
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
            if (s > maxS) {
                maxS = s;
                maxL = l;
            }
        }
        return maxL;
    }
};

int main() {
    Solution s;
    cout << s.maxLevelSum(new TreeNode(
                1, new TreeNode(7, new TreeNode(7), new TreeNode(-8)),
                new TreeNode(0)))
         << endl;
    cout << s.maxLevelSum(new TreeNode(
                -100, new TreeNode(-200, new TreeNode(-20), new TreeNode(-5)),
                new TreeNode(-300, new TreeNode(-10), nullptr)))
         << endl;
}