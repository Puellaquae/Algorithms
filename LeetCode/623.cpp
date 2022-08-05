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
    TreeNode *addOneRow(TreeNode *root, int val, int depth) {
        queue<TreeNode *> q;
        q.push(root);
        if (root == nullptr) {
            return nullptr;
        }
        if (depth <= 1) {
            return new TreeNode(val, root, nullptr);
        }
        int dep = 1;
        while (!q.empty()) {
            int l = q.size();
            dep++;
            while (l-- > 0) {
                auto top = q.front();
                q.pop();

                if (dep == depth) {
                    top->left = new TreeNode(val, top->left, nullptr);
                } else {
                    if (top->left != nullptr) {
                        q.push(top->left);
                    }
                }

                if (dep == depth) {
                    top->right = new TreeNode(val, nullptr, top->right);
                } else {
                    if (top->right != nullptr) {
                        q.push(top->right);
                    }
                }
            }
        }

        return root;
    }
};