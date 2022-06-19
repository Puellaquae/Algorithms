#include <iostream>
#include <vector>
#include <unordered_map>
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
    unordered_map<int, int> m;
    int maxC = 0;
    int calc(TreeNode *node) {
        if (node == nullptr) {
            return 0;
        }
        int cnt = calc(node->left) + calc(node->right) + node->val;
        m[cnt]++;
        if (m[cnt] > maxC) {
            maxC = m[cnt];
        }
        return cnt;
    }

public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        calc(root);
        vector<int> res;
        for (auto p : m) {
            if (p.second == maxC) {
                res.push_back(p.first);
            }
        }
        return res;
    }
};