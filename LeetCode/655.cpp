#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <tuple>
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
    vector<vector<string>> printTree(TreeNode *root) {
        map<TreeNode *, tuple<TreeNode *, int, int, bool>> vals;
        int height = 0;
        queue<TreeNode *> q;
        q.push(root);
        vals[root] = make_tuple(nullptr, 0, 0, true);
        while (!q.empty()) {
            auto len = q.size();
            height++;
            while (len-- > 0) {
                auto cur = q.front();
                q.pop();
                if (cur->left != nullptr) {
                    vals[cur->left] = make_tuple(cur, height, 0, true);
                    q.push(cur->left);
                }
                if (cur->right != nullptr) {
                    vals[cur->right] = make_tuple(cur, height, 0, false);
                    q.push(cur->right);
                }
            }
        }
        height--;
        int n = (1 << (height + 1)) - 1;
        vector<vector<string>> ans(height + 1, vector<string>(n, ""));
        for (auto &kv : vals) {
            if (kv.first == root) {
                int center = (n - 1) / 2;
                ans[0][center] = to_string(root->val);
                get<2>(kv.second) = center;
            } else {
                auto p = get<0>(kv.second);
                auto r = get<1>(kv.second);
                auto left = get<3>(kv.second) ? -1 : 1;
                auto c = get<2>(vals[p]);
                auto nc = c + left * (1 << (height - r));
                ans[r][nc] = to_string(kv.first->val);
                get<2>(kv.second) = nc;
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    for (auto &l : s.printTree(new TreeNode(
             1, new TreeNode(2, nullptr, new TreeNode(4)), new TreeNode(3)))) {
        for (auto &v : l) {
            cout << (v == "" ? " " : v);
        }
        cout << endl;
    }
}