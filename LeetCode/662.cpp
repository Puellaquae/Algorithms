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
    int widthOfBinaryTree(TreeNode *root) {
        queue<pair<TreeNode *, unsigned long long>> q;
        q.emplace(root, 0);
        unsigned long long d = 1;
        while (!q.empty()) {
            int len = q.size();
            unsigned long long l = 0;
            unsigned long long r = 0;
            for (int i = 0; i < len; i++) {
                auto top = q.front();
                q.pop();
                if (i == 0) {
                    l = top.second;
                }
                if (i == len - 1) {
                    r = top.second;
                }
                if (top.first->left != nullptr) {
                    q.emplace(top.first->left, top.second * 2);
                }
                if (top.first->right != nullptr) {
                    q.emplace(top.first->right, top.second * 2 + 1);
                }
            }
            d = max(d, r - l + 1);
        }
        return d;
    }
};